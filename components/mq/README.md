# ESPHome component MQ gaz sensor

основан на

https://github.com/nonameplum/esphome_devices/

https://github.com/miguel5612/MQSensorsLib
# Схема включения ESP8266-ESP32

<img src="https://raw.githubusercontent.com/miguel5612/MQSensorsLib_Docs/master/static/img/MQ_ESP8266.PNG" height="300" alt="MQ">




```yaml



external_components:
  source: github://ananyevgv/esphome-components@mq
  components: [mq]
  refresh: 0s

sensor:
  - platform: adc
    id: mq_adc
    pin: A0
    name: "MQ ADC Voltage"
    unit_of_measurement: "V"
    accuracy_decimals: 3
    #attenuation: auto  # ESPHome handles this
   # update_interval: 1s
    filters:
      - multiply: 3.3
      
  - platform: mq
    model: MQ4
    r0:  4.4
    adc_sensor: mq_adc  # Reference to ADC sensor
    rl: 10  # Load resistor in kOhm
    vr: 3.3  # Voltage resolution
    update_interval: 30s
    sensor_co:
      name: "Carbon Monoxide"
      device_class: carbon_monoxide
    sensor_lpg:
      name: "lpg"
    sensor_ch4:
      name: "ch4"
    sensor_smoke:
      name: "smoke"
    sensor_alcohol:
      name: "Alcohol"
```

Значения RS/R0 для чистого воздуха
Модель	RS/R0 (чистый воздух)

MQ2	9.83

MQ3	60.0

MQ4	4.4

MQ5	6.5

MQ6	10.0

MQ7	27.5

MQ8	70.0

MQ9	9.6

MQ131	15.0

MQ135	3.6

MQ136	3.6

MQ303A	1.0

MQ309A	11.0

# Поддерживаемые датчики и газы

# MQ-2 (Горючие газы и дым)
model: MQ2
сенсоры:
 sensor_h2, sensor_lpg, sensor_co, sensor_alcohol, sensor_propane
 
# MQ-3 (Алкоголь)
model: MQ3
Доступные сенсоры:
 sensor_lpg, sensor_ch4, sensor_co, sensor_alcohol, sensor_benzene, sensor_hexane
 
# MQ-4 (Природный газ)
model: MQ4
Доступные сенсоры:
 sensor_lpg, sensor_ch4, sensor_co, sensor_alcohol, sensor_smoke
 
# MQ-5 (Горючие газы)
model: MQ5
Доступные сенсоры:
 sensor_h2, sensor_lpg, sensor_ch4, sensor_co, sensor_alcohol
 
# MQ-6 (Сжиженный газ)
model: MQ6
 Доступные сенсоры:
 sensor_h2, sensor_lpg, sensor_ch4, sensor_co, sensor_alcohol
 
# MQ-7 (Угарный газ)
model: MQ7
Доступные сенсоры:
 sensor_h2, sensor_lpg, sensor_ch4, sensor_co, sensor_alcohol
 
# MQ-8 (Водород)
model: MQ8
Доступные сенсоры:
 sensor_h2, sensor_lpg, sensor_ch4, sensor_co, sensor_alcohol
 
# MQ-9 (Угарный газ и горючие газы)
model: MQ9
Доступные сенсоры:
 sensor_lpg, sensor_ch4, sensor_co
 
# MQ-131 (Озон)
model: MQ131
Доступные сенсоры:
 sensor_nox, sensor_cl2, sensor_o3
 
# MQ-135 (Качество воздуха)
model: MQ135
Доступные сенсоры:
 sensor_co, sensor_alcohol, sensor_co2, sensor_tolueno, sensor_nh4, sensor_acetona
 
# MQ-136 (Сероводород)
model: MQ136
Доступные сенсоры:
 sensor_h2s, sensor_nh4, sensor_co
 
# MQ-303A (Спирт)
model: MQ303A
Доступные сенсоры:
 sensor_iso_butano, sensor_hydrogen, sensor_ethanol
 
# MQ-309A (Водород и угарный газ)
model: MQ309A
Доступные сенсоры:
 sensor_h2, sensor_ch4, sensor_co, sensor_alcohol
    
Номинал RL (R2), значение RL в кОм  (!!!!!!!! на двух одинаковых датчиках номиналы резисторов могут быть разные 1кОм-120кОм !!!!!!!!)

<img src="https://static.insales-cdn.com/files/1/7780/30170724/original/mceclip8-1688735102483.jpg" height="300" alt="RL">

Значение RS/R0 (из спецификации вашего датчика) RS/R0 (Чистый воздух)

 <img src="https://raw.githubusercontent.com/miguel5612/MQSensorsLib_Docs/master/static/img/Graph_Explanation.jpeg" height="300" alt="R0">

https://www.yourduino.ru/blogs/blog/datchika-gaza-mq-7-slozhnosti-izmereniya-urovnya-ugarnogo-gaza

# примеры в sensor.yaml
