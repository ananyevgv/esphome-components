# liligo t-display измерение напряжения и уровняя заряда батареи

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