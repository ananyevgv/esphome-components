#include "esphome/core/log.h"
#include "anem.h"

namespace esphome {
namespace empty_i2c_sensor {

static const char *TAG = "empty_i2c_sensor.sensor";

void EmptyI2CSensor::setup(){
  void on_set_duct_area(float ductarea_) {
    myself.set_duct_area(ductarea_);
    ESP_LOGD("duct_area_", "Set to %d", ductarea_);
  }    
}

void EmptyI2CSensor::update(){
    myself.data_update();
    float temperature = myself.getTemperature();
    float ductArea =  myself.ductArea;
    float airflowRate = myself.getAirflowRate();
    float airConsumption = myself.airConsumption;
    float FirmwareVersion = myself.getFirmwareVersion();;
    float MaxAirFlowRate = myself.getMaxAirFlowRate();
    float MinAirFlowRate = myself.getMinAirFlowRate();
    bool SensorStatus = myself.getSensorStatus();
    
    SensorStatus_BinarySensor ->  publish_state(SensorStatus);

    if (FirmwareVersion != 0) {
      FirmwareVersion_Sensor -> publish_state(FirmwareVersion);
    }
    temperature_Sensor -> publish_state(temperature);
    airflowRate_Sensor -> publish_state(airflowRate);
    airConsumption_Sensor -> publish_state(airConsumption);
    ductArea_Sensor -> publish_state(ductArea);
    MaxAirFlowRate_Sensor -> publish_state(MaxAirFlowRate);
    MinAirFlowRate_Sensor -> publish_state(MinAirFlowRate);
    
}

void EmptyI2CSensor::dump_config(){

}

}  // namespace EmptyI2CSensor
}  // namespace esphome
