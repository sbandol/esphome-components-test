#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "../tas5805m.h"

namespace esphome {
namespace tas5805m {

class Tas5805mSwitch : public Component, public switch_::Switch,  public Parented<Tas5805mComponent> {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  void write_state(bool deep_sleep) override;
};

}  // namespace tas5805m
}  // namespace esphome
