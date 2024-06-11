# ESPHome component PM1006k & MQ gaz sensor & Climateguard RadSens & Climateguard cgAnem  & Ttgo t-display esp32 battery


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
# Ikea vindriktning

https://github.com/ananyevgv/esphome-vindriktning-ikea/

# yaml
https://github.com/ananyevgv/esphome-vindriktning-ikea/blob/main/ikea-circle-new.yaml

# ESPHome component MQ gaz sensor

основан на

https://github.com/nonameplum/esphome_devices/

https://github.com/miguel5612/MQSensorsLib

```yaml
external_components:
  source: github://ananyevgv/esphome-components
  components: [mq]
  refresh: 0s

sensor:
  - platform: mq
    model: MQ9
    pin: A0
    update_interval: 2s
    sensor_lpg:
      name: Sensor LPG
    sensor_ch4:
      name: Sensor CH4
    sensor_co:
      name: Sensor CO
```

model: MQ2, MQ3, MQ4, MQ5, MQ6, MQ7, MQ8,MQ9, MQ131, MQ135, MQ136, MQ303A, MQ309A

    "MQ2": [H2, LPG, CO, ALCOHOL, PROPANE],
    
    "MQ3": LPG, CH4, CO, ALCOHOL, BENZENE, HEXANE],
    
    "MQ4": [LPG, CH4,CO, ALCOHOL, SMOKE],
    
    "MQ5": [H2, LPG,CH4, CO, ALCOHOL],
    
    "MQ6": [H2, LPG,CH4, CO, ALCOHOL],
    
    "MQ7": [H2, LPG,CH4, CO, ALCOHOL],
    
    "MQ8": [H2, LPG,CH4, CO, ALCOHOL],
    
    "MQ9": [LPG, CH4, CO],
    
    "MQ131": [NOX, CL2, O3],
    
    "MQ135": [CO, ALCOHOL, CO2, TOLUENO, NH4, ACETONA],
    
    "MQ136": [H2S, NH4, CO],
    
    "MQ303A": [ISO_BUTANO, CHYDROGEN, ETHANOL],
    
    "MQ309A": [H2, CH4, CO, ALCOHOL],


## RadSens

ESPHome custom component sensor for Climateguard RadSens 1v2, 1v7, 2v7

https://github.com/ananyevgv/esphome-components/tree/main/components/RadSens


## CG-Anem

ESPHome custom component sensor for Climateguard CG-Anem

https://github.com/ananyevgv/esphome-components/tree/main/components/cgAnem

## Ttgo t-display esp32 battery

ESPHome custom component Ttgo t-display esp32 battery

https://github.com/ananyevgv/esphome-components/tree/main/components/lilygo_t_battery

Dosimeter  ESPHome
==========
По мотивам 
https://github.com/med-lasers/Dosimeter_RadSens_NarodMon

[https://github.com/ananyevgv/esphome-components/components/RadSens/](https://github.com/ananyevgv/esphome-components/tree/main/components/cgAnem)

# yaml
https://github.com/ananyevgv/esphome-components/blob/main/components/RadSens/dosimeter.yaml
