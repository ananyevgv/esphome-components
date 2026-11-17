# 📦 ESPHome Components & Projects

[![License][license-shield]][license]
[![ESPHome release][esphome-release-shield]][esphome-release]

[license-shield]: https://img.shields.io/static/v1?label=License&message=MIT&color=orange&logo=license
[license]: https://opensource.org/licenses/MIT
[esphome-release-shield]: https://img.shields.io/github/v/release/esphome/esphome?label=ESPHome&color=green&logo=esphome
[esphome-release]: https://esphome.io/

Коллекция **внешних компонентов** и **готовых проектов** для [ESPHome](https://esphome.io/).

---

## 🧩 Внешние компоненты (External Components)

| Компонент | Описание | Ссылка |
|-----------|----------|--------|
| **PM1006k** | Датчик качества воздуха (PM1.0, PM2.5, PM10) | [→ Перейти](/components/pm1006k) |
| **MQ** | Датчики газа (MQ-2, MQ-5, MQ-7 и др.) | [→ Перейти](/components/mq) |
| **HTS221** | Датчик температуры и влажности | [→ Перейти](/components/hts221) |
| **CAP1293** | Ёмкостной сенсорный контроллер (3 канала) | [→ Перейти](/components/cap1293) |
| **AW9310X** | Сенсорный контроллер для жестов | [→ Перейти](components/aw9310x) |
| **MCP453X** | Цифровой потенциометр | [→ Перейти](/components/mcp453x) |
| **CG-Anem** | Анемометр для Climateguard | [→ Перейти](/components/cg_anem) |
| **LilyGo T-Battery** | Мониторинг батареи для TTGO T-Display ESP32 | [→ Перейти](/components/lilygo_t_battery) |
| **RadSens** | Дозиметр (ионизирующее излучение) | [→ Перейти](/components/RadSens) |
| **mercury200** |  Меркурий 200.02  | [→ Перейти](/components/mercury200) |

---

## 🚀 Готовые проекты

### 🌬️ IKEA Vindriktning — монитор качества воздуха

Модернизация датчика качества воздуха IKEA Vindriktning с полной заменой электроники.

- 📄 **Репозиторий:** [ananyevgv/esphome-vindriktning-ikea](https://github.com/ananyevgv/esphome-vindriktning-ikea/)


**Возможности:**
- 🌡️ BME680 (температура, влажность, давление, VOC)
- 🌫️ PM1006k (PM1.0, PM2.5, PM10)
- 🌀 Управление вентилятором
- 🎨 Цветовой дисплей ST7735
- 🌅 Индикация солнца и прогноз погоды

---

### ☢️ Дозиметр RadSens

Портативный дозиметр на базе ESPHome и датчика RadSens.

**Основано на:** [med-lasers/Dosimeter_RadSens_NarodMon](https://github.com/med-lasers/Dosimeter_RadSens_NarodMon)

- 📄 **Компонент:** [RadSens](/components/RadSens)
- 📝 **Конфигурация:** [`dosimeter.yaml`](/components/RadSens/dosimeter.yaml)

**Возможности:**
- 📊 Измерение мощности дозы (мкЗв/ч)
- 🔢 Счётчик импульсов
- 📈 Отображение на дисплее

---


⭐ Поддержать проект
Если проект оказался полезным — поставьте ⭐ на GitHub!
