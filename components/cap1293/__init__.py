from esphome import pins
import esphome.codegen as cg
from esphome.components import i2c
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_RESET_PIN

CONF_TOUCH_THRESHOLD = "touch_threshold"
CONF_ALLOW_MULTIPLE_TOUCHES = "allow_multiple_touches"

DEPENDENCIES = ["i2c"]
AUTO_LOAD = ["binary_sensor", "output"]
CODEOWNERS = ["ananyevgv"]

cap1293_ns = cg.esphome_ns.namespace("cap1293")
CONF_CAP1293_ID = "cap1293_id"
CAP1293Component = cap1293_ns.class_("CAP1293Component", cg.Component, i2c.I2CDevice)

MULTI_CONF = True
CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(CAP1293Component),
            cv.Optional(CONF_RESET_PIN): pins.gpio_output_pin_schema,
            cv.Optional(CONF_TOUCH_THRESHOLD, default=0x07): cv.int_range(
                min=0x00, max=0x07
            ),
            cv.Optional(CONF_ALLOW_MULTIPLE_TOUCHES, default=False): cv.boolean,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x28))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.set_touch_threshold(config[CONF_TOUCH_THRESHOLD]))
    cg.add(var.set_allow_multiple_touches(config[CONF_ALLOW_MULTIPLE_TOUCHES]))

    if reset_pin_config := config.get(CONF_RESET_PIN):
        pin = await cg.gpio_pin_expression(reset_pin_config)
        cg.add(var.set_reset_pin(pin))

    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
