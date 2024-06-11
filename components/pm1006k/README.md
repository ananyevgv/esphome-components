# ESPHome component PM1006k


# ESPHome component PM1006k с родным контроллером
основан на PM1006
```yaml

uart:
  rx_pin: 1 #8 ножка контроллера
  baud_rate: 9600

external_components:
  source: github://ananyevgv/esphome-components
  components: [pm1006k]
  refresh: 0s

  sensor:
    - platform: pm1006k
      pm_1_0:   
        name: "PM 1.0"
        id: "pm1"
      pm_2_5:
        name: "PM 2.5"
        id: "pm2"
      pm_10_0:
        name: "PM 10"
        id: "pm10"

```
# ESPHome component PM1006k без родного контроллера


Если вы запускаете PM1006 (2,5 мкм) или PM1006K (1, 2,5, 10 мкм) без родного микроконтроллера, вам необходимо отправить последовательную команду в течение первых 5 секунд после подачи питания на датчик. В противном случае датчик переключится в режим PWM и не будет отвечать на запросы UART. 

```yaml
esphome:
  name: "${name}"
  on_boot:
    priority: 240
    then:
      - uart.write:
          id: PM1006k
          data: [0x11, 0x02, 0x0B, 0x01, 0xE1]
uart:
  tx_pin: 3 #1 ножка контроллера
  rx_pin: 1 #8 ножка контроллера
  baud_rate: 9600
  id: PM1006k

external_components:
  source: github://ananyevgv/esphome-components
  components: [pm1006k]
  refresh: 0s

  sensor:
    - platform: pm1006k
      pm_1_0:   
        name: "PM 1.0"
        id: "pm1"
      pm_2_5:
        name: "PM 2.5"
        id: "pm2"
      pm_10_0:
        name: "PM 10"
        id: "pm10"
      update_interval: 30s
```
