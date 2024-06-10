# liligo t-display измерение напряжения и уровня заряда батареи

```yaml
sensor:
  - platform: lilygo_t_battery
    update_interval: 5s
    voltage:
      name: "Battery Voltage"
      id: vbatt
    bus_voltage:
      name: "Bus Voltage"
    level:
      name: "Battery level"
      id: batt
```
<img src="https://github.com/ananyevgv/esphome-components/edit/main/components/lilygo_t_battery/bat.jpg" height="300" alt="liligo">
