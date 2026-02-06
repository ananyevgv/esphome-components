#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/gpio.h"  // Добавлено для GPIOPin
#include <vector>

namespace esphome {
namespace aw9310x {

// Объявим класс канала вперед, чтобы избежать циклических зависимостей
class AW9310XChannel;

class AW9310XComponent : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  void loop() override;
  
  void set_interrupt_pin(InternalGPIOPin *pin) { interrupt_pin_ = pin; }
  void set_threshold(int32_t threshold) { threshold_ = threshold; }
  
  void set_enabled_channels(const std::vector<uint8_t> &channels) {
    enabled_channels_ = channels;
  }
  
  void register_channel(AW9310XChannel *sensor, uint8_t channel);
  
  // Бинарные сенсоры касаний для каждого канала
  binary_sensor::BinarySensor *touch_sensors_[6] = {nullptr};

 protected:
  bool read_register(uint16_t reg, uint32_t *value);
  bool write_register(uint16_t reg, uint32_t value);
  
  bool read_chip_id();
  bool sw_reset();
  bool param_load();
  bool param_load_defaults();
  bool auto_cali();
  
  void set_threshold_values();
  void operation_mode_set(uint8_t mode);
  bool read_diff(int32_t *diff);
  void update_touch_states(int32_t *diff);
  
 private:
  InternalGPIOPin *interrupt_pin_{nullptr};
  int32_t threshold_{50000};  // Пороговое значение для определения касания
  
  std::vector<uint8_t> enabled_channels_;
  bool channel_states_[6] = {false};
  
  uint8_t mode_{0};
  uint8_t old_mode_{0};
  
  static constexpr uint8_t max_channels_ = 6;
  
  // Состояние GPIO для прерываний
  bool last_interrupt_state_{false};
  uint32_t last_interrupt_time_{0};
};

// Класс для отдельных каналов сенсора
class AW9310XChannel : public binary_sensor::BinarySensor {
 public:
  void set_channel(uint8_t channel) { channel_ = channel; }
  uint8_t get_channel() const { return channel_; }
  
 private:
  uint8_t channel_{0};
};

}  // namespace aw9310x
}  // namespace esphome
