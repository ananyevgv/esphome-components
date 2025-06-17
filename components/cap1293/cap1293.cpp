#include "cap1293.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace cap1293 {

static const char *const TAG = "cap1293";

void CAP1293Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up CAP1293...");

  // Reset device using the reset pin
  if (this->reset_pin_ != nullptr) {
    this->reset_pin_->setup();
    this->reset_pin_->digital_write(false);
    delay(100);  // NOLINT
    this->reset_pin_->digital_write(true);
    delay(100);  // NOLINT
    this->reset_pin_->digital_write(false);
    delay(100);  // NOLINT
  }

  // Check if CAP1293 is actually connected
  this->read_byte(CAP1293_PRODUCT_ID, &this->cap1293_product_id_);
  this->read_byte(CAP1293_MANUFACTURE_ID, &this->cap1293_manufacture_id_);
  this->read_byte(CAP1293_REVISION, &this->cap1293_revision_);

  if ((this->cap1293_product_id_ != 0x6F) || (this->cap1293_manufacture_id_ != 0x5D)) {
    this->error_code_ = COMMUNICATION_FAILED;
    this->mark_failed();
    return;
  }

  // Set sensitivity
  uint8_t sensitivity = 0;
  this->read_byte(CAP1293_SENSITVITY, &sensitivity);
  sensitivity = sensitivity & 0x0f;
  this->write_byte(CAP1293_SENSITVITY, sensitivity | this->touch_threshold_);

  // Allow multiple touches
  this->write_byte(CAP1293_MULTI_TOUCH, this->allow_multiple_touches_);

  // Have LEDs follow touches
  this->write_byte(CAP1293_LED_LINK, 0xFF);

  // Speed up a bit
  this->write_byte(CAP1293_STAND_BY_CONFIGURATION, 0x30);
}

void CAP1293Component::dump_config() {
  ESP_LOGCONFIG(TAG, "CAP1293:");
  LOG_I2C_DEVICE(this);
  LOG_PIN("  Reset Pin: ", this->reset_pin_);
  ESP_LOGCONFIG(TAG, "  Product ID: 0x%x", this->cap1293_product_id_);
  ESP_LOGCONFIG(TAG, "  Manufacture ID: 0x%x", this->cap1293_manufacture_id_);
  ESP_LOGCONFIG(TAG, "  Revision ID: 0x%x", this->cap1293_revision_);

  switch (this->error_code_) {
    case COMMUNICATION_FAILED:
      ESP_LOGE(TAG, "Product ID or Manufacture ID of the connected device does not match a known CAP1293.");
      break;
    case NONE:
    default:
      break;
  }
}

void CAP1293Component::loop() {
  uint8_t touched = 0;

  this->read_register(CAP1293_SENSOR_INPUT_STATUS, &touched, 1);

  if (touched) {
    uint8_t data = 0;
    this->read_register(CAP1293_MAIN, &data, 1);
    data = data & ~CAP1293_MAIN_INT;

    this->write_register(CAP1293_MAIN, &data, 2);
  }

  for (auto *channel : this->channels_) {
    channel->process(touched);
  }
}

}  // namespace cap1293
}  // namespace esphome
