Dosimeter  ESPHome for Climateguard RadSens 1v2, 1v7, 2v7 +
==========
По мотивам 
https://github.com/med-lasers/Dosimeter_RadSens_NarodMon

Подключение
|ESP32            |RadSens          |
|-----------------|-----------------|
| GPIO21 | SDA to RadSens| 
| GPIO22 | SCL to RadSens|
| GPIO17 | pulse input from RadSens, + Buzzer| 
| GPIO2 | - Buzzer| 
| GPIO32 | + RadSens |
| GPIO0 | sleep|
| GPIO35|  wakeup|

<img src="https://github.com/ananyevgv/esphome-components/blob/main/components/RadSens/dosimeter.jpg" height="300" alt="Дозимер">

# ESPHome custom component sensor for Climateguard RadSens 1v2, 1v7, 2v7



## Known issues

#### RadSens 1v5
[1v5 boards workaround](https://github.com/maaad/RadSens1v2/issues/3#issuecomment-1289578773)



## References

[Official RadSens library by ClimateGuard](https://github.com/climateguard/RadSens)

[ESPHome Documentation](https://esphome.io/index.html)
