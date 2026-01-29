#pragma once
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include <vector>
#include <map>

namespace esphome {
namespace mq {

enum MQModel {
  MQ_MODEL_2 = 0,
  MQ_MODEL_3,
  MQ_MODEL_4,
  MQ_MODEL_5,
  MQ_MODEL_6,
  MQ_MODEL_7,
  MQ_MODEL_8,
  MQ_MODEL_9,
  MQ_MODEL_131,
  MQ_MODEL_135,
  MQ_MODEL_136,
  MQ_MODEL_303A,
  MQ_MODEL_309A,
};

enum MQGasType {
  MQ_GAS_TYPE_ACETONA,
  MQ_GAS_TYPE_ALCOHOL,
  MQ_GAS_TYPE_BENZENE,
  MQ_GAS_TYPE_CH4,
  MQ_GAS_TYPE_CL2,
  MQ_GAS_TYPE_CO,
  MQ_GAS_TYPE_CO2,
  MQ_GAS_TYPE_ETHANOL,
  MQ_GAS_TYPE_H2,
  MQ_GAS_TYPE_HEXANE,
  MQ_GAS_TYPE_HYDROGEN,
  MQ_GAS_TYPE_ISO_BUTANO,
  MQ_GAS_TYPE_LPG,
  MQ_GAS_TYPE_NH4,
  MQ_GAS_TYPE_H2S,
  MQ_GAS_TYPE_NOX,
  MQ_GAS_TYPE_O3,
  MQ_GAS_TYPE_PROPANE,
  MQ_GAS_TYPE_SMOKE,
  MQ_GAS_TYPE_TOLUENO,
};

struct MQGasSensor {
  MQGasType gas_type;
  float a;
  float b;
  sensor::Sensor *sensor;

  std::string gas_name();
};

struct MQModelParameters {
  MQModel model;
  std::vector<MQGasSensor> gas_sensors;

  std::string model_name();
  float get_ratio_in_clean_air();
};

class MQSensor : public PollingComponent {
 public:
  MQSensor(sensor::Sensor *adc_sensor, MQModel model, bool is_esp8266, float rl);
  
  void add_sensor(sensor::Sensor *sensor, MQGasType gas_type);
  void set_R0(float r0) { this->r0_ = r0; }
  void set_VR(float vr) { this->voltage_resolution_ = vr; }
  
  // Component overrides
  float get_setup_priority() const override { return setup_priority::DATA; }
  void setup() override;
  void dump_config() override;
  void update() override;
  
 protected:
  sensor::Sensor *adc_sensor_;
  MQModelParameters model_parameters_;
  bool is_esp8266_;
  float rl_ = 10.0;
  float r0_ = 0.0;
  float voltage_resolution_ = 3.3;
  bool calibrated_ = false;
  
  // MQ расчеты
  float calculate_rs(float voltage);
  float calculate_r0();
  float calculate_ppm(float rs, MQGasSensor &gas_sensor);
  
 private:
  static std::map<MQModel, std::vector<MQGasSensor>> gas_parameters_definition;
  
  struct CalibrationData {
    float sum_rs = 0.0f;
    int samples = 0;
  } calibration_data_;
};

}  // namespace mq
}  // namespace esphome