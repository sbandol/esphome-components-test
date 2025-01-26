import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

CODEOWNERS = ["@mrtoy-me"]
DEPENDENCIES = ["i2c"]

CONF_TAS5805M_ID = "tas5805m_id"

tas5805m_ns = cg.esphome_ns.namespace("tas5805m")
Tas5805mComponent = tas5805m_ns.class_("Tas5805mComponent", cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
      {
        cv.GenerateID(): cv.declare_id(Tas5805mComponent),
      }
    ).extend(i2c.i2c_device_schema(0x2D)).extend(cv.COMPONENT_SCHEMA),
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
