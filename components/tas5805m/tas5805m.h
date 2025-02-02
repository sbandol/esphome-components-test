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

class Tas5805mComponent : AudioDac, public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_enable_pin(GPIOPin *enable) { this->enable_pin_ = enable; }

  void set_tas5805m_state(bool deep_sleep);
  //bool get_gain(uint8_t* value);
  //bool set_gain(uint8_t value);

  float volume() override {return (float)this->last_raw_volume_; }
  bool set_volume(float value) override;
  bool set_mute_off() override;
raw_
  bool set_mute_on() override;

  bool is_muted() override { return this->is_muted_; }

  void set_tas5805m_state(bool deep_sleep);
  //bool get_gain(uint8_t* value);
  //bool set_gain(uint8_t value);


 protected:
   GPIOPin *enable_pin_{nullptr};

   bool configure_registers(uint16_t number_registers);
   bool tas5805m_write_byte(uint8_t a_register, uint8_t data);
   bool tas5805m_read_byte(uint8_t a_register, uint8_t* data);

   enum ErrorCode {
     NONE = 0,
     WRITE_REGISTER_FAILED,
   } error_code_{NONE};

   int8_t last_raw_volume_; // tas5805 volume 0-254 == 24 to -103 db
   uint8_t last_i2c_error_{0};
   uint16_t number_configuration_registers_;
};

}  // namespace tas5805m
}  // namespace esphome
