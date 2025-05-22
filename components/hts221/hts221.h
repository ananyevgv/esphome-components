#include "esphome.h"
#include "Adafruit_HTS221.h"

class HTS221CustomSensor : public PollingComponent, public Sensor {
 public:
  Adafruit_HTS221 hts;
  Sensor *temperature_sensor = new Sensor();
  Sensor *humidity_sensor = new Sensor();

  HTS221CustomSensor(uint32_t update_interval) : PollingComponent(update_interval) { }

  void setup() override {
    hts.begin_I2C();
  }

  void update() override {
    // This is the actual sensor reading logic, which will be called every "update_interval" *milli*seconds

    sensors_event_t temp;
    sensors_event_t humidity;
    hts.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data

    temperature_sensor->publish_state(temp.temperature);
    humidity_sensor->publish_state(humidity.relative_humidity);

  }
};