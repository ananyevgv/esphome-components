## Description

ESPHome custom component sensor for Climateguard CG-Anem

```yaml
esphome:
  ...
  libraries:
   - Wire
   - "climateguard/ClimateGuard CG Anem"   
  includes:
   - my_components/cgAnem/_cg_Anem.h

 i2c:

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
        accuracy_decimals: 0
      - name: "FirmwareVersion"
        accuracy_decimals: 0
      - name: "MinAirFlowRate"
        accuracy_decimals: 1
      - name: "MaxAirFlowRate"
        accuracy_decimals: 1

binary_sensor:
  - platform: custom
    lambda: |-
      auto cg_anem = new MycgAnem();
      App.register_component(cg_anem);
      return {cg_anem->SensorStatus_BinarySensor};
    binary_sensors:
      - name: "SensorStatus"

...

## Services

HA service call to set device sensivity:

```yaml
service: esphome.name_set_duct_area 
data:
  duct_area: "100"
```

## References

[Official CG-Anem library by [ClimateGuard](https://github.com/climateguard/CG-Anem])

[ESPHome Documentation](https://esphome.io/index.html)
