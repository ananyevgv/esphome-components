#pragma once

#include "esphome/core/component.h"
#include "esphome/components/output/float_output.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace mcp4017 {

// mcp4017 register addresses
static const uint8_t mcp4017_REG_WIPER = 0x5E;
static const uint8_t mcp4017_REG_CONFIG = 0x5F;

class mcp4017Component : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
  
  void set_wiper(uint8_t value);
  uint8_t get_wiper();
};

class mcp4017Output : public output::FloatOutput, public Component {
 public:
  void set_parent(mcp4017Component *parent) { parent_ = parent; }
  
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
  
 protected:
  void write_state(float state) override;
  mcp4017Component *parent_{nullptr};
};

}  // namespace mcp4017
}  // namespace esphome
