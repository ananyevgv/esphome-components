[![License][license-shield]][license]
[![ESPHome release][esphome-release-shield]][esphome-release]

[license-shield]: https://img.shields.io/static/v1?label=License&message=MIT&color=orange&logo=license
[license]: https://opensource.org/licenses/MIT
[esphome-release-shield]: https://img.shields.io/static/v1?label=ESPHome&message=2025.3&color=green&logo=esphome
[esphome-release]: https://GitHub.com/esphome/esphome/releases/


# Интегрированные устройства UJIN в ESPHome


# [Lume Luxe L.te M1](https://github.com/NagibinA/esphome-ujin-1/blob/7df921a225203874b50efc2a2f6a108fb8cb2985/Lume%20Luxe_L.te%20M1/lume%20luxe%20L.te%20M1.yaml)

<img src="https://github.com/NagibinA/esphome-ujin-1/blob/5f76cadf9561d7a832881ac16208bb044533d744/Lume%20Luxe_L.te%20M1/images/Luxe_Lte%20M1_1.jpg" height="300" alt="Lume L.te lite"> 

В этом выключателе, ипользуется прямое управление диммером (с отслеживанием нуля).

В прошивке выключателя реализовано:
1. Диммирование двух каналов.

      При включенном диммировании:

      • Однократное (короткое) нажатие включает или выключает лампу с установленной (сохраненной) яркостью.

      • Удерживая сенсорную панель (длинное нажатие), плавно увеличивает или уменьшает яркость лампы. Это прекращается, когда лампа полностью включается или полностью выключается.

      • Отпустив, а затем снова нажав удерживая сенсорную панель, измениться направление, то есть если свет становился тусклее, то, отпустив и снова нажав, он будет ярче.

2. Подключение внешних выключателей в режиме "выключатель"
3. Подсветка сенсорных кнопок адресными светодиодами с выбором цвета и яркости состояния (нажата, включено, выключено)
4. Реализован режим "Ночник" тремя вертикальными, адресными светодиодами, с выбором яркости и цвета
5. В режиме подключения к Wi-Fi, вертикальные светодиоды мигают до подключения к сети
6. Реализован датчик шума с выбором действия по сработке
7. Реализован датчик движения с выбором действия по сработке
8. Подключен датчик освещенности
9. Подключен датчик температуры и влажности
10. Реализован приемник IR  с выбором бренда и отображением принятого кода
11. Подключен передатчик IR
12. Реализована работа ZigBee координатора ZHA

    


# todo: 
      
      1. Отключение диммирования на ходу
      2. Ограничение включения света по датчику освещенности
      3. BLE

# [Lume wifi/BLE/IR/CO2]

<img src="https://github.com/ananyevgv/esphome-ujin/blob/main/image%2Flumi%20co2.jpg" height="300" alt="Lume CO2 lite">

В этом выключателе, управление диммером происходит по цифровому интерфейсу.

# todo: 

      1. Управление диммером
      2. BLE (мало памяти необходимо замена flash)
      3. Отключение диммирования на ходу
      4. Ограничение включения света по датчику освещенности.


# [Connect din](https://github.com/NagibinA/esphome-ujin-1/blob/f9e8dd99a58445ae1349fafaf5a36c6e7d8ec50f/Connect-din%20Wi-Fi/rele-ujin.yaml)

<img src="https://github.com/NagibinA/esphome-ujin-1/blob/65961438cc7a0ce8dfc24b3891ebbf458555e8bc/Connect-din%20Wi-Fi/images/connect-din_wi-fi.jpg" height="300" alt="Lume relay">

 
# [Aqua Sense](https://github.com/NagibinA/esphome-ujin-1/blob/02668abdb31d5efbcec2e42ae0b62cf414c559d0/Aqua-Sense%20BLE/leak-sensor.yaml)

<img src="https://github.com/NagibinA/esphome-ujin-1/blob/9f9ec3743ae0b0ab61f9c3933ee5707e63ab953d/Aqua-Sense%20BLE/images/Aqua-Sense%20BLE.jpg" height="300" alt="Lume leak sensor lite">


# [Heat Wi-Fi]

<img src="https://github.com/NagibinA/esphome-ujin-1/blob/382708609ab669d9a017be2ed7dc692cb6605322/Heat%20Wi-Fi/images/heat_1.jpg" height="300" alt="Lume leak sensor lite">


# todo: 

      1. Подключение сенсорных кнопок
      2. Подсветка режимов работы и текущего состояния термостата, адресными светодиодами

