#include "LilygotBattery.h"
#include "esphome/core/log.h"

namespace esphome {
namespace lilygo_t_battery {

static const char *const TAG = "lilygo";

void LilygotBattery::dump_config() {
  ESP_LOGCONFIG(TAG, "lilygo:");
  LOG_SENSOR("  ", "USB voltage", this->voltage);
  LOG_SENSOR("  ", "Battery charge", this->bus_voltage);
  LOG_SENSOR("  ", "Battery voltage", this->battery_level);
  LOG_UPDATE_INTERVAL(this);
}

void LilygotBattery::update() {

  // wait for voltage to stabilise
  delay(1);
  LilygotBattery::update_battery_info();
}
void LilygotBattery::update_battery_info() {
  LilygotBattery::correct_adc_reference();

  float vb = this->reference_voltage_;
  // analogRead(34);
  float bus = (vb / 4095.0) * 7.26;

  int level = 0;
  float battery_voltage;
  if (bus > 0) { 
    level = (1-(4.75-bus)/(4.75-4.2))*100;
    battery_voltage = 0;
  } 
  else {
    if (this->enable_pin_ != nullptr) {
      this->enable_pin_->setup();
      this->enable_pin_->digital_write(true);
    }    

    delay(10);
    float v = this->reference_voltage_;
    // analogRead(34);
    battery_voltage = (v / 4095.0) * 7.26;
    if (this->enable_pin_ != nullptr) {
      this->enable_pin_->setup();
      this->enable_pin_->digital_write(false);
    }

    level = (1-(4-battery_voltage)/(4-3.25))*100;
  }

  if (level > 100) {level=100;} 
  if (level < 0) {level=0;} 

  ESP_LOGD(TAG, "USB voltage: %0.2f V", bus);
  ESP_LOGD(TAG, "Battery charge: %d %%", level);
  ESP_LOGD(TAG, "Battery voltage: %0.2f V", battery_voltage);

  if (this-> bus_voltage != nullptr) {
    this->bus_voltage->publish_state(bus);
  }
  if (this->battery_level != nullptr) {
    this->battery_level->publish_state(level);
  }
  if (this->voltage != nullptr) {
    this->voltage->publish_state(battery_voltage);

  }
}


}  // namespace lilygo_t_battery
}  // namespace esphome
