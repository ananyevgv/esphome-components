import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID
CONF_NR = "number_resistors"
CONF_BITS = "bits"


DEPENDENCIES = ["i2c"]
MULTI_CONF = True
CODEOWNERS = ["ananyevgv"]

mcp4017_ns = cg.esphome_ns.namespace("mcp4017")
MCP4017Component = mcp4017_ns.class_("MCP4017Component", cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(MCP4017Component),
}).extend(i2c.i2c_device_schema(0x2F)).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
