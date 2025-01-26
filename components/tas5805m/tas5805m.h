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

static const uint8_t CFG_META_DELAY = 254;

static const tas5805m_cfg_reg_t tas5805m_registers[] = {
// RESET
    { 0x00, 0x00 },
    { 0x7f, 0x00 },
    { 0x03, 0x02 },
    { 0x01, 0x11 },
    { 0x03, 0x02 },
    { CFG_META_DELAY, 10 },
    { 0x03, 0x00 },
    { 0x46, 0x01 },
    { 0x03, 0x02 },
    { 0x61, 0x0b },
    { 0x60, 0x01 },
    { 0x7d, 0x11 },
    { 0x7e, 0xff },
    { 0x00, 0x01 },
    { 0x51, 0x05 },
// Register Tuning
    { 0x00, 0x00 },
    { 0x7f, 0x00 },
    { 0x02, 0x00 },
    { 0x30, 0x00 },
    { 0x4c, 0x30 },
    { 0x53, 0x00 },
    { 0x54, 0x00 },
    { 0x03, 0x03 },
    { 0x78, 0x80 },
};

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
};

}  // namespace tas5805m
}  // namespace esphome
