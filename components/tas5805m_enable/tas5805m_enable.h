#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace tas5805m_enable {

class Tas5805mEnableComponent : public Component {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;

  void set_enable_pin(GPIOPin *enable) { this->enable_pin_ = enable; }

 protected:
   GPIOPin *enable_pin_{nullptr};

};

}  // namespace tas5805m_enable
}  // namespace esphome
