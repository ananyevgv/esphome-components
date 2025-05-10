[![License][license-shield]][license]
[![ESPHome release][esphome-release-shield]][esphome-release]

[license-shield]: https://img.shields.io/static/v1?label=License&message=MIT&color=orange&logo=license
[license]: https://opensource.org/licenses/MIT
[esphome-release-shield]: https://img.shields.io/static/v1?label=ESPHome&message=2025.3&color=green&logo=esphome
[esphome-release]: https://GitHub.com/esphome/esphome/releases/


CAP1293 Capacitive Touch Sensor. 
# Example configuration entry

```
cap1293:
  id: cap1293_component
  address: 0x28
  reset_pin: GPIOXX
  touch_threshold: 0x03
  allow_multiple_touches: true

binary_sensor:
  - platform: cap1293
    id: touch_key0
    channel: 0
    name: "Touch Key 0"
```

Configuration variables:
The configuration is made up of two parts: The central component, and individual Binary sensors per channel.

address (Optional, int): The I²C address of the sensor. Defaults to 0x28.

id (Optional, ID): Set the ID of this sensor.

reset_pin (Optional, Pin): Set the pin that is used to reset the CAP1293 board on boot.

Parameters:    

| Sensitivity level   | Defined name     | Value | 
| ------------------- | ---------------- | ----- |
| Highest sensitivity | SENSITIVITY_128X | 0x00 |
| High sensitivity | SENSITIVITY_64X | 0x01 |
| Higher sensitivity | SENSITIVITY_32X | 0x02 |
| Medium sensitivity | SENSITIVITY_16X | 0x03 |
| Lower sensitivity | SENSITIVITY_8X | 0x04 | 
| Low sensitivity | SENSITIVITY_4X | 0x05 |
| Low sensitivity | SENSITIVITY_2X | 0x06 |
| Lowest sensitivity | SENSITIVITY_1X | 0x07 |

