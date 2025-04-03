import esphome.codegen as cg
import esphome.config_validation as cv
import esphome.final_validate as fv
from esphome import pins
from esphome.core import CORE
from esphome.components import sensor
from esphome.components.esp32 import get_esp32_variant
from esphome.const import (
    CONF_ATTENUATION,
    CONF_ID,
    CONF_NUMBER,
    CONF_PIN,
    CONF_RAW,
    CONF_WIFI,
    DEVICE_CLASS_VOLTAGE,
    DEVICE_CLASS_CARBON_MONOXIDE,
    CONF_MODEL,
    STATE_CLASS_MEASUREMENT,
    UNIT_VOLT,
    UNIT_PARTS_PER_MILLION,
    ICON_GAS_CYLINDER,
    ICON_MOLECULE_CO,
    ICON_MOLECULE_CO2,
)
from . import (
    ATTENUATION_MODES,
    ESP32_VARIANT_ADC1_PIN_TO_CHANNEL,
    ESP32_VARIANT_ADC2_PIN_TO_CHANNEL,
    validate_adc_pin,
)

CONF_RL = "rl"
CONF_R0 = "r0"
CONF_SENSOR_ACETONA = "sensor_acetona"
CONF_SENSOR_ALCOHOL = "sensor_alcohol"
CONF_SENSOR_BENZENE = "sensor_benzene"
CONF_SENSOR_CH4 = "sensor_ch4"
CONF_SENSOR_CL2 = "sensor_cl2"
CONF_SENSOR_CO = "sensor_co"
CONF_SENSOR_CO2 = "sensor_co2"
CONF_SENSOR_ETHANOL = "sensor_ethanol"
CONF_SENSOR_H2 = "sensor_h2"
CONF_SENSOR_HEXANE = "sensor_hexane"
CONF_SENSOR_HYDROGEN = "sensor_hydrogen"
CONF_SENSOR_ISO_BUTANO = "sensor_iso_butano"
CONF_SENSOR_LPG = "sensor_lpg"
CONF_SENSOR_NH4 = "sensor_nh4"
CONF_SENSOR_H2S = "sensor_h2s"
CONF_SENSOR_NOX = "sensor_nox"
CONF_SENSOR_O3 = "sensor_o3"
CONF_SENSOR_PROPANE = "sensor_propane"
CONF_SENSOR_SMOKE = "sensor_smoke"
CONF_SENSOR_TOLUENO = "sensor_tolueno"

mq_ns = cg.esphome_ns.namespace("mq")
MQModel = mq_ns.enum("MQModel")
MQ_MODELS = {
    "MQ2": MQModel.MQ_MODEL_2,
    "MQ3": MQModel.MQ_MODEL_3,
    "MQ4": MQModel.MQ_MODEL_4,
    "MQ5": MQModel.MQ_MODEL_5,
    "MQ6": MQModel.MQ_MODEL_6,
    "MQ7": MQModel.MQ_MODEL_7,
    "MQ8": MQModel.MQ_MODEL_8,
    "MQ9": MQModel.MQ_MODEL_9,
    "MQ131": MQModel.MQ_MODEL_131,
    "MQ135": MQModel.MQ_MODEL_135,
    "MQ136": MQModel.MQ_MODEL_136,
    "MQ303A": MQModel.MQ_MODEL_303A,
    "MQ309A": MQModel.MQ_MODEL_309A,
}
MQGasType = mq_ns.enum("MQ_GAS_TYPES")

