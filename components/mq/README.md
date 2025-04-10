# ESPHome component MQ gaz sensor

основан на

https://github.com/nonameplum/esphome_devices/

https://github.com/miguel5612/MQSensorsLib
# Схема включения ESP8266-ESP32

<img src="https://raw.githubusercontent.com/miguel5612/MQSensorsLib_Docs/master/static/img/MQ_ESP8266.PNG" height="300" alt="MQ">

```yaml
external_components:
  source: github://ananyevgv/esphome-components
  components: [mq]
  refresh: 0s

sensor:
  - platform: mq
    model: MQ9
    r0: 9.6 # из спецификации вашего датчика) RS/R0 (Чистый воздух)
    rl: 10 # Номинал R2 (RL) в кОм
    pin: A0
    update_interval: 2s
    sensor_lpg:
      name: Sensor LPG
    sensor_ch4:
      name: Sensor CH4
    sensor_co:
      name: Sensor CO
```

# Набор сенсоров в зависимости от датчика:
model: MQ2, MQ3, MQ4, MQ5, MQ6, MQ7, MQ8,MQ9, MQ131, MQ135, MQ136, MQ303A, MQ309A

    "MQ2": [H2, LPG, CO, ALCOHOL, PROPANE],R0 = 9.83
    
    "MQ3": LPG, CH4, CO, ALCOHOL, BENZENE, HEXANE],R0 = 60 
    
    "MQ4": [LPG, CH4,CO, ALCOHOL, SMOKE],R0 = 4.4
    
    "MQ5": [H2, LPG,CH4, CO, ALCOHOL],R0 = 6.5
    
    "MQ6": [H2, LPG,CH4, CO, ALCOHOL],R0 = 10 
    
    "MQ7": [H2, LPG,CH4, CO, ALCOHOL],R0 = 27.5
    
    "MQ8": [H2, LPG,CH4, CO, ALCOHOL],R0 = 70
    
    "MQ9": [LPG, CH4, CO],R0 = 9.6
    
    "MQ131": [NOX, CL2, O3],R0 = 15 
    
    "MQ135": [CO, ALCOHOL, CO2, TOLUENO, NH4, ACETONA],R0 = 3.6 
    
    "MQ136": [H2S, NH4, CO], R0 = 3.6 
    
    "MQ303A": [ISO_BUTANO, CHYDROGEN, ETHANOL],R0 = 1
    
    "MQ309A": [H2, CH4, CO, ALCOHOL],R0 = 11


    
Номинал RL (R2), значение RL в кОм

<img src="https://static.insales-cdn.com/files/1/7780/30170724/original/mceclip8-1688735102483.jpg" height="300" alt="RL">

Значение RS/R0 (из спецификации вашего датчика) RS/R0 (Чистый воздух)

 <img src="https://raw.githubusercontent.com/miguel5612/MQSensorsLib_Docs/master/static/img/Graph_Explanation.jpeg" height="300" alt="R0">

https://www.yourduino.ru/blogs/blog/datchika-gaza-mq-7-slozhnosti-izmereniya-urovnya-ugarnogo-gaza

# примеры в sensor.yaml
