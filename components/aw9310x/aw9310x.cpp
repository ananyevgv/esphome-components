#include "aw9310x.h"
#include "aw9310x_reg.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <cstring>

namespace esphome {
namespace aw9310x {

static const char *const TAG = "aw9310x";

// Константы режимов
#define AW9310X_ACTIVE_MODE    1
#define AW9310X_SLEEP_MODE     2

void AW9310XComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up AW9310X Touch Sensor...");
  
  // Инициализация I²C (уже выполнена базовым классом)
  
  // Проверка наличия устройства
  if (!this->read_chip_id()) {
    ESP_LOGE(TAG, "Failed to read chip ID");
    this->mark_failed();
    return;
  }
  
  ESP_LOGI(TAG, "Chip ID verified");
  
  // Сброс
  if (!this->sw_reset()) {
    ESP_LOGE(TAG, "Software reset failed");
    this->mark_failed();
    return;
  }
  
  // Загрузка параметров по умолчанию (из референсного драйвера)
  if (!this->param_load_defaults()) {
    ESP_LOGE(TAG, "Failed to load default parameters");
    this->mark_failed();
    return;
  }

  // Загрузка параметров
  if (!this->param_load()) {
    ESP_LOGE(TAG, "Failed to load parameters");
    this->mark_failed();
    return;
  }

  
  // Автоматическая калибровка
  if (!this->auto_cali()) {
    ESP_LOGE(TAG, "Auto calibration failed");
    this->mark_failed();
    return;
  }
  
  // Установка пороговых значений
  this->set_threshold_values();
  
  // Установка активного режима
  this->operation_mode_set(AW9310X_ACTIVE_MODE);
  
  ESP_LOGI(TAG, "AW9310X initialized successfully");
  ESP_LOGI(TAG, "Threshold: %d", this->threshold_);
}

void AW9310XComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "AW9310X Touch Sensor:");
  LOG_I2C_DEVICE(this);
  
  if (this->interrupt_pin_ != nullptr) {
    ESP_LOGCONFIG(TAG, "  Interrupt Pin: %d", this->interrupt_pin_->get_pin());
  }
  
  ESP_LOGCONFIG(TAG, "  Threshold: %d", this->threshold_);
  ESP_LOGCONFIG(TAG, "  Enabled Channels: ");
  for (auto ch : this->enabled_channels_) {
    ESP_LOGCONFIG(TAG, "    - Channel %d", ch);
  }
  
  if (this->is_failed()) {
    ESP_LOGE(TAG, "  Setup failed!");
  }
}

void AW9310XComponent::loop() {
  // Проверяем состояние прерывания, если пин настроен
  if (this->interrupt_pin_ != nullptr) {
    bool current_state = this->interrupt_pin_->digital_read();
    if (current_state != this->last_interrupt_state_) {
      this->last_interrupt_state_ = current_state;
      if (current_state) {
        ESP_LOGD(TAG, "Interrupt triggered");
        
        // Читаем разностные значения
        int32_t diff[6] = {0};
        if (this->read_diff(diff)) {
          this->update_touch_states(diff);
        }
      }
    }
  } else {
    // Опросный режим: читаем состояния каждые 50 мс
    static uint32_t last_poll = 0;
    uint32_t now = millis();
    if (now - last_poll > 50) {
      last_poll = now;
      
      int32_t diff[6] = {0};
      if (this->read_diff(diff)) {
        this->update_touch_states(diff);
      }
    }
  }
}

bool AW9310XComponent::read_register(uint16_t reg, uint32_t *value) {
  uint8_t data[4] = {0};
  
  // Преобразование адреса в big-endian
  uint8_t reg_addr[2] = {(uint8_t)(reg >> 8), (uint8_t)(reg & 0xFF)};
  
  // Используем штатный I2C API ESPHome
  if (this->write(reg_addr, 2) != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "Failed to write register address 0x%04X", reg);
    return false;
  }
  
  // Читаем данные
  if (this->read(data, 4) != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "Failed to read register data");
    return false;
  }
  
  *value = ((uint32_t)data[0] << 24) | 
           ((uint32_t)data[1] << 16) | 
           ((uint32_t)data[2] << 8) | 
           data[3];
  
  ESP_LOGVV(TAG, "Read register 0x%04X = 0x%08lX", reg, *value);
  return true;
}

