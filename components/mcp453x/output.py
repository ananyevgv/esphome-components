import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID
from . import MCP453XComponent, mcp453x_ns

MCP453XOutput = mcp453x_ns.class_("MCP453XOutput", output.FloatOutput, cg.Component)

CONF_MCP453X_ID = "mcp453x_id"

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend({
    cv.Required(CONF_MCP453X_ID): cv.use_id(MCP453XComponent),
    cv.Required(CONF_ID): cv.declare_id(MCP453XOutput),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await output.register_output(var, config)
    
    parent = await cg.get_variable(config[CONF_MCP453X_ID])
    cg.add(var.set_parent(parent))