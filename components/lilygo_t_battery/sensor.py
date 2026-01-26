import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome import pins
from esphome.const import (
    CONF_ID,
    CONF_PIN,
    CONF_SENSOR,
    CONF_REFERENCE_VOLTAGE,
    CONF_ENABLE_PIN,
    CONF_VOLTAGE,
    CONF_BUS_VOLTAGE,
    CONF_LEVEL,
    UNIT_VOLT,
    UNIT_PERCENT,
    DEVICE_CLASS_VOLTAGE,
    DEVICE_CLASS_BATTERY,
    ICON_BATTERY,
)
ICON_BATTERY_CHARGING = "mdi:battery-charging"

CODEOWNERS = ["ananyevgv"]

Lilygotbattery_ns = cg.esphome_ns.namespace("lilygo_t_battery")
Lilygotbattery = Lilygotbattery_ns.class_(
    "LilygotBattery", cg.PollingComponent
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(Lilygotbattery),
        cv.Optional(CONF_ENABLE_PIN): pins.gpio_output_pin_schema,
        cv.Optional(CONF_REFERENCE_VOLTAGE, default="3.3V"): cv.voltage,
        cv.Required(CONF_SENSOR): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_BATTERY,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_VOLTAGE,
        ),

        cv.GenerateID(): cv.declare_id(Lilygotbattery),
        cv.Optional(CONF_BUS_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            accuracy_decimals=2,
            icon=ICON_BATTERY_CHARGING,
            device_class=DEVICE_CLASS_VOLTAGE,
        ),

        cv.GenerateID(): cv.declare_id(Lilygotbattery),
        cv.Optional(CONF_LEVEL): sensor.sensor_schema(
            unit_of_measurement=UNIT_PERCENT,
            accuracy_decimals=0,
            icon=ICON_BATTERY,
            device_class=DEVICE_CLASS_BATTERY,
        ), 
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    sens = await cg.get_variable(config[CONF_SENSOR])
    cg.add(var.set_sensor(sens))

    if CONF_VOLTAGE in config:
      sens = await sensor.new_sensor(config[CONF_VOLTAGE])
      cg.add(var.set_voltage_sensor(sens))

    if CONF_BUS_VOLTAGE in config:
      sens = await sensor.new_sensor(config[CONF_BUS_VOLTAGE])
      cg.add(var.set_bus_voltage_sensor(sens))

    if CONF_LEVEL in config:
      sens = await sensor.new_sensor(config[CONF_LEVEL])
      cg.add(var.set_battery_level_sensor(sens))

    if CONF_ENABLE_PIN in config:
        enable = await cg.gpio_pin_expression(config[CONF_ENABLE_PIN])

 
    