bool AW9310XComponent::write_register(uint16_t reg, uint32_t value) {
  uint8_t data[6];
  
  // Адрес регистра (2 байта)
  data[0] = (uint8_t)(reg >> 8);
  data[1] = (uint8_t)(reg & 0xFF);
  
  // Данные (4 байта)
  data[2] = (uint8_t)(value >> 24);
  data[3] = (uint8_t)(value >> 16);
  data[4] = (uint8_t)(value >> 8);
  data[5] = (uint8_t)(value & 0xFF);
  
  // Отправляем все 6 байт
  i2c::ErrorCode err = this->write(data, 6);
  if (err != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "Failed to write register 0x%04X (error: %d)", reg, err);
    return false;
  }
  
  ESP_LOGVV(TAG, "Write register 0x%04X = 0x%08lX", reg, value);
  return true;
}

bool AW9310XComponent::read_chip_id() {
  uint32_t data = 0;
  
  for (int i = 0; i < 5; i++) {
    if (this->read_register(REG_CHIP_ID, &data)) {
      // Chip ID находится в старших 2 байтах
      uint16_t chip_id = (uint16_t)(data >> 16);
      if (chip_id == AW9310X_CHIP_ID) {
        ESP_LOGI(TAG, "Chip ID: 0x%04X", chip_id);
        return true;
      } else {
        ESP_LOGW(TAG, "Invalid chip ID: 0x%04X (expected: 0x%04X)", chip_id, AW9310X_CHIP_ID);
      }
    }
    delay(10);
  }
  
  ESP_LOGE(TAG, "Failed to read valid chip ID");
  return false;
}

bool AW9310XComponent::sw_reset() {
  if (!this->write_register(REG_HOSTCTRL2, 0x00000000)) {
    ESP_LOGE(TAG, "Failed to write reset register");
    return false;
  }
  delay(20);  // Даем время на сброс
  return true;
}

bool AW9310XComponent::param_load() {
  // Базовая конфигурация регистров
  uint32_t scan_ctrl = 0x00000707; // Включить каналы 0-2
  if (!this->write_register(REG_SCANCTRL0, scan_ctrl)) {
    ESP_LOGE(TAG, "Failed to write SCANCTRL0 register");
    return false;
  }
  
  // Настройка прерываний
  uint32_t irq_en = 0x00000606; // Включить прерывания
  if (!this->write_register(REG_HOSTIRQEN, irq_en)) {
    ESP_LOGE(TAG, "Failed to write IRQ enable register");
    return false;
  }
  
  return true;
}

bool AW9310XComponent::param_load_defaults() {
  const size_t count = sizeof(aw9310x_reg_default) / sizeof(aw9310x_reg_default[0]);
  for (size_t i = 0; i < count; i++) {
    if (!this->write_register(aw9310x_reg_default[i].addr, aw9310x_reg_default[i].data)) {
      ESP_LOGE(TAG, "Default param write failed: addr=0x%04X data=0x%08lX",
               aw9310x_reg_default[i].addr, aw9310x_reg_default[i].data);
      return false;
    }
  }
  ESP_LOGI(TAG, "Default parameters loaded (%u regs)", (unsigned) count);
  return true;
}

bool AW9310XComponent::auto_cali() {
  uint32_t data_en = 0;
  
  if (!this->read_register(REG_SCANCTRL0, &data_en)) {
    ESP_LOGE(TAG, "Failed to read SCANCTRL0 for calibration");
    return false;
  }
  
  // Установка битов калибровки
  uint32_t mask = ~(0x3f << 8);
  uint32_t value = (data_en & 0x3f) << 8;
  
  if (!this->write_register(REG_SCANCTRL0, (data_en & mask) | value)) {
    ESP_LOGE(TAG, "Failed to write calibration bits");
    return false;
  }
  
  // Ждем завершения калибровки
  delay(100);
  
  ESP_LOGI(TAG, "Auto calibration completed");
  return true;
}

