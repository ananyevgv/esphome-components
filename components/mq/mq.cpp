#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include "mq.h"

namespace esphome {
namespace mq {

static const char *TAG = "mq";

// Реализация методов MQGasSensor
std::string MQGasSensor::gas_name() {
  switch (gas_type) {
    case MQ_GAS_TYPE_ACETONA:
      return "ACETONA";
    case MQ_GAS_TYPE_ALCOHOL:
      return "ALCOHOL";
    case MQ_GAS_TYPE_BENZENE:
      return "BENZENE";
    case MQ_GAS_TYPE_CH4:
      return "CH4";
    case MQ_GAS_TYPE_CL2:
      return "CL2";
    case MQ_GAS_TYPE_CO:
      return "CO";
    case MQ_GAS_TYPE_CO2:
      return "CO2";
    case MQ_GAS_TYPE_ETHANOL:
      return "ETHANOL";
    case MQ_GAS_TYPE_H2:
      return "H2";
    case MQ_GAS_TYPE_HEXANE:
      return "HEXANE";
    case MQ_GAS_TYPE_HYDROGEN:
      return "HYDROGEN";
    case MQ_GAS_TYPE_ISO_BUTANO:
      return "ISO_BUTANO";
    case MQ_GAS_TYPE_LPG:
      return "LPG";
    case MQ_GAS_TYPE_NH4:
      return "NH4";
    case MQ_GAS_TYPE_H2S:
      return "H2S";
    case MQ_GAS_TYPE_NOX:
      return "NOX";
    case MQ_GAS_TYPE_O3:
      return "O3";
    case MQ_GAS_TYPE_PROPANE:
      return "PROPANE";
    case MQ_GAS_TYPE_SMOKE:
      return "SMOKE";
    case MQ_GAS_TYPE_TOLUENO:
      return "TOLUENO";
    default:
      return "UNKNOWN GAS";
  }
}

// Реализация методов MQModelParameters
std::string MQModelParameters::model_name() {
  switch (model) {
    case MQ_MODEL_2:
      return "MQ2";
    case MQ_MODEL_3:
      return "MQ3";
    case MQ_MODEL_4:
      return "MQ4";
    case MQ_MODEL_5:
      return "MQ5";
    case MQ_MODEL_6:
      return "MQ6";
    case MQ_MODEL_7:
      return "MQ7";
    case MQ_MODEL_8:
      return "MQ8";
    case MQ_MODEL_9:
      return "MQ9";
    case MQ_MODEL_131:
      return "MQ131";
    case MQ_MODEL_135:
      return "MQ135";
    case MQ_MODEL_136:
      return "MQ136";
    case MQ_MODEL_303A:
      return "MQ303A";
    case MQ_MODEL_309A:
      return "MQ309A";
    default:
      return "MQ Unknown";
  }
}

float MQModelParameters::get_ratio_in_clean_air() {
  switch (model) {
    case MQ_MODEL_2:
      return 9.83;
    case MQ_MODEL_3:
      return 60.0;
    case MQ_MODEL_4:
      return 4.4;
    case MQ_MODEL_5:
      return 6.5;
    case MQ_MODEL_6:
      return 10.0;
    case MQ_MODEL_7:
      return 27.5;
    case MQ_MODEL_8:
      return 70.0;
    case MQ_MODEL_9:
      return 9.6;
    case MQ_MODEL_131:
      return 15;
    case MQ_MODEL_135:
      return 3.6;
    case MQ_MODEL_136:
      return 3.6;
    case MQ_MODEL_303A:
      return 1.0;
    case MQ_MODEL_309A:
      return 11.0;
    default:
      return 0.0;
  }
}

// Public methods

MQSensor::MQSensor(sensor::Sensor *adc_sensor, MQModel model, bool is_esp8266, float rl)
    : adc_sensor_(adc_sensor), is_esp8266_(is_esp8266), rl_(rl) {
  this->model_parameters_ = {.model = model, .gas_sensors = gas_parameters_definition[model]};
}

void MQSensor::add_sensor(sensor::Sensor *sensor, MQGasType gas_type) {
  auto it = std::find_if(this->model_parameters_.gas_sensors.begin(),
                         this->model_parameters_.gas_sensors.end(),
                         [gas_type](const MQGasSensor &e) { return e.gas_type == gas_type; });
  if (it != this->model_parameters_.gas_sensors.end()) {
    it->sensor = sensor;
  }
}

// Setup and calibration

void MQSensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up %s MQ sensor...", this->model_parameters_.model_name().c_str());
  ESP_LOGCONFIG(TAG, "  RL: %.1f kOhm", this->rl_);
  ESP_LOGCONFIG(TAG, "  Voltage resolution: %.1f V", this->voltage_resolution_);
  
