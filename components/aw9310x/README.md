!!!test!!!

``` yaml
aw9310x:
  address: 0x12  # опционально, по умолчанию 0x12
 # interrupt_pin: GPIO23  # если не указать, будет работать в опросном режиме
  threshold: 50000
  id: aw9310x_sensor
  
binary_sensor:
  # Канал 0 
  - platform: aw9310x
    aw9310x_id: aw9310x_sensor  # автоматически создается, можно не указывать
    channel: 0
    name: "Touch Channel 0"
    id: left_touch

  # Канал 1
  - platform: aw9310x
    aw9310x_id: aw9310x_sensor  # автоматически создается, можно не указывать
    channel: 1
    name: "Touch Channel "
    id: touch

  # Канал 2
  - platform: aw9310x
    aw9310x_id: aw9310x_sensor  # автоматически создается, можно не указывать
    channel: 2
    name: "Touch Channel 2"
    id: right_touch
```
