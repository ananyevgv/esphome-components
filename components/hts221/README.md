[![License][license-shield]][license]
[![ESPHome release][esphome-release-shield]][esphome-release]

[license-shield]: https://img.shields.io/static/v1?label=License&message=MIT&color=orange&logo=license
[license]: https://opensource.org/licenses/MIT
[esphome-release-shield]: https://img.shields.io/static/v1?label=ESPHome&message=2025.3&color=green&logo=esphome
[esphome-release]: https://GitHub.com/esphome/esphome/releases/


hts221 temperature & Humidity Sensor. 
# Example configuration entry

```
#-------------------------------------------
# SENSOR HTS221
#-------------------------------------------
sensor:
  - platform: hts221
    temperature:
      name: "${name} temperature"
      id: ${id_hts221_t}
      icon: mdi:thermometer
    humidity:
      name: "${name} humidity"
      id: ${id_hts221_h}
      icon: mdi:water-percent
    update_interval: 10s
    address: 0x5F

  - platform: absolute_humidity
    name: "${name} Absolute Humidity"
    temperature: ${id_hts221_t}
    humidity: ${id_hts221_h}   
    icon: mdi:water-outline
```




