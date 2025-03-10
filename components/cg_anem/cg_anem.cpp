#include "cg_anem.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace cg_anem {

static const char *const TAG = "cg_anem.sensor";

static const uint8_t CG_ANEM_REGISTER_VERSION = 0x04;
static const uint8_t CG_ANEM_REGISTER_WHO_I_AM = 0x05;
static const uint8_t CG_ANEM_REGISTER_STATUS = 0x06;

static const uint8_t CG_ANEM_REGISTER_WIND_H = 0x07;
static const uint8_t CG_ANEM_REGISTER_WIND_L = 0x08; // 16 bit

static const uint8_t CG_ANEM_REGISTER_TEST_COLD_H = 0x09;
static const uint8_t CG_ANEM_REGISTER_TEST_COLD_L = 0x0A;
static const uint8_t CG_ANEM_REGISTER_TEST_HOT_H = 0x0B;
static const uint8_t CG_ANEM_REGISTER_TEST_HOT_L = 0x0C;

static const uint8_t CG_ANEM_REGISTER_VIN = 0x0D;
static const uint8_t CG_ANEM_REGISTER_HEAT_WT = 0x0E;

static const uint8_t CG_ANEM_REGISTER_COLD_H = 0x10;
static const uint8_t CG_ANEM_REGISTER_COLD_L = 0x11;
static const uint8_t CG_ANEM_REGISTER_HOT_H = 0x12;
static const uint8_t CG_ANEM_REGISTER_HOT_L = 0x13;
static const uint8_t CG_ANEM_REGISTER_DT_H = 0x14;
static const uint8_t CG_ANEM_REGISTER_DT_L = 0x15;

static const uint8_t CG_ANEM_REGISTER_ADDRESS = 0x20;

static const uint8_t CG_ANEM_REGISTER_WIND_MAX_H = 0x21;
static const uint8_t CG_ANEM_REGISTER_WIND_MAX_L = 0x22;
static const uint8_t CG_ANEM_REGISTER_WIND_MIN_H = 0x23;
static const uint8_t CG_ANEM_REGISTER_WIND_MIN_L = 0x24;
static const uint8_t CG_ANEM_REGISTER_RESET_WIND = 0x25;

static const uint8_t CG_ANEM_STATUS_INCORRECT_TARING_RANGE = 0b10000000;
static const uint8_t CG_ANEM_STATUS_INCORRECT_TARING = 0b01000000;
static const uint8_t CG_ANEM_STATUS_WATCHDOG_TIMER = 0b00100000;
static const uint8_t CG_ANEM_STATUS_OVERVOLTAGE = 0b00000010;
static const uint8_t CG_ANEM_STATUS_UNSTEADY_PROCESS = 0b00000001;

inline uint16_t combine_bytes(uint8_t msb, uint8_t lsb) { return ((msb & 0xFF) << 8) | (lsb & 0xFF); }

void CGAnemComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up CG Anem...");
  uint8_t chip_id = 0;

  // Mark as not failed before initializing. Some devices will turn off sensors to save on batteries
  // and when they come back on, the COMPONENT_STATE_FAILED bit must be unset on the component.
  if ((this->component_state_ & COMPONENT_STATE_MASK) == COMPONENT_STATE_FAILED) {
    this->component_state_ &= ~COMPONENT_STATE_MASK;
    this->component_state_ |= COMPONENT_STATE_CONSTRUCTION;
  }
  uint8_t version_raw;
  !this->read_byte(CG_ANEM_REGISTER_VERSION, &version_raw);
  float version = version_raw / 10.0;
  ESP_LOGI(TAG, "Version: %.1f", version);
  if (this->firmware_version_sensor_ != nullptr)
    this->firmware_version_sensor_->publish_state(version);
  
  if (!this->write_byte(CG_ANEM_REGISTER_WHO_I_AM, 0x11)) {
     this->error_code_ = COMMUNICATION_FAILED;
     this->mark_failed();
    return;
  }
  this->read_status();
}

void CGAnemComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "CGANEM:");
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

  LOG_SENSOR("  ", "Ambient temperature", this->ambient_temperature_sensor_);
  LOG_SENSOR("  ", "Hotend_temperature", this->hotend_temperature_sensor_);
  LOG_SENSOR("  ", "Heat power", this->heat_power_sensor_);
  LOG_SENSOR("  ", "Air_consumption", this->air_consumption_sensor_);
  LOG_SENSOR("  ", "Air flow rate", this->air_flow_rate_sensor_);
  LOG_SENSOR("  ", "Min air flow rate", this->min_air_flow_rate_sensor_);
  LOG_SENSOR("  ", "Max air flow rate", this->max_air_flow_rate_sensor_);

}


