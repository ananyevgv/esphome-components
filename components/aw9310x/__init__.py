# components/aw9310x/__init__.py
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome import pins
from esphome.const import (
    CONF_ID,
    CONF_ADDRESS,
    CONF_INTERRUPT_PIN,
    CONF_THRESHOLD,
)

DEPENDENCIES = ["i2c"]
AUTO_LOAD = ["binary_sensor"]
CODEOWNERS = ["ananyevgv"]

aw9310x_ns = cg.esphome_ns.namespace("aw9310x")
CONF_AW9310X_ID = "aw9310x_id"
AW9310XComponent = aw9310x_ns.class_("AW9310XComponent", cg.Component, i2c.I2CDevice)

MULTI_CONF = True
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(AW9310XComponent),
    cv.Optional(CONF_ADDRESS, default=0x12): cv.i2c_address,
    cv.Optional(CONF_INTERRUPT_PIN): pins.gpio_input_pin_schema,
    cv.Optional(CONF_THRESHOLD, default=50000): cv.int_range(min=1000, max=1000000),
}).extend(cv.COMPONENT_SCHEMA).extend(i2c.i2c_device_schema(0x12))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    
    if CONF_INTERRUPT_PIN in config:
        pin = await cg.gpio_pin_expression(config[CONF_INTERRUPT_PIN])
        cg.add(var.set_interrupt_pin(pin))
    cg.add(var.set_threshold(config[CONF_THRESHOLD]))
    
    

