## Description

ESPHome custom component sensor for Climateguard 




```yaml
esphome:
  ...
  libraries:
   - Wire
   - "climateguard/ClimateGuard CG Anem"   
  includes:
   - my_components/cgAnem/_cg_Anem.h

 i2c:

...
sensor:
  - platform: custom
    lambda: |-
      auto cg_anem = new MycgAnem();
      App.register_component(cg_anem);
      return {cg_anem->temperature_Sensor, cg_anem->airConsumption_Sensor, cg_anem->airflowRate_Sensor, cg_anem->ductArea_Sensor, cg_anem->FirmwareVersion_Sensor, cg_anem->MinAirFlowRate_Sensor, cg_anem->MaxAirFlowRate_Sensor};
    sensors:
      - name: "temperature"
        accuracy_decimals: 1
      - name: "airConsumption"
        accuracy_decimals: 1
      - name: "airflowRate"
        accuracy_decimals: 1
      - name: "ductArea"
        accuracy_decimals: 1
      - name: "FirmwareVersion"
        accuracy_decimals: 1
      - name: "MinAirFlowRate"
        accuracy_decimals: 1
      - name: "MaxAirFlowRate"
        accuracy_decimals: 1
        




## Known issues

#### RadSens 1v5
[1v5 boards workaround](https://github.com/maaad/RadSens1v2/issues/3#issuecomment-1289578773)



## References

[Official RadSens library by [ClimateGuard](https://github.com/climateguard/CG-Anem])

[ESPHome Documentation](https://esphome.io/index.html)