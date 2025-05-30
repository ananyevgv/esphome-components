#pragma once

#include <utility>

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace hts221 {

class hts221Component : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;
 
  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { temperature_sensor_ = temperature_sensor; }
  void set_humidity_sensor(sensor::Sensor *humidity_sensor) { humidity_sensor_ = humidity_sensor; }

 protected:
  sensor::Sensor *temperature_sensor_{nullptr};
  sensor::Sensor *humidity_sensor_{nullptr};

 enum ErrorCode {
    NONE = 0,
    COMMUNICATION_FAILED,
  } error_code_{NONE};


 private:
  void read_status();
  float _hts221HumiditySlope;
  float _hts221HumidityZero;
  float _hts221TemperatureSlope;
  float _hts221TemperatureZero;
};

}  // namespace hts221
}  // namespace esphome
