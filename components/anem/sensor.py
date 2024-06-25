import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    CONF_ID,
    CONF_ADDRESS,
    CONF_TEMPERATURE,
    CONF_MAX_TEMPERATURE,
    CONF_MIN_TEMPERATURE,
    CONF_WIND_SPEED,
    CONF_POWER,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_WIND_SPEED,
    DEVICE_CLASS_VOLTAGE,
    DEVICE_CLASS_POWER,
    DEVICE_CLASS_VOLUME_STORAGE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
    UNIT_VOLT,
    UNIT_EMPTY,
    
)

DEPENDENCIES = ['i2c']

CONF_I2C_ADDR = 0x01

anem_sensor_ns = cg.esphome_ns.namespace('anem')
Anem = anem_ns.class_('Anem', cg.PollingComponent, i2c.I2CDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(CGAnemComponent),
            cv.Optional(CONF_MIN_TEMPERATURE): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            
            cv.GenerateID(): cv.declare_id(CGAnemComponent),
            cv.Optional(CONF_MAX_TEMPERATURE): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),            
            cv.GenerateID(): cv.declare_id(CGAnemComponent),
            cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.GenerateID(): cv.declare_id(CGAnemComponent),
            cv.Optional(CONF_WIND_SPEED): sensor.sensor_schema(
                unit_of_measurement=UNIT_METER_PER_SECOND,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_WIND_SPEED,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.GenerateID(): cv.declare_id(CGAnemComponent),
            cv.Optional(CONF_MIN_WIND_SPEED): sensor.sensor_schema(
                unit_of_measurement=UNIT_METER_PER_SECOND,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_WIND_SPEED,
                state_class=STATE_CLASS_MEASUREMENT,
            ),            
            cv.GenerateID(): cv.declare_id(CGAnemComponent),
            cv.Optional(CONF_MAX_WIND_SPEED): sensor.sensor_schema(
                unit_of_measurement=UNIT_METER_PER_SECOND,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_WIND_SPEED,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.GenerateID(): cv.declare_id(CGAnemComponent),
            cv.Optional(CONF_SUPPLY_V): sensor.sensor_schema(
                unit_of_measurement=UNIT_VOLT,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_VOLTAGE,
            ), 
            cv.GenerateID(): cv.declare_id(CGAnemComponent),
            cv.Optional(CONF_POWER): sensor.sensor_schema(
                unit_of_measurement=UNIT_WATT,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_POWER,
            ),            
            cv.GenerateID(): cv.declare_id(CGAnemComponent),
            cv.Optional(CONF_FIRMWARE): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_MEASUREMENT,
            ),            
            cv.GenerateID(): cv.declare_id(CGAnemComponent),
            cv.Optional(CONF_DUCT_AREA): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_MEASUREMENT,
            ),   
            cv.GenerateID(): cv.declare_id(CGAnemComponent),
            cv.Optional(CONF_CONSUMPTION): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_VOLUME_STORAGE,
                state_class=STATE_CLASS_MEASUREMENT,
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

    if temperature_config := config.get(CONF_TEMPERATURE):
        sens = await sensor.new_sensor(temperature_config)
        cg.add(var.set_temperature_sensor(sens))
    if temperature_cold_config := config.get(CONF_TEMPERATURE_COLD):
        sens = await sensor.new_sensor(temperature_cold_config)
        cg.add(var.set_temperature_cold_sensor(sens)) 
    if temperature_hot_config := config.get(CONF_TEMPERATURE_HOT):
        sens = await sensor.new_sensor(temperature_hot_config)
        cg.add(var.set_temperature_hot_sensor(sens))        
        
    if speed_config := config.get(CONF_WIND_SPEED):
        sens = await sensor.new_sensor(speed_config)
        cg.add(var.set_speed_sensor(sens))
    if min_speed_config := config.get(CONF_MIN_WIND_SPEED):
        sens = await sensor.new_sensor(min_speed_config)
        cg.add(var.set_min_speed_sensor(sens))
    if max_speed_config := config.get(CONF_MAX_WIND_SPEED):
        sens = await sensor.new_sensor(max_speed_config)
        cg.add(var.set_max_speed_sensor(sens))        
        
    if consumption_config := config.get(CONF_CONSUMPTION):
        sens = await sensor.new_sensor(consumption_config)
        cg.add(var.set_consumption_sensor(sens))          
    if supply_v_config := config.get(CONF_SUPPLY_V):
        sens = await sensor.new_sensor(supply_v_config)
        cg.add(var.set_supply_v_sensor(sens))          
    if power_config := config.get(CONF_POWER):
        sens = await sensor.new_sensor(power_config)
        cg.add(var.set_power_sensor(sens))          
    if firmfare_config := config.get(CONF_FIRMWARE):
        sens = await sensor.new_sensor(firmfare)
        cg.add(var.firmfare_sensor(sens))   
        
    if duct := config.get(CONF_DUCT):
        sens = await sensor.new_sensor(duct_config)
        cg.add(var.set_duct_sensor(sens))     
    
