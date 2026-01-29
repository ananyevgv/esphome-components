#pragma once
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace lilygo_t_battery {

class LilygotBattery : public PollingComponent {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;
  
  void set_enable_pin(GPIOPin *enable) { enable_pin_ = enable; }
  void set_adc_sensor(sensor::Sensor *sensor) { adc_sensor_ = sensor; }
  void set_voltage_sensor(sensor::Sensor *sensor) { voltage_sensor_ = sensor; }
  void set_bus_voltage_sensor(sensor::Sensor *sensor) { bus_voltage_sensor_ = sensor; }
  void set_battery_level_sensor(sensor::Sensor *sensor) { battery_level_sensor_ = sensor; }
  void set_voltage_divider(float divider) { voltage_divider_ = divider; }

 protected:
  GPIOPin *enable_pin_{nullptr};
  sensor::Sensor *adc_sensor_{nullptr};
  sensor::Sensor *voltage_sensor_{nullptr};
  sensor::Sensor *bus_voltage_sensor_{nullptr};
  sensor::Sensor *battery_level_sensor_{nullptr};
  float voltage_divider_{7.26f};
  
  void update_battery_info();
  int calculate_battery_level(float voltage, bool is_charging);
};
}  // namespace lilygo_t_battery
}  // namespace esphome