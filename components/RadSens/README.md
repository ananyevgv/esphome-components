ESPHome custom component sensor for Climateguard RadSens 1v2, 1v7, 2v7 + Dosimeter  ESPHome
==========
По мотивам 
https://github.com/med-lasers/Dosimeter_RadSens_NarodMon

Подключение
|ESP32            |RadSens          |
|-----------------|-----------------|
| GPIO21 | SDA to RadSens| 
| GPIO22 | SCL to RadSens|
| GPIO17 | pulse input from RadSens, + Buzzer| 
| GPIO2 | - Buzzer| 
| GPIO32 | + RadSens |
| GPIO0 | sleep|
| GPIO35|  wakeup|

<img src="https://github.com/ananyevgv/esphome-components/blob/main/components/RadSens/dosimeter.jpg" height="300" alt="Дозимер">

# ESPHome custom component sensor for Climateguard RadSens 1v2, 1v7, 2v7

Add to device config for climateguard/RadSens

```yaml
esphome:

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
globals:
  - id: sens
    type: float
    restore_value: no
    initial_value: '105' # sensitivity

```
## Sensor
```yaml
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
        
      - name: "Current impulse"
        accuracy_decimals: 0
        unit_of_measurement: imp
        state_class: measurement
        icon: mdi:pulse

      - name: "Max impulse"
        accuracy_decimals: 0
        unit_of_measurement: imp
        state_class: measurement
        icon: mdi:pulse

      - name: "Calibration Sensivity"
        state_class: measurement
        entity_category: diagnostic
        unit_of_measurement: "imp/μR"
        icon: mdi:account-wrench-outline 
```
## Binary sensor
```yaml
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
#  режим пониженного энергопотребления
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
