#include "tas5805m_enable.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace tas5805m_enable {

static const char *const TAG = "tas5805m_enable";

const float STARTUP = 1100.0f;

void Tas5805mEnableComponent::setup() {
  if (this->enable_pin_ != nullptr) {
    // Set enable pin as OUTPUT and disable the enable pin
    this->enable_pin_->setup();
    this->enable_pin_->digital_write(false);
    delay(10);
    this->enable_pin_->digital_write(true);
    delay(10);
  }
}

void Tas5805mEnableComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "  Tas5805m DAC Enabled");
}
float Tas5805mEnableComponent::get_setup_priority() const {
  return STARTUP;
}

}  // namespace tas5805_startupm
}  // namespace esphome
