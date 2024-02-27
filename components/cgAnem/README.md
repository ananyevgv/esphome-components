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
globals:
  - id: duct
    type: float
    restore_value: no
    initial_value: '100'  # Задаём площадь поперечного площадь воздуховода см^2
```

```yaml
sensor:
  - platform: custom
    lambda: |-
      auto cg_anem = new MycgAnem();
      App.register_component(cg_anem);
      return {cg_anem->temperature_Sensor, cg_anem->airConsumption_Sensor, cg_anem->airflowRate_Sensor, cg_anem->ductArea_Sensor, cg_anem->FirmwareVersion_Sensor, cg_anem->MinAirFlowRate_Sensor, cg_anem->MaxAirFlowRate_Sensor};
    sensors:
      - name: "temperature"
        accuracy_decimals: 1
        state_class: "measurement"
        device_class: temperature
        unit_of_measurement: "°C"
      - name: "airConsumption"
        accuracy_decimals: 1
        state_class: "measurement"
        device_class: volume
        unit_of_measurement: "m³/h"
      - name: "airflowRate"
        accuracy_decimals: 1
        state_class: "measurement"
        device_class: wind_speed
        unit_of_measurement: "m/s"
      - name: "ductArea"
        accuracy_decimals: 0
        device_class: volume
        unit_of_measurement: "cm²"
      - name: "FirmwareVersion"
        accuracy_decimals: 2
      - name: "MinAirFlowRate"
        accuracy_decimals: 1
        state_class: "measurement"
        device_class: wind_speed
        unit_of_measurement: "m/s"
      - name: "MaxAirFlowRate"
        accuracy_decimals: 1
        state_class: "measurement"
        device_class: wind_speed
        unit_of_measurement: "m/s"
```

```yaml
binary_sensor:
  - platform: custom
    lambda: |-
      auto cg_anem = new MycgAnem();
      App.register_component(cg_anem);
      return {cg_anem->SensorStatus_BinarySensor};
    binary_sensors:
      - name: "SensorStatus"
```

## Services

HA service call to set set_duct_area:

```yaml
service: esphome.name_set_duct_area 
data:
  duct_area: "100"

service: esphome.name_resetMinMaxValues
data:
  reset_Min_Max: ""
```

## References

[Official CG-Anem library by ClimateGuard](https://github.com/climateguard/CG-Anem)

[ESPHome Documentation](https://esphome.io/index.html)
