#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace tas5805m {

struct tas5805m_cfg_reg_t {
  uint8_t offset;
  uint8_t value;
};

class Tas5805mComponent : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_tas5805m_state(bool deep_sleep);

 protected:
   bool configure_registers(const tas5805m_cfg_reg_t* configuration, int size);
   bool tas5805m_write_byte(uint8_t a_register, uint8_t data);

   enum ErrorCode {
     NONE = 0,
     WRITE_REGISTER_FAILED,
   } error_code_{NONE};

   uint8_t last_i2c_error_{0};
};

}  // namespace tas5805m
}  // namespace esphome
