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
  if ((this->component_state_ & COMPONENT_STATE_MASK) == COMPONENT_STATE_FAILED) {
    this->component_state_ &= ~COMPONENT_STATE_MASK;
    this->component_state_ |= COMPONENT_STATE_CONSTRUCTION;
  }

  if (!this->write_byte(HTS221_WHO_AM_I_REG, 0xbc)) {
    this->error_code_ = COMMUNICATION_FAILED;
    this->mark_failed();
    return;
  }
  uint8_t h0rH, h1rH, t0degC0, t0degC1, t1degC0, t1degC1;
  
  this-> read_byte(HTS221_H0_rH_x2_REG, &h0rH);
  this-> read_byte(HTS221_H1_rH_x2_REG, &h1rH);
  this-> read_byte(HTS221_T0_degC_x8_REG, &t0degC0);
  this-> read_byte(HTS221_T1_T0_MSB_REG, &t0degC1);
  this-> read_byte(HTS221_T1_degC_x8_REG, &t1degC0);
  this-> read_byte(HTS221_T1_T0_MSB_REG, &t1degC1);
  
  uint16_t t0degC = (t0degC0) | ((t0degC & 0x03) << 8);
  uint16_t t1degC = (t1degC0) | ((t1degC1 & 0x0c) << 6);
  
  uint8_t H0_T0_OUT_H, H0_T0_OUT_L, H1_T0_OUT_H, H1_T0_OUT_L, t0Out_H, t0Out_L, t1Out_H, t1Out_L;
  int16_t h0t0Out, h1t0Out, t0Out, t1Out;
  
  if (this-> read_byte(HTS221_H0_T0_OUT_REG, &H0_T0_OUT_L)) {
    if (this-> read_byte((HTS221_H0_T0_OUT_REG+1), &H0_T0_OUT_H)) {
      h0t0Out = ((H0_T0_OUT_H << 8) | H0_T0_OUT_L);
    } else {
      ESP_LOGW(TAG, "Error reading H0_T0_OUT_H.");
      //this->status_set_warning();
      return;
    }
  } else {
    ESP_LOGW(TAG, "Error reading H0_T0_OUT_L.");
    this->status_set_warning();
    return;
  }  
  
  if (this-> read_byte(HTS221_H1_T0_OUT_REG, &H1_T0_OUT_L)) {
    if (this-> read_byte((HTS221_H1_T0_OUT_REG+1), &H1_T0_OUT_H)) {
      h0t0Out = ((H1_T0_OUT_H << 8) | H1_T0_OUT_L);
    } else {
      ESP_LOGW(TAG, "Error reading H1_T0_OUT_H.");
      //this->status_set_warning();
      return;
    }
  } else {
    ESP_LOGW(TAG, "Error reading H1_T0_OUT_L.");
    this->status_set_warning();
    return;
  }   

  if (this-> read_byte(HTS221_T0_OUT_REG, &t0Out_L)) {
    if (this-> read_byte(HTS221_T0_OUT_REG+1, &t0Out_H)) {
      t0Out = ((t0Out_H << 8) | t0Out_L);
    } else {
      ESP_LOGW(TAG, "Error reading t0Out_H.");
      //this->status_set_warning();
      return;
    }
  } else {
    ESP_LOGW(TAG, "Error reading t0Out_L.");
    this->status_set_warning();
    return;
  }   

  if (this-> read_byte(HTS221_T1_OUT_REG, &t1Out_L)) {
    if (this-> read_byte(HTS221_T1_OUT_REG+1, &t1Out_H)) {
      t1Out = ((t1Out_H << 8) | t1Out_L);
    } else {
      ESP_LOGW(TAG, "Error reading t1Out_H.");
      //this->status_set_warning();
      return;
    }
  } else {
    ESP_LOGW(TAG, "Error reading t1Out_L.");
    this->status_set_warning();
    return;
  }  
  
  // calculate slopes and 0 offset from calibration values,
  // for future calculations: value = a * X + b

  _hts221HumiditySlope = (h1rH - h0rH) / (2.0 * (h1t0Out - h0t0Out));
  _hts221HumidityZero = (h0rH / 2.0) - _hts221HumiditySlope * h0t0Out;

  _hts221TemperatureSlope = (t1degC - t0degC) / (8.0 * (t1Out - t0Out));
  _hts221TemperatureZero = (t0degC / 8.0) - _hts221TemperatureSlope * t0Out;
  write_byte(HTS221_CTRL1_REG, 0x84);
  write_byte(HTS221_CTRL2_REG, 0x01);
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
  uint8_t tout_L, tout_H, hout_L, hout_H;
  int16_t tout, hout;

  if (this-> read_byte(HTS221_TEMP_OUT_L_REG, &tout_L)) {
    if (this-> read_byte(HTS221_TEMP_OUT_L_REG+1, &tout_H)) {
      tout = ((tout_H << 8) | tout_L);
    } else {
      ESP_LOGW(TAG, "Error reading tout_H.");
      //this->status_set_warning();
      return;
    }
  } else {
    ESP_LOGW(TAG, "Error reading tout_L.");
    this->status_set_warning();
    return;
  }  
  
  float temp = (tout * _hts221TemperatureSlope + _hts221TemperatureZero);

  if (this-> read_byte(HTS221_HUMIDITY_OUT_L_REG, &hout_L)) {
    if (this-> read_byte(HTS221_HUMIDITY_OUT_L_REG+1, &hout_H)) {
      hout = ((hout_H << 8) | hout_L);
    } else {
      ESP_LOGW(TAG, "Error reading hout_H.");
      //this->status_set_warning();
      return;
    }
  } else {
    ESP_LOGW(TAG, "Error reading hout_L.");
    this->status_set_warning();
    return;
  } 

  float humm = (hout * _hts221HumiditySlope + _hts221HumidityZero);
  
  if (this->temperature_sensor_ != nullptr)
    this->temperature_sensor_->publish_state(temp);
  if (this->humidity_sensor_ != nullptr)
    this->humidity_sensor_->publish_state(humm);
 
  ESP_LOGV(TAG, "Got temperature=%.1f°C humidity=%.1f%% ", temp, humm);

}

}  // namespace hts221
}  // namespace esphome
