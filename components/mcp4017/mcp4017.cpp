#include "mcp4017.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mcp4017 {

static const char *const TAG = "mcp4017";

void MCP4017Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up MCP4017...");
  
  // Try to write to the wiper register to verify the device is connected
  if (!this->write_byte(MCP4017_REG_WIPER, 0x00)) {
    ESP_LOGE(TAG, "Communication with MCP4017 failed!");
    this->mark_failed();
    return;
  }
  
  ESP_LOGD(TAG, "MCP4017 initialized successfully");
}

void MCP4017Component::dump_config() {
  ESP_LOGCONFIG(TAG, "MCP4017:");
  LOG_I2C_DEVICE(this);
  
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication failed");
  }
}

void MCP4017Component::set_wiper(uint8_t value) {
  // The MCP4017 has 7-bit resolution (0-127)
  if (value > 127)
    value = 127;
    
  ESP_LOGD(TAG, "Setting wiper to %u", value);
  this->write_byte(MCP4017_REG_WIPER, value);
}

uint8_t MCP4017Component::get_wiper() {
  uint8_t value = 0;
  this->read_byte(MCP4017_REG_WIPER, &value);
  return value;
}

void MCP4017Output::setup() {
  if (this->parent_ == nullptr) {
    ESP_LOGE(TAG, "MCP4017Output parent not set!");
    this->mark_failed();
    return;
  }
  
  ESP_LOGCONFIG(TAG, "Setting up MCP4017 output");
}

void MCP4017Output::dump_config() {
  ESP_LOGCONFIG(TAG, "MCP4017 Output:");
  ESP_LOGCONFIG(TAG, "  Component parent %s", this->parent_ ? "set" : "NOT SET");
}

void MCP4017Output::write_state(float state) {
  if (this->parent_ == nullptr) {
    ESP_LOGW(TAG, "No parent set for MCP4017Output!");
    return;
  }
  
  // Map state (0.0-1.0) to wiper value (0-127)
  int wiper_value = static_cast<int>(state * 127.0f);
  
  // Clamp value to valid range
  wiper_value = std::max(0, std::min(127, wiper_value));
  
  ESP_LOGD(TAG, "Setting output: %.2f%% (wiper: %d)", state * 100.0f, wiper_value);
  this->parent_->set_wiper(wiper_value);
}

}  // namespace mcp4017
}  // namespace esphome