void AW9310XComponent::set_threshold_values() {
  // Установка пороговых значений для каждого канала
  uint16_t th_regs[] = {
    REG_PROXTH0_CH0, REG_PROXTH0_CH1, REG_PROXTH0_CH2,
    REG_PROXTH0_CH3, REG_PROXTH0_CH4, REG_PROXTH0_CH5
  };
  
  for (uint8_t i = 0; i < 6; i++) {
    if (!this->write_register(th_regs[i], this->threshold_)) {
      ESP_LOGW(TAG, "Failed to set threshold for channel %d", i);
    } else {
      ESP_LOGI(TAG, "Set threshold %d for channel %d", this->threshold_, i);
    }
  }
}

void AW9310XComponent::operation_mode_set(uint8_t mode) {
  if (mode == AW9310X_ACTIVE_MODE && this->old_mode_ != AW9310X_ACTIVE_MODE) {
    if (!this->write_register(REG_CMD, AW9310X_ACTIVE_MODE)) {
      ESP_LOGE(TAG, "Failed to set active mode");
    } else {
      ESP_LOGI(TAG, "Set to active mode");
    }
  } else if (mode == AW9310X_SLEEP_MODE && this->old_mode_ != AW9310X_SLEEP_MODE) {
    if (!this->write_register(REG_CMD, AW9310X_SLEEP_MODE)) {
      ESP_LOGE(TAG, "Failed to set sleep mode");
    } else {
      ESP_LOGI(TAG, "Set to sleep mode");
    }
  }
  
  this->mode_ = mode;
  this->old_mode_ = this->mode_;
}

bool AW9310XComponent::read_diff(int32_t *diff) {
  uint16_t diff_regs[] = {
    REG_DIFF_CH0, REG_DIFF_CH1, REG_DIFF_CH2,
    REG_DIFF_CH3, REG_DIFF_CH4, REG_DIFF_CH5
  };
  
  for (uint8_t i = 0; i < 6; i++) {
    uint32_t value = 0;
    if (!this->read_register(diff_regs[i], &value)) {
      ESP_LOGW(TAG, "Failed to read diff register for channel %d", i);
      return false;
    }
    
    // Преобразуем знаковое значение
    diff[i] = (int32_t)value;
  }
  
  return true;
}

void AW9310XComponent::update_touch_states(int32_t *diff) {
  for (auto ch : this->enabled_channels_) {
    if (ch < 6 && this->touch_sensors_[ch] != nullptr) {
      // Определение состояния касания
      // В оригинальном драйвере diff логируют со сдвигом >> 10
      const int32_t diff_scaled = diff[ch] >> 10;
      bool new_state = (diff_scaled > this->threshold_);
      
      // Обновляем состояние только если оно изменилось
      if (new_state != this->channel_states_[ch]) {
        this->channel_states_[ch] = new_state;
        this->touch_sensors_[ch]->publish_state(new_state);
        
        if (new_state) {
          ESP_LOGD(TAG, "Channel %d touched (diff=%d scaled=%d)", ch, diff[ch], diff_scaled);
        } else {
          ESP_LOGD(TAG, "Channel %d released", ch);
        }
      }
    }
  }
}

void AW9310XComponent::register_channel(AW9310XChannel *sensor, uint8_t channel) {
  if (channel < max_channels_) {
    // Приводим AW9310XChannel* к binary_sensor::BinarySensor*
    touch_sensors_[channel] = static_cast<binary_sensor::BinarySensor*>(sensor);
    enabled_channels_.push_back(channel);
    ESP_LOGI(TAG, "Registered channel %d", channel);
  } else {
    ESP_LOGW(TAG, "Invalid channel %d (max: %d)", channel, max_channels_ - 1);
  }
}

}  // namespace aw9310x
}  // namespace esphome
