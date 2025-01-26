import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_SWITCH,
)

from .. import tas5805m_ns, Tas5805mComponent, CONF_TAS5805M_ID

DEPENDENCIES = ["tas5805m"]

Tas5805mSwitch = tas5805m_ns.class_("Tas5805mSwitch", switch.Switch, cg.Component)

CONFIG_SCHEMA = switch.switch_schema(
    Tas5805mSwitch,
    device_class=DEVICE_CLASS_SWITCH,
).extend(
    cv.Schema(
        {
           cv.GenerateID(CONF_TAS5805M_ID): cv.use_id(Tas5805mComponent),
        }
    )
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await switch.register_switch(var, config)
    await cg.register_parented(var, config[CONF_TAS5805M_ID])
