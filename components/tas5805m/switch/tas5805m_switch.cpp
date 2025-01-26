#include "tas5805m_switch.h"
#include "esphome/core/log.h"

namespace esphome {
namespace tas5805m {

static const char *const TAG = "tas5805m.switch";

void Tas5805mSwitch::setup() {
  this->write_state(false);
}

void Tas5805mSwitch::dump_config() {
  LOG_SWITCH("", "Tas8505m Switch:", this);
}

void Tas5805mSwitch::write_state(bool deep_sleep) {
  this->publish_state(deep_sleep);
  this->parent_->set_tas5805m_state(deep_sleep);
}

}  // namespace tas5805m
}  // namespace esphome