  // Если R0 задан вручную, используем его
  if (this->r0_ > 0.0) {
    ESP_LOGCONFIG(TAG, "  Using predefined R0: %.2f kOhm", this->r0_);
    this->calibrated_ = true;
  }
}

void MQSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "MQ Sensor:");
  ESP_LOGCONFIG(TAG, "  Model: %s", this->model_parameters_.model_name().c_str());
  ESP_LOGCONFIG(TAG, "  RL: %.1f kOhm", this->rl_);
  ESP_LOGCONFIG(TAG, "  Voltage resolution: %.1f V", this->voltage_resolution_);
  
  if (this->r0_ > 0.0) {
    ESP_LOGCONFIG(TAG, "  R0: %.2f kOhm (predefined)", this->r0_);
  } else if (this->calibrated_) {
    ESP_LOGCONFIG(TAG, "  R0: %.2f kOhm (calibrated)", this->r0_);
  } else {
    ESP_LOGCONFIG(TAG, "  R0: Not calibrated yet");
  }
  
  LOG_UPDATE_INTERVAL(this);
  
  for (auto &gas_sensor : this->model_parameters_.gas_sensors) {
    if (gas_sensor.sensor != nullptr) {
      ESP_LOGCONFIG(TAG, "  %s sensor: enabled", gas_sensor.gas_name().c_str());
    }
  }
}

// Расчетные функции

float MQSensor::calculate_rs(float voltage) {
  if (voltage <= 0.0f) {
    return NAN;
  }
  
  // RS = RL * (Vcc - VRL) / VRL
  // Где VRL - напряжение на RL (измеренное)
  // Vcc - напряжение питания (voltage_resolution_)
  float vrl = voltage;
  float vcc = this->voltage_resolution_;
  
  if (vrl >= vcc) {
    return 0.0f;  // Короткое замыкание или неправильные измерения
  }
  
  return (this->rl_ * (vcc - vrl)) / vrl;
}

float MQSensor::calculate_r0() {
  if (this->calibration_data_.samples == 0) {
    return NAN;
  }
  
  float avg_rs = this->calibration_data_.sum_rs / this->calibration_data_.samples;
  float ratio_in_clean_air = this->model_parameters_.get_ratio_in_clean_air();
  
  // R0 = RS / ratio_in_clean_air
  return avg_rs / ratio_in_clean_air;
}

float MQSensor::calculate_ppm(float rs, MQGasSensor &gas_sensor) {
  if (this->r0_ <= 0.0f || rs <= 0.0f) {
    return NAN;
  }
  
  float rs_r0_ratio = rs / this->r0_;
  
  // Используем формулу из библиотеки MQUnifiedsensor
  // ppm = a * (rs_r0_ratio)^b
  return gas_sensor.a * powf(rs_r0_ratio, gas_sensor.b);
}

// Основной цикл обновления

