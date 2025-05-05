import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID
CONF_NR = "number_resistors"
CONF_BITS = "bits"


DEPENDENCIES = ["i2c"]
MULTI_CONF = True

mcp453x_ns = cg.esphome_ns.namespace("mcp453x")
MCP453XComponent = mcp453x_ns.class_("MCP453XComponent", cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(MCP453XComponent),
}).extend(i2c.i2c_device_schema(0x2F)).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
