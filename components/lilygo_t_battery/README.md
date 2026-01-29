# Ttgo t-display esp32 измерение напряжения батареи и уровня заряда 

```yaml
sensor:
  - platform: adc
    pin: GPIO34
    name: "ADC Raw Voltage"
    id: adc_raw
    update_interval: 1s
    attenuation: 12db  #
    unit_of_measurement: "V"
    accuracy_decimals: 3
    filters:
      - sliding_window_moving_average:
          window_size: 10
          send_every: 1
  

  - platform: lilygo_t_battery
    id: battery_monitor
    sensor: adc_raw
    enable_pin: GPIO14
    update_interval: 30s
    voltage_divider: 6 # 7.26 # коэффициент делителя напряжения Коэффициент делителя = (R1 + R2) / R2 = 120K / 20K = 6
    
    voltage:
      name: "Battery Voltage"
      id: battery_voltage
      accuracy_decimals: 2
      
    bus_voltage:
      name: "USB Voltage"
      id: usb_voltage
      accuracy_decimals: 2
      
    level:
      name: "Battery Level"
      id: battery_level
      accuracy_decimals: 0

binary_sensor:
  - platform: template
    name: "Battery Charging"
    device_class: battery_charging
    lambda: |-
      if (id(usb_voltage).has_state() and id(usb_voltage).state > 4.2) {
        return true;
      } else {
        return false;
      }
```
<img src="https://github.com/ananyevgv/esphome-components/blob/main/components/lilygo_t_battery/bat.jpg" height="300" alt="liligo">
