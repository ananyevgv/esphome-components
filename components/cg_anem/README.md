Обязательно выставить частоту шины!!!!   frequency: 10kHz   !!!!
На версиях прошивки < 1.0 значения min_air_flow_rate и max_air_flow_rate не вычисляются (нет алгоритма от производителя (не факт что он есть вообще), значение будет -1), бинарные сенсоры  вполне возможно будут позже и смена адреса... как разберусь как их написать

проверено на версиях прошивки 0.4, 0.5, 1.0


```
external_components:
  - source: github://ananyevgv/esphome-components/
    components: [ cg_anem ]
    refresh: 0s
i2c:
  frequency: 10kHz

sensor:
  - platform: cg_anem
    duct: 91.6 # 91.6 = расчитанное сечение воздуховодав см2  где стоит анемометр в метрах сантиметрах 122.71 для 125
    air_consumption:
      name: "Air consumption"
      id: air
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
    update_interval: 1s


  - platform: total_daily_energy
    name: 'Total Daily Air'
    power_id: air
    unit_of_measurement: 'm³'
    state_class: total_increasing
    device_class: volume
    accuracy_decimals: 3

time:
  - platform: sntp
    id: sntp_time
    servers:
     - 0.pool.ntp.org


```
