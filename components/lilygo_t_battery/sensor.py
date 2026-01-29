import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome import pins
from esphome.const import (
    CONF_ID,
    CONF_SENSOR,
    CONF_ENABLE_PIN,
    CONF_VOLTAGE,
    CONF_BUS_VOLTAGE,
    CONF_LEVEL,
    UNIT_VOLT,
    UNIT_PERCENT,
    DEVICE_CLASS_VOLTAGE,
    DEVICE_CLASS_BATTERY,
)

CODEOWNERS = ["ananyevgv"]

DEPENDENCIES = ["esp32"]

Lilygotbattery_ns = cg.esphome_ns.namespace("lilygo_t_battery")
LilygotBattery = Lilygotbattery_ns.class_("LilygotBattery", cg.PollingComponent)

CONF_VOLTAGE_DIVIDER = "voltage_divider"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(LilygotBattery),
    cv.Required(CONF_SENSOR): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_ENABLE_PIN): pins.gpio_output_pin_schema,
    cv.Optional(CONF_VOLTAGE_DIVIDER, default=7.26): cv.float_range(min=1.0, max=20.0),
    
    cv.Optional(CONF_VOLTAGE): sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_VOLTAGE,
    ),
    
    cv.Optional(CONF_BUS_VOLTAGE): sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_VOLTAGE,
    ),
    
    cv.Optional(CONF_LEVEL): sensor.sensor_schema(
        unit_of_measurement=UNIT_PERCENT,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_BATTERY,
    ),
}).extend(cv.polling_component_schema('60s'))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
    # ADC sensor
    adc_sensor = await cg.get_variable(config[CONF_SENSOR])
    cg.add(var.set_adc_sensor(adc_sensor))
    
    # Enable pin
    if CONF_ENABLE_PIN in config:
        enable_pin = await cg.gpio_pin_expression(config[CONF_ENABLE_PIN])
        cg.add(var.set_enable_pin(enable_pin))
    
    # Voltage divider
    cg.add(var.set_voltage_divider(config[CONF_VOLTAGE_DIVIDER]))
    
    # Sensors
    if CONF_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_VOLTAGE])
        cg.add(var.set_voltage_sensor(sens))
    
    if CONF_BUS_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_BUS_VOLTAGE])
        cg.add(var.set_bus_voltage_sensor(sens))
    
    if CONF_LEVEL in config:
        sens = await sensor.new_sensor(config[CONF_LEVEL])
        cg.add(var.set_battery_level_sensor(sens))