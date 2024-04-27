import esphome.codegen as cg
from esphome.components import switch

from .. import (
    HOME_ASSISTANT_IMPORT_SCHEMA,
    homeassistant_ns,
    setup_home_assistant_entity,
)

DEPENDENCIES = ["api"]

HomeassistantSwitch = homeassistant_ns.class_(
    "HomeassistantSwitch", switch.Switch, cg.Component
)

CONFIG_SCHEMA = switch.switch_schema(HomeassistantSwitch).extend(
    HOME_ASSISTANT_IMPORT_SCHEMA
)


async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)
    setup_home_assistant_entity(var, config)