MQ_MODEL_SENSORS = {
    "MQ2": [CONF_SENSOR_H2, CONF_SENSOR_LPG, CONF_SENSOR_CO, CONF_SENSOR_ALCOHOL, CONF_SENSOR_PROPANE],
    "MQ3": [CONF_SENSOR_LPG, CONF_SENSOR_CH4, CONF_SENSOR_CO, CONF_SENSOR_ALCOHOL, CONF_SENSOR_BENZENE, CONF_SENSOR_HEXANE],
    "MQ4": [CONF_SENSOR_LPG, CONF_SENSOR_CH4, CONF_SENSOR_CO, CONF_SENSOR_ALCOHOL, CONF_SENSOR_SMOKE],
    "MQ5": [CONF_SENSOR_H2, CONF_SENSOR_LPG, CONF_SENSOR_CH4, CONF_SENSOR_CO, CONF_SENSOR_ALCOHOL],
    "MQ6": [CONF_SENSOR_H2, CONF_SENSOR_LPG, CONF_SENSOR_CH4, CONF_SENSOR_CO, CONF_SENSOR_ALCOHOL],
    "MQ7": [CONF_SENSOR_H2, CONF_SENSOR_LPG, CONF_SENSOR_CH4, CONF_SENSOR_CO, CONF_SENSOR_ALCOHOL],
    "MQ8": [CONF_SENSOR_H2, CONF_SENSOR_LPG, CONF_SENSOR_CH4, CONF_SENSOR_CO, CONF_SENSOR_ALCOHOL],
    "MQ9": [CONF_SENSOR_LPG, CONF_SENSOR_CH4, CONF_SENSOR_CO],
    "MQ131": [CONF_SENSOR_NOX, CONF_SENSOR_CL2, CONF_SENSOR_O3],
    "MQ135": [CONF_SENSOR_CO, CONF_SENSOR_ALCOHOL, CONF_SENSOR_CO2, CONF_SENSOR_TOLUENO, CONF_SENSOR_NH4, CONF_SENSOR_ACETONA],
    "MQ136": [CONF_SENSOR_H2S, CONF_SENSOR_NH4, CONF_SENSOR_CO],
    "MQ303A": [CONF_SENSOR_ISO_BUTANO, CONF_SENSOR_HYDROGEN, CONF_SENSOR_ETHANOL],
    "MQ309A": [CONF_SENSOR_H2, CONF_SENSOR_CH4, CONF_SENSOR_CO, CONF_SENSOR_ALCOHOL],
}

MQ_GAS_TYPES = {
    CONF_SENSOR_ACETONA: MQGasType.MQ_GAS_TYPE_ACETONA,
    CONF_SENSOR_ALCOHOL: MQGasType.MQ_GAS_TYPE_ALCOHOL,
    CONF_SENSOR_BENZENE: MQGasType.MQ_GAS_TYPE_BENZENE,
    CONF_SENSOR_CH4: MQGasType.MQ_GAS_TYPE_CH4,
    CONF_SENSOR_CL2: MQGasType.MQ_GAS_TYPE_CL2,
    CONF_SENSOR_CO: MQGasType.MQ_GAS_TYPE_CO,
    CONF_SENSOR_CO2: MQGasType.MQ_GAS_TYPE_CO2,
    CONF_SENSOR_ETHANOL: MQGasType.MQ_GAS_TYPE_ETHANOL,
    CONF_SENSOR_H2: MQGasType.MQ_GAS_TYPE_H2,
    CONF_SENSOR_HEXANE: MQGasType.MQ_GAS_TYPE_HEXANE,
    CONF_SENSOR_HYDROGEN: MQGasType.MQ_GAS_TYPE_HYDROGEN,
    CONF_SENSOR_ISO_BUTANO: MQGasType.MQ_GAS_TYPE_ISO_BUTANO,
    CONF_SENSOR_LPG: MQGasType.MQ_GAS_TYPE_LPG,
    CONF_SENSOR_NH4: MQGasType.MQ_GAS_TYPE_NH4,
    CONF_SENSOR_H2S: MQGasType.MQ_GAS_TYPE_H2S,
    CONF_SENSOR_NOX: MQGasType.MQ_GAS_TYPE_NOX,
    CONF_SENSOR_O3: MQGasType.MQ_GAS_TYPE_O3,
    CONF_SENSOR_PROPANE: MQGasType.MQ_GAS_TYPE_PROPANE,
    CONF_SENSOR_SMOKE: MQGasType.MQ_GAS_TYPE_SMOKE,
    CONF_SENSOR_TOLUENO: MQGasType.MQ_GAS_TYPE_TOLUENO,
}

MQSensor = mq_ns.class_("MQSensor", cg.PollingComponent)


def get_model_valid_sensors(config):
    return set(MQ_MODEL_SENSORS[config[CONF_MODEL]])


def get_sensors_schemas(config):
    return set(list(dict(filter(lambda elem: "sensor_" in elem[0].lower(), config.items())).keys()))