void MQSensor::update() {
  if (!this->adc_sensor_->has_state()) {
    ESP_LOGW(TAG, "ADC sensor not ready");
    return;
  }
  
  // Получаем напряжение от ADC сенсора
  float voltage = this->adc_sensor_->get_state();
  
  if (std::isnan(voltage) || voltage <= 0.0f) {
    ESP_LOGW(TAG, "Invalid voltage reading: %.3f V", voltage);
    return;
  }
  
  ESP_LOGD(TAG, "ADC voltage: %.3f V", voltage);
  
  // Рассчитываем RS
  float rs = calculate_rs(voltage);
  
  if (std::isnan(rs)) {
    ESP_LOGW(TAG, "Failed to calculate RS");
    return;
  }
  
  // Калибровка (первые 10 измерений)
  if (!this->calibrated_ && this->r0_ <= 0.0f) {
    if (this->calibration_data_.samples < 10) {
      this->calibration_data_.sum_rs += rs;
      this->calibration_data_.samples++;
      ESP_LOGD(TAG, "Calibration sample %d/10, RS: %.2f kOhm", 
               this->calibration_data_.samples, rs);
      
      if (this->calibration_data_.samples == 10) {
        this->r0_ = calculate_r0();
        this->calibrated_ = true;
        ESP_LOGCONFIG(TAG, "Calibration complete: R0 = %.2f kOhm", this->r0_);
      }
      return;
    }
  }
  
  // Публикуем данные для каждого газового сенсора
  for (auto &gas_sensor : this->model_parameters_.gas_sensors) {
    if (gas_sensor.sensor == nullptr) {
      continue;
    }
    
    float ppm = calculate_ppm(rs, gas_sensor);
    
    if (!std::isnan(ppm) && ppm > 0.0f) {
      ESP_LOGD(TAG, "%s: %.2f ppm", gas_sensor.gas_name().c_str(), ppm);
      gas_sensor.sensor->publish_state(ppm);
    }
  }
}

