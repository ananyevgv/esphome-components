#pragma once
#include <Arduino.h>
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/hal.h"

#include <driver/adc.h>
#include "esp_adc_cal.h"


namespace esphome {
namespace lilygo_t_battery {

class LilygotBattery : public PollingComponent {
 public:
  sensor::Sensor *voltage{nullptr};
  sensor::Sensor *bus_voltage{nullptr};
  sensor::Sensor *battery_level{nullptr};
  
  int vref = 1100;
  void setup() override;
  void update() override;
  void update_battery_info();
  void correct_adc_reference();
  void dump_config() override;

  void set_enable_pin(GPIOPin *enable_pin) { this->enable_pin_ = enable_pin; }
  void set_voltage_sensor(sensor::Sensor *voltage_sensor) { voltage = voltage_sensor; }
  void set_bus_voltage_sensor(sensor::Sensor *bus_voltage_sensor) { bus_voltage = bus_voltage_sensor; }
  void set_battery_level_sensor(sensor::Sensor *battery_level_sensor) { battery_level = battery_level_sensor; }

 protected:
  GPIOPin *enable_pin_{nullptr};

};
}  // namespace lilygo_t_battery
}  // namespace esphome
