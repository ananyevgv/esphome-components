#include "esphome.h"

#include "cgAnem.h"

#ifdef ANEM_I2C_ADDR 
#undef ANEM_I2C_ADDR
#define ANEM_I2C_ADDR 0x11
#endif 

using namespace esphome;


class MycgAnem: public PollingComponent, public CustomAPIDevice {
  public: 
  Sensor * temperature_Sensor = new Sensor();
  Sensor * airConsumption_Sensor = new Sensor();
  Sensor * airflowRate_Sensor = new Sensor();  
  Sensor * ductArea_Sensor = new Sensor();
  Sensor * FirmwareVersion_Sensor = new Sensor();
  Sensor * MinAirFlowRate_Sensor = new Sensor(); 
  Sensor * MaxAirFlowRate_Sensor = new Sensor();
  
  BinarySensor * SensorStatus_BinarySensor = new BinarySensor();

  CG_Anem myself {
    ANEM_I2C_ADDR
  };

  MycgAnem(): PollingComponent(5000) {}

  void on_set_duct_area(float ductarea_) {
    myself.set_duct_area(ductarea_);
    ESP_LOGD("duct_area_", "Set to %d", ductarea_);
  }

  void on_resetMinMaxValues() {
    myself.resetMinMaxValues();
    ESP_LOGD("MinMax", "Reset");
  }

  void setup() override {
    myself.init();
    myself.set_duct_area(id(duct)); //  
    register_service( & MycgAnem::on_set_duct_area, "set_duct_area", {
      "ductarea_"
    });
    register_service( & MycgAnem::on_resetMinMaxValues, "reset_Min_Max_Values");
    ;
  }

  void update() override {
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
    MaxAirFlowRate_Sensor -> publish_state(MaxAirFlowRate);
    MinAirFlowRate_Sensor -> publish_state(MinAirFlowRate);
    
    
  }
};
