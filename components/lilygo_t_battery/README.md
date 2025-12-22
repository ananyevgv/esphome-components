# Ttgo t-display esp32 измерение напряжения батареи и уровня заряда 

```yaml
sensor:
  - platform: adc
    pin: 34
    id: adc_34   
    attenuation: auto

  - platform: lilygo_t_battery
    update_interval: 5s
    voltage:
      name: "${name} battery Voltage"
      id: vbatt
    bus_voltage:
      name: "${name} bus Voltage"
      id: vbus
    level:
      name: "${name} battery level"
      id: batt
    enable_pin: 14
    sensor: adc_34

binary_sensor:
  - platform: template
    name: "charge"
    device_class: battery_charging
    lambda: |-
      if (id(vbus).state > 0) {
        return true;
      } else {
        return false;
      }

```
<img src="https://github.com/ananyevgv/esphome-components/blob/main/components/lilygo_t_battery/bat.jpg" height="300" alt="liligo">
