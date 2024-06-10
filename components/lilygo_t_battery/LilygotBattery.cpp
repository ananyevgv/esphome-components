#include "LilygotBattery.h"
#include "esphome/core/log.h"

namespace esphome {
namespace lilygo_t_battery {

void LilygotBattery::setup() {
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize((adc_unit_t)ADC_UNIT_1, (adc_atten_t)ADC_ATTEN_DB_2_5, (adc_bits_width_t)ADC_WIDTH_BIT_12, 1100, &adc_chars);
  pinMode(14, OUTPUT);
}
void LilygotBattery::update() {
  
  // wait for voltage to stabilise
  delay(10);
  LilygotBattery::update_battery_info();
}
void LilygotBattery::update_battery_info() {
  LilygotBattery::correct_adc_reference();
  // 36 main power supply ?
  // 35 battery ?
  float vb = analogRead(34);
  float bus = (vb / 4095.0) * 7.26;
  
  digitalWrite(14, HIGH);
  delay(10);
  
  float v = analogRead(34);
  //double_t battery_voltage = ((double_t) v / 4095.0) * 2.0 * 3.3 * (this->vref / 1000.0);
  float battery_voltage = (v / 4095.0) * 7.26;
  digitalWrite(14, LOW);
  int level = (1-(4.1-battery_voltage)/(4.1-3.3))*100;
  
  if (level > 100) {level=100;} 
  if (level < 0) {level=0;} 
  
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

