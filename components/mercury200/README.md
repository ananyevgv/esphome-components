uart:
  tx_pin: 1
  rx_pin: 3
  id: uart_for_mercury
  baud_rate: 9600
  data_bits: 8
  parity: NONE
  stop_bits: 1
  
mercury200:
  id: mercury_id
  address:  76527317
  uart_id: uart_for_mercury
  # dir_pin: 5
  all_commands: true
  startup_delay: 20s
  voltage: Voltage
  current: Current
  power: Power
  energy1: Energy1
  energy2: Energy2
  energy3: Energy3
  energy4: Energy4
  battery_voltage: Battery
  error: Error
