#include "hts221.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace hts221 {

static const char *const TAG = "hts221.sensor";

static const uint8_t HTS221_WHO_AM_I_REG       = 0x0f;
static const uint8_t HTS221_CTRL1_REG          = 0x20;
static const uint8_t HTS221_CTRL2_REG          = 0x21;
static const uint8_t HTS221_STATUS_REG         = 0x27;
static const uint8_t HTS221_HUMIDITY_OUT_L_REG = 0x28;
static const uint8_t HTS221_TEMP_OUT_L_REG     = 0x2a;
static const uint8_t HTS221_H0_rH_x2_REG       = 0x30;
static const uint8_t HTS221_H1_rH_x2_REG       = 0x31;
static const uint8_t HTS221_T0_degC_x8_REG     = 0x32;
static const uint8_t HTS221_T1_degC_x8_REG     = 0x33;
static const uint8_t HTS221_T1_T0_MSB_REG      = 0x35;
static const uint8_t HTS221_H0_T0_OUT_REG      = 0x36;
static const uint8_t HTS221_H1_T0_OUT_REG      = 0x3a;
static const uint8_t HTS221_T0_OUT_REG         = 0x3c;
static const uint8_t HTS221_T1_OUT_REG         = 0x3e;

void hts221Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up HTS221...");


  // Mark as not failed before initializing. Some devices will turn off sensors to save on batteries
  // and when they come back on, the COMPONENT_STATE_FAILED bit must be unset on the component.

  if (!this->write_byte(HTS221_WHO_AM_I_REG, 0xbc)) {
    this->error_code_ = COMMUNICATION_FAILED;
    this->mark_failed();
    return;
  }
}
void hts221Component::dump_config() {
  ESP_LOGCONFIG(TAG, "HTS221:");
  LOG_I2C_DEVICE(this);
  switch (this->error_code_) {
    case COMMUNICATION_FAILED:
      ESP_LOGE(TAG, "Communication with CG Anem failed!");
      break;
    case NONE:
    default:
      break;
  }

  LOG_UPDATE_INTERVAL(this);

  LOG_SENSOR("  ", "temperature", this->temperature_sensor_);
  LOG_SENSOR("  ", "humidity", this->humidity_sensor_);

}

void hts221Component::update() {
  this->read_status();

  if (this->status_has_warning()) {
    return;
  }
  
  int16_t tout, hout;
  if (this-> read_byte(HTS221_TEMP_OUT_L_REG, &tout)) {
    return (tout * _hts221TemperatureSlope + _hts221TemperatureZero);
  } else {
      ESP_LOGW(TAG, "Error reading Temperature");
      return;
  }
  
  if (this-> read_byte(HTS221_HUMIDITY_OUT_L_REG, &hout)) {
    return (hout * _hts221HumiditySlope + _hts221HumidityZero);;
  } else {
      ESP_LOGW(TAG, "Error reading Hummiditi");
      return;
  }

  
  if (this->temperature_sensor_ != nullptr)
    this->temperature_sensor_->publish_state(tout);
  if (this->humidity_sensor_ != nullptr)
    this->humidity_sensor_->publish_state(hout);
 
  ESP_LOGV(TAG, "Got temperature=%.1f°C humidity=%.1f%% ", tout, hout);

}


}  // namespace hts221
}  // namespace esphome
