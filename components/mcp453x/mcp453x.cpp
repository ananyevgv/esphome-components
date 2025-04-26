#include "mcp453x.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mcp453x {

static const char *const TAG = "mcp453x";

void MCP453XComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up MCP453X...");
  
  // Try to write to the wiper register to verify the device is connected
  if (!this->write_byte(MCP453X_REG_WIPER, 0x00)) {
    ESP_LOGE(TAG, "Communication with MCP453X failed!");
    this->mark_failed();
    return;
  }
  
  ESP_LOGD(TAG, "MCP453X initialized successfully");
}

void MCP453XComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "MCP453X:");
  LOG_I2C_DEVICE(this);
  
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication failed");
  }
}

void MCP453XComponent::set_wiper(uint8_t value) {
  // The MCP453X has 7-bit resolution (0-127)
  if (value > 127)
    value = 127;
    
  ESP_LOGD(TAG, "Setting wiper to %u", value);
  this->write_byte(MCP453X_REG_WIPER, value);
}

uint8_t MCP453XComponent::get_wiper() {
  uint8_t value = 0;
  this->read_byte(MCP453X_REG_WIPER, &value);
  return value;
}

void MCP453XOutput::setup() {
  if (this->parent_ == nullptr) {
    ESP_LOGE(TAG, "MCP453XOutput parent not set!");
    this->mark_failed();
    return;
  }
  
  ESP_LOGCONFIG(TAG, "Setting up MCP453X output");
}

void MCP453XOutput::dump_config() {
  ESP_LOGCONFIG(TAG, "MCP453X Output:");
  ESP_LOGCONFIG(TAG, "  Component parent %s", this->parent_ ? "set" : "NOT SET");
}

void MCP453XOutput::write_state(float state) {
  if (this->parent_ == nullptr) {
    ESP_LOGW(TAG, "No parent set for MCP453XOutput!");
    return;
  }
  
  // Map state (0.0-1.0) to wiper value (0-127)
  int wiper_value = static_cast<int>(state * 127.0f);
  
  // Clamp value to valid range
  wiper_value = std::max(0, std::min(127, wiper_value));
  
  ESP_LOGD(TAG, "Setting output: %.2f%% (wiper: %d)", state * 100.0f, wiper_value);
  this->parent_->set_wiper(wiper_value);
}

}  // namespace mcp453x
}  // namespace esphome