// Определения параметров газов
std::map<MQModel, std::vector<MQGasSensor>> MQSensor::gas_parameters_definition = {
    {MQ_MODEL_2,
     {
         {.gas_type = MQ_GAS_TYPE_H2, .a = 987.99, .b = -2.162},
         {.gas_type = MQ_GAS_TYPE_LPG, .a = 574.25, .b = -2.222},
         {.gas_type = MQ_GAS_TYPE_CO, .a = 36974.0, .b = -3.109},
         {.gas_type = MQ_GAS_TYPE_ALCOHOL, .a = 3616.1, .b = -2.675},
         {.gas_type = MQ_GAS_TYPE_PROPANE, .a = 658.71, .b = -2.168},
     }},
    {MQ_MODEL_3,
     {
         {.gas_type = MQ_GAS_TYPE_LPG, .a = 44771, .b = -3.245},
         {.gas_type = MQ_GAS_TYPE_CH4, .a = 2 * 10 ^ 31, .b = 19.01},
         {.gas_type = MQ_GAS_TYPE_CO, .a = 521853, .b = -3.821},
         {.gas_type = MQ_GAS_TYPE_ALCOHOL, .a = 0.3934, .b = -1.504},
         {.gas_type = MQ_GAS_TYPE_BENZENE, .a = 4.8387, .b = -2.68},
         {.gas_type = MQ_GAS_TYPE_HEXANE, .a = 7585.3, .b = -2.849},
     }},
    {MQ_MODEL_4,
     {
         {.gas_type = MQ_GAS_TYPE_LPG, .a = 3811.9, .b = -3.113},
         {.gas_type = MQ_GAS_TYPE_CH4, .a = 1012.7, .b = -2.786},
         {.gas_type = MQ_GAS_TYPE_CO, .a = 200000000000000.0, .b = -19.05},
         {.gas_type = MQ_GAS_TYPE_ALCOHOL, .a = 60000000000.0, .b = -14.01},
         {.gas_type = MQ_GAS_TYPE_SMOKE, .a = 30000000.0, .b = -8.308},
     }},
    {MQ_MODEL_5,
     {
         {.gas_type = MQ_GAS_TYPE_H2, .a = 1163.8, .b = -3.874},
         {.gas_type = MQ_GAS_TYPE_LPG, .a = 80.897, .b = -2.431},
         {.gas_type = MQ_GAS_TYPE_CH4, .a = 177.65, .b = -2.56},
         {.gas_type = MQ_GAS_TYPE_CO, .a = 491204, .b = -5.826},
         {.gas_type = MQ_GAS_TYPE_ALCOHOL, .a = 97124, .b = -4.918},
     }},
    {MQ_MODEL_6,
     {
         {.gas_type = MQ_GAS_TYPE_H2, .a = 88158, .b = -3.597},
         {.gas_type = MQ_GAS_TYPE_LPG, .a = 1009.2, .b = -2.35},
         {.gas_type = MQ_GAS_TYPE_CH4, .a = 2127.2, .b = -2.526},
         {.gas_type = MQ_GAS_TYPE_CO, .a = 1000000000000000.0, .b = -13.5},
         {.gas_type = MQ_GAS_TYPE_ALCOHOL, .a = 50000000.0, .b = -6.017},
     }},
    {MQ_MODEL_7,
     {
         {.gas_type = MQ_GAS_TYPE_H2, .a = 69.014, .b = -1.374},
         {.gas_type = MQ_GAS_TYPE_LPG, .a = 700000000.0, .b = -7.703},
         {.gas_type = MQ_GAS_TYPE_CH4, .a = 60000000000000.0, .b = -10.54},
         {.gas_type = MQ_GAS_TYPE_CO, .a = 99.042, .b = -1.518},
         {.gas_type = MQ_GAS_TYPE_ALCOHOL, .a = 40000000000000000.0, .b = -12.35},
     }},
    {MQ_MODEL_8,
     {
         {.gas_type = MQ_GAS_TYPE_H2, .a = 976.97, .b = -0.688},
         {.gas_type = MQ_GAS_TYPE_LPG, .a = 10000000.0, .b = -3.123},
         {.gas_type = MQ_GAS_TYPE_CH4, .a = 80000000000000.0, .b = -6.666},
         {.gas_type = MQ_GAS_TYPE_CO, .a = 2000000000000000000.0, .b = -8.074},
         {.gas_type = MQ_GAS_TYPE_ALCOHOL, .a = 76101.0, .b = -1.86},
     }},
    {MQ_MODEL_9,
     {
         {.gas_type = MQ_GAS_TYPE_LPG, .a = 1000.5, .b = -2.186},
         {.gas_type = MQ_GAS_TYPE_CH4, .a = 4269.6, .b = -2.648},
         {.gas_type = MQ_GAS_TYPE_CO, .a = 599.65, .b = -2.244},
     }},
    {MQ_MODEL_131,
     {
         {.gas_type = MQ_GAS_TYPE_NOX, .a = -462.43 , .b = -2.204},
         {.gas_type = MQ_GAS_TYPE_CL2, .a = 47.209, .b = -1.186},
         {.gas_type = MQ_GAS_TYPE_O3, .a = 23.943, .b = -1.11},
     }},
    {MQ_MODEL_135,
     {
         {.gas_type = MQ_GAS_TYPE_CO, .a = 605.18, .b = -3.937},
         {.gas_type = MQ_GAS_TYPE_ALCOHOL, .a = 77.255, .b = -3.18},
         {.gas_type = MQ_GAS_TYPE_CO2, .a = 110.47, .b = -2.862},
         {.gas_type = MQ_GAS_TYPE_TOLUENO, .a = 44.947, .b = -3.445},
         {.gas_type = MQ_GAS_TYPE_NH4, .a = 102.2, .b = -2.473},
         {.gas_type = MQ_GAS_TYPE_ACETONA, .a = 34.668, .b = -3.369},
     }},
    {MQ_MODEL_136,
     {
         {.gas_type = MQ_GAS_TYPE_H2S, .a = 36.737, .b = -3.536},
         {.gas_type = MQ_GAS_TYPE_NH4, .a = 98.551, .b = -2.475},
         {.gas_type = MQ_GAS_TYPE_CO, .a = 503.34, .b = -3.774},
     }},
    {MQ_MODEL_303A,
     {
         {.gas_type = MQ_GAS_TYPE_ISO_BUTANO, .a = 6.2144, .b = -2.894},
         {.gas_type = MQ_GAS_TYPE_HYDROGEN, .a = 4.1487, .b = -2.716},
         {.gas_type = MQ_GAS_TYPE_ETHANOL, .a = 3.4916, .b = -2.432},
     }},
    {MQ_MODEL_309A,
     {
         {.gas_type = MQ_GAS_TYPE_H2, .a = 1532.9, .b = -1.951},
         {.gas_type = MQ_GAS_TYPE_CH4, .a = 980.24, .b = -1.68},
         {.gas_type = MQ_GAS_TYPE_CO, .a = 1000000.0, .b = -4.01},
         {.gas_type = MQ_GAS_TYPE_ALCOHOL, .a = 473622, .b = -3.647},
     }},
};

}  // namespace mq
}  // namespace esphome