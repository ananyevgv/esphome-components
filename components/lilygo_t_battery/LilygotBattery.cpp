#include "LilygotBattery.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace lilygo_t_battery {

static const char *const TAG = "lilygo_t_battery";

void LilygotBattery::setup() {
  ESP_LOGI(TAG, "Initializing LilyGO T-Battery component");
  
  if (enable_pin_ != nullptr) {
    enable_pin_->setup();
    enable_pin_->digital_write(false);
    ESP_LOGD(TAG, "Enable pin configured");
  }
  
  if (adc_sensor_ == nullptr) {
    ESP_LOGE(TAG, "No ADC sensor configured!");
  } else {
    ESP_LOGD(TAG, "ADC sensor configured");
  }
}

void LilygotBattery::update() {
  update_battery_info();
}

void LilygotBattery::update_battery_info() {
  if (adc_sensor_ == nullptr || !adc_sensor_->has_state()) {
    ESP_LOGW(TAG, "ADC sensor not available or has no state");
    return;
  }
  
  // Получаем напряжение от ADC сенсора
  float adc_voltage = adc_sensor_->state;
  
  if (adc_voltage < 0.001f) {
    ESP_LOGW(TAG, "ADC reading too low: %.3fV", adc_voltage);
    return;
  }
  
  ESP_LOGD(TAG, "Raw ADC voltage: %.3fV", adc_voltage);
  
  // Применяем коэффициент делителя напряжения
  float measured_voltage = adc_voltage * voltage_divider_;
  
  // Определяем, идет ли зарядка
  bool is_charging = (measured_voltage > 4.2f);
  
  float bus_voltage = 0.0f;
  float battery_voltage = measured_voltage;
  
  // Логика для работы с дополнительной схемой измерения
  if (!is_charging && enable_pin_ != nullptr) {
    // Включаем схему измерения батареи
    enable_pin_->digital_write(true);
    delay(10); // Ждем стабилизации
    
    // Дополнительная задержка для обновления ADC
    delay(50);
    
    // Читаем обновленное значение
    if (adc_sensor_->has_state()) {
      float new_adc_voltage = adc_sensor_->state;
      if (new_adc_voltage > 0.001f) {
        battery_voltage = new_adc_voltage * voltage_divider_;
      }
    }
    
    // Выключаем схему
    enable_pin_->digital_write(false);
    
    ESP_LOGD(TAG, "Battery mode - voltage: %.2fV", battery_voltage);
  } else if (is_charging) {
    // При зарядке USB напряжение доступно напрямую
    bus_voltage = measured_voltage;
    ESP_LOGD(TAG, "Charging mode - USB voltage: %.2fV", bus_voltage);
  }
  
  // Рассчитываем уровень заряда
  int battery_level = calculate_battery_level(battery_voltage, is_charging);
  
  // Публикуем данные
  if (bus_voltage_sensor_ != nullptr && bus_voltage > 0.1f) {
    bus_voltage_sensor_->publish_state(bus_voltage);
  }
  
  if (voltage_sensor_ != nullptr && battery_voltage > 0.1f) {
    voltage_sensor_->publish_state(battery_voltage);
  }
  
  if (battery_level_sensor_ != nullptr) {
    battery_level_sensor_->publish_state(battery_level);
  }
  
  ESP_LOGD(TAG, "Final: Battery=%.2fV, Level=%d%%, Charging=%s", 
           battery_voltage, battery_level, is_charging ? "Yes" : "No");
}

int LilygotBattery::calculate_battery_level(float voltage, bool is_charging) {
  int level = 0;
  
  if (is_charging) {
    // При зарядке: 4.2V = 0%, 4.35V = 100%
    if (voltage >= 4.35f) {
      level = 100;
    } else if (voltage <= 4.2f) {
      level = 0;
    } else {
      level = static_cast<int>(((voltage - 4.2f) / 0.15f) * 100.0f);
    }
  } else {
    // При разряде: 3.3V = 0%, 4.2V = 100%
    if (voltage >= 4.2f) {
      level = 100;
    } else if (voltage <= 3.3f) {
      level = 0;
    } else {
      level = static_cast<int>(((voltage - 3.3f) / 0.9f) * 100.0f);
    }
  }
  
  // Ограничиваем значения
  if (level > 100) level = 100;
  if (level < 0) level = 0;
  
  return level;
}

void LilygotBattery::dump_config() {
  ESP_LOGCONFIG(TAG, "LilyGO T-Battery:");
  
  if (enable_pin_ != nullptr) {
    LOG_PIN("  Enable pin: ", enable_pin_);
  }
  
  ESP_LOGCONFIG(TAG, "  Voltage divider ratio: %.2f", voltage_divider_);
  
  if (voltage_sensor_ != nullptr) {
    LOG_SENSOR("  ", "Battery Voltage", voltage_sensor_);
  }
  
  if (bus_voltage_sensor_ != nullptr) {
    LOG_SENSOR("  ", "Bus Voltage", bus_voltage_sensor_);
  }
  
  if (battery_level_sensor_ != nullptr) {
    LOG_SENSOR("  ", "Battery Level", battery_level_sensor_);
  }
  
  LOG_UPDATE_INTERVAL(this);
}

}  // namespace lilygo_t_battery
}  // namespace esphome