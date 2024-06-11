#  t-display измерение напряжения батареи и уровня заряда 

```yaml
sensor:
  - platform: lilygo_t_battery
    update_interval: 5s
    voltage:
      name: "Battery Voltage"
      id: vbatt
    bus_voltage:
      name: "Bus Voltage"
      id: vbus
    level:
      name: "Battery level"
      id: batt

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
