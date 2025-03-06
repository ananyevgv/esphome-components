#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace cg_anem {

/// This class implements support for the GC Anem Temperature+Pressure+Humidity i2c sensor.
class CGAnemComponent : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  void update() override;

  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_ambient_temperature_sensor(sensor::Sensor *ambient_temperature_sensor) { this->ambient_temperature_sensor_ = ambient_temperature_sensor; }
  void set_hotend_temperature_sensor(sensor::Sensor *hotend_temperature_sensor) { this->hotend_temperature_sensor_ = hotend_temperature_sensor; }
  void set_heat_power_sensor(sensor::Sensor *heat_power_sensor) { this->heat_power_sensor_ = heat_power_sensor; }
  void set_air_consumption_sensor(sensor::Sensor *air_consumption_sensor) { this->air_consumption_sensor_ = air_consumption_sensor; }
  void set_air_flow_rate_sensor(sensor::Sensor *air_flow_rate_sensor) { this->air_flow_rate_sensor_ = air_flow_rate_sensor; }
  void set_firmware_version_sensor(sensor::Sensor *firmware_version_sensor) { this->firmware_version_sensor_ = firmware_version_sensor; }
  void set_min_air_flow_rate_sensor(sensor::Sensor *min_air_flow_rate_sensor) { this->min_air_flow_rate_sensor_ = min_air_flow_rate_sensor; }
  void set_max_air_flow_rate_sensor(sensor::Sensor *max_air_flow_rate_sensor) { this->max_air_flow_rate_sensor_ = max_air_flow_rate_sensor; }


  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)


  float get_setup_priority() const override;

 protected:
  sensor::Sensor *ambient_temperature_sensor_{nullptr};
  sensor::Sensor *hotend_temperature_sensor_{nullptr};
  sensor::Sensor *heat_power_sensor_{nullptr};
  sensor::Sensor *air_consumption_sensor_{nullptr};
  sensor::Sensor *air_flow_rate_sensor_{nullptr};
  sensor::Sensor *firmware_version_sensor_{nullptr};
  sensor::Sensor *min_air_flow_rate_sensor_{nullptr};
  sensor::Sensor *max_air_flow_rate_sensor_{nullptr};


  enum ErrorCode {
    NONE = 0,
    COMMUNICATION_FAILED,
  } error_code_{NONE};

 private:
  void read_status();
};

}  // namespace cg_anem
}  // namespace esphome