void CGAnemComponent::read_status() {
  uint8_t status;
  if (!this->read_byte(CG_ANEM_REGISTER_STATUS, &status)) {
    ESP_LOGW(TAG, "Error reading status register.");
    this->status_set_warning();
    return;
  }

  if (status & CG_ANEM_STATUS_INCORRECT_TARING_RANGE) {
    ESP_LOGW(TAG, "Incorrect taring range detected");
  }

  if (status & CG_ANEM_STATUS_INCORRECT_TARING) {
    ESP_LOGW(TAG, "Incorrect taring detected");
  }

  if ((status & CG_ANEM_STATUS_WATCHDOG_TIMER) == 0) {
    ESP_LOGW(TAG, "Watchdog disabled");
    // this->status_wdt_sensor_->publish_state(true);
  } else {
    // this->status_wdt_sensor_->publish_state(false);
  }


  if (status & CG_ANEM_STATUS_OVERVOLTAGE) {
    ESP_LOGW(TAG, "Overvoltage detected");
    // this->status_ov_sensor_->publish_state(true);
  } else {
    // this->status_ov_sensor_->publish_state(false);
  }

  if (status & CG_ANEM_STATUS_UNSTEADY_PROCESS) {
    ESP_LOGW(TAG, "Unsteady process detected");
    this->status_set_warning();
    // this->status_up_sensor_->publish_state(true);
  } else {
    this->status_clear_warning();
    // this->status_up_sensor_->publish_state(false);
  }
}

void CGAnemComponent::update() {
  this->read_status();

  if (this->status_has_warning()) {
    return;
  }

  uint16_t tempRaw;
  if (auto tempH = this->read_byte(CG_ANEM_REGISTER_COLD_H)) {
    if (auto tempL = this->read_byte(CG_ANEM_REGISTER_COLD_L)) {
      tempRaw = (*tempH << 8) | *tempL;

    } else {
      ESP_LOGW(TAG, "Error reading cold temp.");
      this->status_set_warning();
      return;
    }
  } else {
    ESP_LOGW(TAG, "Error reading cold temp.");
    this->status_set_warning();
    return;
  }

  uint16_t speedRaw;
  if (auto speedH = this->read_byte(CG_ANEM_REGISTER_WIND_H)) {
    if (auto speedL = this->read_byte(CG_ANEM_REGISTER_WIND_L)) {
      speedRaw = (*speedH << 8) | *speedL;
      ESP_LOGI(TAG, "speedH: %d", speedH);
      ESP_LOGI(TAG, "speedL: %d", speedL);
    } else {
      ESP_LOGW(TAG, "Error reading wind speed.");
      this->status_set_warning();
      return;
    }
  } else {
    ESP_LOGW(TAG, "Error reading wind speed.");
    this->status_set_warning();
    return;
  }
  
  float MinAir;
  if (11 >= 10) {
    if (auto MinAirH = this->read_byte(CG_ANEM_REGISTER_WIND_MIN_H)) {
      if (auto MinAirL = this->read_byte(CG_ANEM_REGISTER_WIND_MIN_L)) {
        MinAir = ((*MinAirH << 8) | *MinAirL) / 10.0;
      }
     }
  } else {
    MinAir = -255;
    this->status_set_warning();
    return;
  }
  float MaxAir;
  if (11 >= 10) {
    if (auto MaxAirH = this->read_byte(CG_ANEM_REGISTER_WIND_MAX_H)) {
      if (auto MaxAirL = this->read_byte(CG_ANEM_REGISTER_WIND_MAX_L)) {
        MinAir = ((*MaxAirH << 8) | *MaxAirL) / 10.0;
      }
     }
  } else {
    MinAir = -255;
    this->status_set_warning();
    return;
  }

  float power;
  if (auto PowerRaw = this->read_byte(CG_ANEM_REGISTER_HEAT_WT)) {
    power = (*PowerRaw * 1.36125) / 255;
  } else {
    ESP_LOGW(TAG, "Error reading power.");
    this->status_set_warning();
    return;
  }

  if (this->hotend_temperature_sensor_ != nullptr)
    this->hotend_temperature_sensor_->publish_state(power);




  float temp = tempRaw / 10.0f;
  float speed = speedRaw / 10.0f;
  float сonsumption;
  // duct= πr2
  float duct = 78.5;
  if (duct > -0.01 && speed != -255) {
    сonsumption = 6 * speed * duct * 0.06;
  } else {
    сonsumption = -255;
  }



  ESP_LOGV(TAG, "Got temperature=%.1f°C speed=%.1fm/s ", temp, speed);

  if (this->ambient_temperature_sensor_ != nullptr)
    this->ambient_temperature_sensor_->publish_state(temp);
  if (this->air_flow_rate_sensor_ != nullptr)
    this->air_flow_rate_sensor_->publish_state(speed);
  if (this->air_consumption_sensor_ != nullptr)
    this->air_consumption_sensor_->publish_state(сonsumption);

}

}  // namespace cg_anem
}  // namespace esphome
