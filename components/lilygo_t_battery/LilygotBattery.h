#pragma once
#include <Arduino.h>
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/hal.h"

#include <driver/adc.h>
#include "esp_adc_cal.h"


namespace esphome {
namespace lilygo_t_battery {

class LilygotBattery : public Component, public sensor::Sensor  {
 public:
  sensor::Sensor *voltage{nullptr};
  sensor::Sensor *bus_voltage{nullptr};
  sensor::Sensor *battery_level{nullptr};
  
  int vref = 1100;
  void setup() override {
    this->sensor_->add_on_state_callback([this](float value) { this->process_(value); });
    if (this->sensor_->has_state())
      this->process_(this->sensor_->state);
  }
  void update() override;
  void update_battery_info();
  void correct_adc_reference();
  void dump_config() override;

  void set_sensor(Sensor *sensor) { sensor_ = sensor; }
  void set_enable_pin(GPIOPin *enable) { this->enable_pin_ = enable; }
  void set_reference_voltage(float reference_voltage) { reference_voltage_ = reference_voltage; }
  void set_voltage_sensor(sensor::Sensor *voltage_sensor) { voltage = voltage_sensor; }
  void set_bus_voltage_sensor(sensor::Sensor *bus_voltage_sensor) { bus_voltage = bus_voltage_sensor; }
  void set_battery_level_sensor(sensor::Sensor *battery_level_sensor) { battery_level = battery_level_sensor; }

 protected:
  sensor::Sensor *sensor_;
  GPIOPin *enable_pin_{nullptr};
  float reference_voltage_;

};
}  // namespace lilygo_t_battery
}  // namespace esphome
