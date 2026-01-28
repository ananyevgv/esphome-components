import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import CONF_CHANNEL, CONF_ID

from . import CONF_AW9310X_ID, AW9310XComponent, aw9310x_ns

DEPENDENCIES = ["aw9310x"]

# Создаем класс для каналов AW9310X
AW9310XChannel = aw9310x_ns.class_("AW9310XChannel", binary_sensor.BinarySensor)

CONFIG_SCHEMA = binary_sensor.binary_sensor_schema(AW9310XChannel).extend(
    {
        cv.Required(CONF_AW9310X_ID): cv.use_id(AW9310XComponent),
        cv.Required(CONF_CHANNEL): cv.int_range(min=0, max=5),
    }
)


async def to_code(config):
    # Создаем бинарный сенсор
    var = await binary_sensor.new_binary_sensor(config)
    
    # Получаем хаб AW9310X
    hub = await cg.get_variable(config[CONF_AW9310X_ID])
    channel = config[CONF_CHANNEL]
    
    # Регистрируем сенсор в хабе
    cg.add(var.set_channel(channel))
    cg.add(hub.register_channel(var, channel))