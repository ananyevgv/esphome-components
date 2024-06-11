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
