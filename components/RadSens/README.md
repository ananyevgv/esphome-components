## Description

ESPHome custom component sensor for Climateguard RadSens 1v2, 1v7, 2v7

## Deployment

First of all get the code:
```bash
git clone https://github.com/maaad/RadSens1v2 /usr/share/hassio/homeassistant/esphome/RadSens1v2
```
Add to device config for climateguard/RadSens
```yaml
esphome:
  ...
 libraries:
   - Wire
   - "climateguard/ClimateGuard RadSens"
 includes:
   - RadSens1v2/_CG_RadSens.h
  on_boot:
    then:
 #     - delay: 2s
      - switch.turn_on: hvg
      - switch.turn_on: led
 i2c:

...

sensor:
  - platform: custom
    lambda: |-
      auto rad_sens = new MyRadSens();
      App.register_component(rad_sens);
      return {rad_sens->IntensityDynamic_Sensor,rad_sens->IntensityStatic_Sensor, rad_sens->Firmware_Sensor, rad_sens->CurrentCPM_Sensor, rad_sens->MaxCPM_Sensor, rad_sens->Sensivity_Sensor};
    sensors:
      - name: "Dynamic intensity"
        id: dynamic_intensity
        accuracy_decimals: 1
        unit_of_measurement: μR/h
        state_class: measurement
        icon: mdi:radioactive

      - name: "Static intensity"
        accuracy_decimals: 1
        unit_of_measurement: μR/h
        state_class: measurement
        icon: mdi:radioactive

      - name: "Firmware"
        accuracy_decimals: 0
        icon: mdi:folder-arrow-up-outline
        
      - name: "Current CPM"
        accuracy_decimals: 1
        unit_of_measurement: CPM
        state_class: measurement
        icon: mdi:radioactive
      - name: "Max CPM"
        accuracy_decimals: 1
        unit_of_measurement: CPM
        state_class: measurement
        icon: mdi:radioactive
      - name: "Device Sensivity"
        id: sensivity
        state_class: measurement
        entity_category: diagnostic
        

binary_sensor:
  - platform: custom
    lambda: |-
      auto rad_sens = new MyRadSens();
      App.register_component(rad_sens);
      return {rad_sens->HVGenerator_BinarySensor, rad_sens->LedState_BinarySensor};
    binary_sensors:
      - name: "HVGenerator"
        icon: mdi:flash-triangle
      - name: "LedState"
        icon: mdi:led-outline
```

## Switch

```yaml
switch:
  - platform: custom
    lambda: |-
      auto rad_sens_switch = new MyRadSens_Switch();
      App.register_component(rad_sens_switch);
      return {rad_sens_switch->lpmode_switch, rad_sens_switch->hv_generator_switch, rad_sens_switch->led_indicator_switch};

    switches:
      - name: "lpmode"
        icon: mdi:lock-clock  

      - name: "High Voltage Generator"
        icon: mdi:flash-triangle-outline
        id: hvg
      - name: "LED Indicator"
        icon: mdi:led-outline
        id: led
```


## Services

HA service call to set device sensivity:
```yaml
service: esphome.name_set_sensivity 
data:
  sensivity: "105"
```

Reset Max CPM Counter 

```yaml
service: esphome.name_reset_cpm
data: {}
```

HVgenerator enabled

```yaml
service: esphome.name_set_generator
data:
  generator: false #true

```

## Known issues

#### RadSens 1v5
[1v5 boards workaround](https://github.com/maaad/RadSens1v2/issues/3#issuecomment-1289578773)



## References

[Official RadSens library by ClimateGuard](https://github.com/climateguard/RadSens)

[ESPHome Documentation](https://esphome.io/index.html)
