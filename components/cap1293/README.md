[![License][license-shield]][license]
[![ESPHome release][esphome-release-shield]][esphome-release]

[license-shield]: https://img.shields.io/static/v1?label=License&message=MIT&color=orange&logo=license
[license]: https://opensource.org/licenses/MIT
[esphome-release-shield]: https://img.shields.io/static/v1?label=ESPHome&message=2025.3&color=green&logo=esphome
[esphome-release]: https://GitHub.com/esphome/esphome/releases/


CAP1293 Capacitive Touch Sensor. 
# Example configuration entry

...yaml
cap1293:
  id: cap1293_component
  address: 0x28
  reset_pin: GPIOXX
  touch_threshold: 0x40
  allow_multiple_touches: true

binary_sensor:
  - platform: cap1293
    id: touch_key0
    channel: 0
    name: "Touch Key 0"

Configuration variables:
The configuration is made up of two parts: The central component, and individual Binary sensors per channel.

address (Optional, int): The I²C address of the sensor. Defaults to 0x29.

id (Optional, ID): Set the ID of this sensor.

reset_pin (Optional, Pin): Set the pin that is used to reset the CAP1293 board on boot.

touch_threshold (Optional, int): The touch threshold for all channels. This defines the sensitivity for touch detection.

0x01: Maximum sensitivity - Most sensitive to touch

0x03: Default sensitivity

0x04: Medium sensitivity (I used this sensitivity when being used through a 3mm sheet of plastic)

0x07: Minimum sensitivity - Least sensitive to touch

allow_multiple_touches (Optional, boolean): Whether to allow multitouch. Defaults to off.
