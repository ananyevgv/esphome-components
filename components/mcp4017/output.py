import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID
from . import MCP4017Component, mcp4017_ns

MCP4017Output = mcp4017_ns.class_("MCP4017Output", output.FloatOutput, cg.Component)

CONF_MCP4017_ID = "mcp4017_id"

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend({
    cv.Required(CONF_MCP4017_ID): cv.use_id(MCP4017Component),
    cv.Required(CONF_ID): cv.declare_id(MCP4017Output),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await output.register_output(var, config)
    
    parent = await cg.get_variable(config[CONF_MCP4017_ID])
    cg.add(var.set_parent(parent))