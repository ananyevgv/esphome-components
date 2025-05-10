import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import CONF_CHANNEL

from . import CONF_CAP1293_ID, CAP1293Component, cap1293_ns

DEPENDENCIES = ["cap1293"]
CAP1293Channel = cap1293_ns.class_("CAP1293Channel", binary_sensor.BinarySensor)

CONFIG_SCHEMA = binary_sensor.binary_sensor_schema(CAP1293Channel).extend(
    {
        cv.GenerateID(CONF_CAP1293_ID): cv.use_id(CAP1293Component),
        cv.Required(CONF_CHANNEL): cv.int_range(min=0, max=7),
    }
)


async def to_code(config):
    var = await binary_sensor.new_binary_sensor(config)
    hub = await cg.get_variable(config[CONF_CAP1293_ID])
    cg.add(var.set_channel(config[CONF_CHANNEL]))

    cg.add(hub.register_channel(var))
