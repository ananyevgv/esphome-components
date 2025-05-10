#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/output/binary_output.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

#include <vector>

namespace esphome {
namespace cap1293 {

enum {
  CAP1293_I2CADDR = 0x28,
  CAP1293_SENSOR_INPUT_STATUS = 0x3,
  CAP1293_MULTI_TOUCH = 0x2A,
  CAP1293_LED_LINK = 0x72,
  CAP1293_PRODUCT_ID = 0xFD,
  CAP1293_MANUFACTURE_ID = 0xFE,
  CAP1293_STAND_BY_CONFIGURATION = 0x41,
  CAP1293_REVISION = 0xFF,
  CAP1293_MAIN = 0x00,
  CAP1293_MAIN_INT = 0x01,
  CAP1293_LEDPOL = 0x73,
  CAP1293_INTERUPT_REPEAT = 0x28,
  CAP1293_SENSITVITY = 0x1f,
};

class CAP1293Channel : public binary_sensor::BinarySensor {
 public:
  void set_channel(uint8_t channel) { channel_ = channel; }
  void process(uint8_t data) { this->publish_state(static_cast<bool>(data & (1 << this->channel_))); }

 protected:
  uint8_t channel_{0};
};

class CAP1293Component : public Component, public i2c::I2CDevice {
 public:
  void register_channel(CAP1293Channel *channel) { this->channels_.push_back(channel); }
  void set_touch_threshold(uint8_t touch_threshold) { this->touch_threshold_ = touch_threshold; };
  void set_allow_multiple_touches(bool allow_multiple_touches) {
    this->allow_multiple_touches_ = allow_multiple_touches ? 0x41 : 0x80;
  };
  void set_reset_pin(GPIOPin *reset_pin) { this->reset_pin_ = reset_pin; }
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }
  void loop() override;

 protected:
  std::vector<CAP1293Channel *> channels_{};
  uint8_t touch_threshold_{0x07};
  uint8_t allow_multiple_touches_{0x80};

  GPIOPin *reset_pin_{nullptr};

  uint8_t cap1293_product_id_{0};
  uint8_t cap1293_manufacture_id_{0};
  uint8_t cap1293_revision_{0};

  enum ErrorCode {
    NONE = 0,
    COMMUNICATION_FAILED,
  } error_code_{NONE};
};

}  // namespace cap1293
}  // namespace esphome
