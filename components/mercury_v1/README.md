#-------------------------------------------
# uart
#-------------------------------------------
uart:
  id: uart_mercury
  baud_rate: 9600
  data_bits: 8
  parity: NONE
  stop_bits: 1
  tx_pin: 1
  rx_pin: 3
  debug:
    direction: BOTH
    dummy_receiver: false
    after:
      bytes: 60
    sequence:
      - lambda: UARTDebug::log_hex(direction, bytes, ':');
#-------------------------------------------
# sensor
#-------------------------------------------
sensor:
  - platform: total_daily_energy
    name: "Total Daily Energy"
    icon: "mdi:current-ac"
    power_id: "power"
    method: "trapezoid"
  - platform: mercury_v1
    address: 123456
    update_interval: 60s
    voltage:
      name: "Voltage"
      icon: "mdi:flash"
    amperage:
      name: "Amperage"
      icon: "mdi:flash"
    power:
      name: "Power"
      id: "power"
      icon: "mdi:flash"
    frequency:
      name: "Frequency"
      icon: "mdi:flash"
    tariff1:
      name: "Tariff 1"
      icon: "mdi:flash"
    tariff2:
      name: "Tariff 2"
      icon: "mdi:flash"
    tariff3:
      name: "Tariff 3"
      icon: "mdi:flash"
    tariff4:
      name: "Tariff 4"
      icon: "mdi:flash"
    tariffs_total:
      name: "Tariffs total"
      icon: "mdi:flash"

