#pragma once

#include "esphome/core/component.h"
#include "esphome/components/output/float_output.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace mcp453x {

// MCP453X register addresses
static const uint8_t MCP453X_REG_WIPER = 0x00;
static const uint8_t MCP453X_REG_CONFIG = 0x04;

class MCP453XComponent : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
  
  void set_wiper(uint8_t value);
  uint8_t get_wiper();
};

class MCP453XOutput : public output::FloatOutput, public Component {
 public:
  void set_parent(MCP453XComponent *parent) { parent_ = parent; }
  
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
  
 protected:
  void write_state(float state) override;
  MCP453XComponent *parent_{nullptr};
};

}  // namespace mcp453x
}  // namespace esphome