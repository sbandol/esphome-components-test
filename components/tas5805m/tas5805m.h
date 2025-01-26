#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace tas5805m {

class Tas5805mComponent : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_tas5805m_state(bool deep_sleep);

 protected:
   bool configure_registers(uint16_t number_registers);
   bool tas5805m_write_byte(uint8_t a_register, uint8_t data);

   enum ErrorCode {
     NONE = 0,
     WRITE_REGISTER_FAILED,
   } error_code_{NONE};

   uint8_t last_i2c_error_{0};
   uint16_t number_configuration_registers_;
};

}  // namespace tas5805m
}  // namespace esphome
