Example usage

```
external_components:
  - source: github://ananyevgv/esphome-components/
    components: [ cg_anem ]
    refresh: 0s
i2c:
  frequency: 10kHz

sensor:
- platform: cg_anem
  ambient_temperature:
    name: "Ambient temperature"
  hotend_temperature:
    name: "Hotend temperature"
  heat_power:
    name: "Heat power"
  air_flow_rate:
    name: "Air flow rate"
  firmware_version:
    name: "Firmware version"
  min_air_flow_rate:
    name: "Min air flow rate"
  max_air_flow_rate:
    name: "Max air flow rate"
  address: 0x11
  update_interval: 10s


```
