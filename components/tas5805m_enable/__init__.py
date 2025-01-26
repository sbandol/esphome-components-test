import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_ENABLE_PIN,
)

from esphome import pins

CODEOWNERS = ["@mrtoy-me"]

tas5805m_enable_ns = cg.esphome_ns.namespace("tas5805m_enable")
Tas5805mEnableComponent = tas5805m_enable_ns.class_("Tas5805mEnableComponent", cg.Component)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
      {
        cv.GenerateID(): cv.declare_id(Tas5805mEnableComponent),
        cv.Required(CONF_ENABLE_PIN): pins.gpio_output_pin_schema,
      }
    ).extend(cv.COMPONENT_SCHEMA),
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    if CONF_ENABLE_PIN in config:
        enable = await cg.gpio_pin_expression(config[CONF_ENABLE_PIN])
        cg.add(var.set_enable_pin(enable))
