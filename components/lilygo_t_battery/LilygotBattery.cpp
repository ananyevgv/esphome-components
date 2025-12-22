#include "LilygotBattery.h"
#include "esphome/core/log.h"

namespace esphome {
namespace lilygo_t_battery {

static const char *const TAG = "lilygo";

void LilygotBattery::setup() {
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize((adc_unit_t)ADC_UNIT_1, (adc_atten_t)ADC_ATTEN_DB_2_5, (adc_bits_width_t)ADC_WIDTH_BIT_12, 1100, &adc_chars);
  // pinMode(14, OUTPUT);

}
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

  float vb = analogRead(34);
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
    // digitalWrite(14, HIGH);
    delay(10);
    float v = analogRead(34);
    battery_voltage = (v / 4095.0) * 7.26;
    if (this->enable_pin_ != nullptr) {
      this->enable_pin_->setup();
      this->enable_pin_->digital_write(false);
    }
    // digitalWrite(14, LOW);
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

void LilygotBattery::correct_adc_reference() {
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type =
      esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_0, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
    this->vref = adc_chars.vref;
  }
}

}  // namespace lilygo_t_battery
}  // namespace esphome

