import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    CONF_ID,
    CONF_DUCT,
    CONF_AMBIENT_TEMPERATURE,
    CONF_HOTEND_TEMPERATURE,
    CONF_HEAT_POWER,
    CONF_AIR_CONSUMPTION,
    CONF_AIR_FLOW_RATE,
    CONF_FIRMWARE_VERSION,
    CONF_MIN_AIR_FLOW_RATE,
    CONF_MAX_AIR_FLOW_RATE,
    CONF_STATUS_UP,
    CONF_STATUS_OV,
    CONF_STATUS_WDT,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_WIND_SPEED,
    DEVICE_CLASS_FIRMWARE,
    DEVICE_CLASS_AREA,
    DEVICE_CLASS_POWER,
    DEVICE_CLASS_VOLUME,
    DEVICE_CLASS_EMPTY,

    UNIT_CELSIUS,
    UNIT_EMPTY,
    STATE_CLASS_MEASUREMENT,
    ICON_CHIP,
    ENTITY_CATEGORY_DIAGNOSTIC
)

UNIT_METER_PER_SECOND = "m/s"
UNIT_COUNTS_PER_SQUARED_CENTIMETER = "cm²"
DEPENDENCIES = ["i2c"]

cg_anem_ns = cg.esphome_ns.namespace("cg_anem")

CGAnemComponent = cg_anem_ns.class_(
    "CGAnemComponent", cg.PollingComponent, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(CGAnemComponent),
            cv.Optional(CONF_AMBIENT_TEMPERATURE): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_HOTEND_TEMPERATURE): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(AIR_FLOW_RATE): sensor.sensor_schema(
                unit_of_measurement=UNIT_METER_PER_SECOND,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_WIND_SPEED,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(MIN_AIR_FLOW_RATE): sensor.sensor_schema(
                unit_of_measurement=UNIT_METER_PER_SECOND,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_WIND_SPEED,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(MAX_AIR_FLOW_RATE): sensor.sensor_schema(
                unit_of_measurement=UNIT_METER_PER_SECOND,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_WIND_SPEED,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_HEAT_POWER): sensor.sensor_schema(
                unit_of_measurement=UNIT_WATT,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_POWER,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_AIR_CONSUMPTION): sensor.sensor_schema(
                unit_of_measurement=UNIT_CUBIC_METER_PER_HOUR,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_VOLUME,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_FIRMWARE_VERSION): sensor.sensor_schema(
    		unit_of_measurement=UNIT_EMPTY,
    		icon=ICON_CHIP,
    		accuracy_decimals=0,
    		state_class=STATE_CLASS_MEASUREMENT,
    		device_class=DEVICE_CLASS_EMPTY,
    		entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),


            cv.Optional(CONF_STATUS_UP): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
            ),
            cv.Optional(CONF_STATUS_OV): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
            ),
            cv.Optional(CONF_STATUS_WDT): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
            ),

        }
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(i2c.i2c_device_schema(0x11))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    if CONF_AMBIENT_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_AMBIENT_TEMPERATURE])
        cg.add(var.set_ambient_temperature_sensor(sens))
    if CONF_HOTEND_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_HOTEND_TEMPERATURE])
        cg.add(var.set_hotend_temperature_sensor(sens))
    if AIR_FLOW_RATE in config:
        sens = await sensor.new_sensor(config[AIR_FLOW_RATE])
        cg.add(var.set_air_flow_rate(sens))
    if MIN_AIR_FLOW_RATE in config:
        sens = await sensor.new_sensor(config[MIN_AIR_FLOW_RATE])
        cg.add(var.set_min_air_flow_rate(sens))
    if MAX_AIR_FLOW_RATE in config:
        sens = await sensor.new_sensor(config[MAX_AIR_FLOW_RATE])
        cg.add(var.set_max_air_flow_rate(sens))
    if HEAT_POWER in config:
        sens = await sensor.new_sensor(config[HEAT_POWER])
        cg.add(var.set_heat_power(sens))
    if CONF_FIRMWARE_VERSION in config:
        sens = await sensor.new_sensor(config[CONF_FIRMWARE_VERSION])
        cg.add(var.set_firmware_version_sensor(sens))
    if CONF_AIR_CONSUMPTION in config:
        sens = await sensor.new_sensor(config[CONF_AIR_CONSUMPTION])
        cg.add(var.set_air_consumption_sensor(sens))


    if CONF_STATUS_UP in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_STATUS_UP])
        cg.add(var.set_status_up_sensor(sens))
    if CONF_STATUS_OV in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_STATUS_OV])
        cg.add(var.set_status_ov_sensor(sens))
    if CONF_STATUS_WDT in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_STATUS_WDT])
        cg.add(var.set_status_wdt_sensor(sens))

