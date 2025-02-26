#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace cg_anem {

/// This class implements support for the GC Anem Temperature+Pressure+Humidity i2c sensor.
class CGAnemComponent : public PollingComponent, public i2c::I2CDevice {
 public:
  void set_duct(float duct);
  void set_ambient_temperature_sensor(sensor::Sensor *ambient_temperature_sensor) { ambient_temperature_sensor_ = ambient_temperature_sensor; }
  void set_hotend_temperature(sensor::Sensor *hotend_temperature_sensor) { hotend_temperature_sensor_ = hotend_temperature_sensor; }
  void set_heat_power_sensor(sensor::Sensor *heat_power_sensor) { heat_power_sensor_ = heat_power_sensor; }
  void set_air_consumption_sensor(sensor::Sensor *air_consumption_sensor) { air_consumption_sensor_ = air_consumption_sensor; }
  void set_air_flow_rate_sensor(sensor::Sensor *air_flow_rate_sensor) { air_flow_rate_sensor_ = air_flow_rate_sensor; }
  void set_firmware_version_sensor(sensor::Sensor *firmware_version_sensor) { firmware_version_sensor_ = firmware_version_sensor; }
  void set_min_air_flow_rate_sensor(sensor::Sensor *min_air_flow_rate_sensor) { min_air_flow_rate_sensor_ = min_air_flow_rate_sensor; }
  void set_max_air_flow_rate_sensor(sensor::Sensor *max_air_flow_rate_sensor) { max_air_flow_rate_sensor_ = max_air_flow_rate_sensor; }

  void set_status_up_sensor(binary_sensor::BinarySensor *status_up) { status_up_sensor_ = status_up_sensor; }
  void set_status_ov_sensor(binary_sensor::BinarySensor *status_ov) { status_ov_sensor_ = status_ov_sensor; }
  void set_status_wdt_sensor(binary_sensor::BinarySensor *status_wdt) { status_wdt_sensor_ = status_wdt_sensor; }

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void update() override;

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