def validate_sensors(config):
    model = config[CONF_MODEL]
    valid_sensors = get_model_valid_sensors(config)
    sensors_schemas = get_sensors_schemas(config)
    if sensors_schemas - valid_sensors != set():
        invalid_sensors = sensors_schemas.difference(valid_sensors)
        raise cv.Invalid(
            "Invalid sensors definition for {model}\nNot supported sensors:\n\t{}\n{model} supports:\n\t{}"
            "".format(", ".join(map(str, invalid_sensors)), ", ".join(map(str, valid_sensors)), model=model)
        )
    return config


sensor_schema = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_acetona = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_alcohol = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_benzene = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_ch4 = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_cl2 = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_co = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_MOLECULE_CO,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_co2 = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_MOLECULE_CO2,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_ethanol = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_h2 = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_hexane = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_hydrogen = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_iso_butano = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_lpg = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_nh4 = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_h2s = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_nox = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_o3 = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_propane = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_smoke = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
sensor_schema_tolueno = sensor.sensor_schema(
    unit_of_measurement=UNIT_PARTS_PER_MILLION,
    icon=ICON_GAS_CYLINDER,
    accuracy_decimals=2,
    state_class=STATE_CLASS_MEASUREMENT
)
CONFIG_SCHEMA = cv.All(
    cv.Schema({
        cv.GenerateID(): cv.declare_id(MQSensor),
        cv.Required(CONF_PIN): validate_adc_pin,
        cv.Optional(CONF_RL, default=10.0): cv.positive_float,
        cv.Optional(CONF_R0): cv.positive_float,
        cv.Required(CONF_MODEL): cv.enum(
            MQ_MODELS, upper=True, space="_"
        ),
        cv.Optional(CONF_SENSOR_ACETONA): sensor_schema_acetona,
        cv.Optional(CONF_SENSOR_ALCOHOL): sensor_schema_alcohol,
        cv.Optional(CONF_SENSOR_BENZENE): sensor_schema_benzene,
        cv.Optional(CONF_SENSOR_CH4): sensor_schema_ch4,
        cv.Optional(CONF_SENSOR_CL2): sensor_schema_cl2,
        cv.Optional(CONF_SENSOR_CO): sensor_schema_co,
        cv.Optional(CONF_SENSOR_CO2): sensor_schema_co2,
        cv.Optional(CONF_SENSOR_ETHANOL): sensor_schema_ethanol,
        cv.Optional(CONF_SENSOR_H2): sensor_schema_h2,
        cv.Optional(CONF_SENSOR_HEXANE): sensor_schema_hexane,
        cv.Optional(CONF_SENSOR_HYDROGEN): sensor_schema_hydrogen,
        cv.Optional(CONF_SENSOR_ISO_BUTANO): sensor_schema_iso_butano,
        cv.Optional(CONF_SENSOR_LPG): sensor_schema_lpg,
        cv.Optional(CONF_SENSOR_NH4): sensor_schema_nh4,
        cv.Optional(CONF_SENSOR_H2S): sensor_schema_h2s,       
        cv.Optional(CONF_SENSOR_NOX): sensor_schema_nox,
        cv.Optional(CONF_SENSOR_O3): sensor_schema_o3,
        cv.Optional(CONF_SENSOR_PROPANE): sensor_schema_propane,
        cv.Optional(CONF_SENSOR_SMOKE): sensor_schema_smoke,
        cv.Optional(CONF_SENSOR_TOLUENO): sensor_schema_tolueno,
    }).extend(cv.polling_component_schema("10s")),
    validate_sensors,
)


async def to_code(config):
    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    var = cg.new_Pvariable(config[CONF_ID], pin, config[CONF_MODEL], CORE.is_esp8266, config[CONF_RL])
    await cg.register_component(var, config)

    cg.add_library("MQUnifiedsensor", "2.0.1")

    if CONF_R0 in config:
        cg.add(var.set_R0(config[CONF_R0]))

    model_valid_sensors = set(MQ_MODEL_SENSORS[config[CONF_MODEL]])
    sensors_schemas = get_sensors_schemas(config)
    sensors = model_valid_sensors.intersection(sensors_schemas)

    for item in sensors:
        conf = config[item]
        gas_type = MQ_GAS_TYPES[item]
        sens = await sensor.new_sensor(conf)
        cg.add(var.add_sensor(sens, gas_type))
