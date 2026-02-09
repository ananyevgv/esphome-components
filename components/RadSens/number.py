import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import (
    CONF_ID,
    CONF_ICON,
    CONF_UNIT_OF_MEASUREMENT,
    ICON_TUNE,
    UNIT_EMPTY,
)

from . import RadSensComponent, CONF_SENSITIVITY_NUMBER

DEPENDENCIES = ['rad_sens']

CONFIG_SCHEMA = cv.Schema({
    cv.Required(CONF_ID): cv.use_id(RadSensComponent),
    cv.Optional(CONF_SENSITIVITY_NUMBER): number.NUMBER_SCHEMA.extend({
        cv.Optional(CONF_ICON, default=ICON_TUNE): cv.icon,
        cv.Optional(CONF_UNIT_OF_MEASUREMENT, default="imp/µR"): cv.string_strict,
    }),
})

async def to_code(config):
    parent = await cg.get_variable(config[CONF_ID])
    
    if CONF_SENSITIVITY_NUMBER in config:
        num = await number.new_number(config[CONF_SENSITIVITY_NUMBER],
                                     min_value=100,
                                     max_value=1100,
                                     step=10)
        cg.add(parent.set_sensitivity_number(num))
