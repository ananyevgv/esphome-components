
На версиях прошивки < 1.0 значения min_air_flow_rate и max_air_flow_rate не вычисляются (нет алгоритма от производителя (не факт что он есть вообще), значение будет -1), бинарные сенсоры  вполне возможно будут позже и смена адреса... как разберусь как их написать

проверено на версиях прошивки 0.4, 0.5, 1.0


```
external_components:
  - source: github://ananyevgv/esphome-components/
    components: [ cg_anem ]
    refresh: 0s
i2c:
  frequency: 100kHz

i2c:
  sda: D1
  scl: D2
  frequency: 100kHz  # I2C_FREQ из официальной библиотеки


sensor:
  - platform: cg_anem
    address: 0x11
    diameter: "105 mm"  # диаметр в мм
    update_interval: 10s
    
   # enable_sleep: true
    ambient_temperature:
      name: "Ambient Temperature"
      id: ambient_temp
      filters:
        - sliding_window_moving_average:
            window_size: 5
            send_every: 1
    hotend_temperature:
      name: "Hotend Temperature"
      id: hotend_temp
    temperature_difference:
      name: "Temperature Difference (dT)"
      id: temp_diff
      icon: "mdi:thermometer-lines"
    air_flow_rate:
      name: "Air Flow Rate"
      id: airflow_rate
      unit_of_measurement: "m/s"
    min_air_flow_rate:
      name: "Min Air Flow Rate"
      id: min_airflow_rate
    max_air_flow_rate:
      name: "Max Air Flow Rate"
      id: max_airflow_rate
    heat_power:
      name: "Heater Power"
      id: heater_power
      unit_of_measurement: "W"
    supply_voltage:
      name: "Supply Voltage"
      id: supply_voltage
      unit_of_measurement: "V"
    air_consumption:
      name: "Air Consumption"
      id: air_consumption
      unit_of_measurement: "m³/h"
    firmware_version:
      name: "Firmware Version"
    status_ov:
      name: "OVERVOLTAGE"
    status_wdt:
      name: "WATCHDOG TIMER"
    status_incorrect_taring:
      name: "Incorrect Taring"
    status_incorrect_taring_range:
      name: "Incorrect Taring Range"


  - platform: total_daily_energy
    name: 'Total Daily Air'
    power_id: air_consumption
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

# Для версий прошивки < 1.0
```
sensor:
  - platform: copy
    source_id: flow_rate
    name: "Min air flow rate"
    filters:
      - min:
          window_size: 10
          send_every: 4
  - platform: copy
    source_id: flow_rate
    name: "Max air flow rate"
    filters:
      - max:
          window_size: 10
          send_every: 4
```
