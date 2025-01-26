#include "tas5805m.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace tas5805m {

static const char *const TAG = "tas5805m";

static const uint8_t CFG_META_DELAY = 254;

struct tas5805m_cfg_reg_t {
  uint8_t offset;
  uint8_t value;
};

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

static const uint8_t DEVICE_CTRL_2_REGISTER = 0x03; // Device state control register

void Tas5805mComponent::setup() {
  if (!configure_registers(sizeof(tas5805m_registers) / sizeof(tas5805m_registers[0]))) {
    this->error_code_ = WRITE_REGISTER_FAILED;
    this->mark_failed();
    return;
  }

  // if (!this->tas5805m_write_byte(DEVICE_CTRL_2_REGISTER, 0x02)) { // device state Hi-Z
  //   this->error_code_ = WRITE_REGISTER_FAILED;
  //   this->mark_failed();
  //   return;
  // }

  // delay(10);

  // if (!this->tas5805m_write_byte(DEVICE_CTRL_2_REGISTER, 0x03)) { // device state PLAY
  //   this->error_code_ = WRITE_REGISTER_FAILED;
  //   this->mark_failed();
  //   return;
  // }
}

bool Tas5805mComponent::configure_registers(uint16_t number_registers) {
  uint16_t i = 0;
  while (i < number_registers) {
    switch (tas5805m_registers[i].offset) {
      case CFG_META_DELAY:
        delay(tas5805m_registers[i].value);
        break;
      default:
        if (!this->tas5805m_write_byte(tas5805m_registers[i].offset, tas5805m_registers[i].value)) return false;
        break;
    }
    i++;
  }
  return true;
}

void Tas5805mComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Tas5805m:");

  switch (this->error_code_) {
    case WRITE_REGISTER_FAILED:
      ESP_LOGE(TAG, "  Write register failed with error code = %i",this->last_i2c_error_);
      break;
    case NONE:
      ESP_LOGD(TAG, "  Setup successful");
      LOG_I2C_DEVICE(this);
      break;
  }
}

void Tas5805mComponent::set_tas5805m_state(bool deep_sleep) {
  uint8_t mode = deep_sleep ? 0x00 : 0x03; // device state Deep Sleep or PLAY
  this->tas5805m_write_byte(DEVICE_CTRL_2_REGISTER, mode);
}

bool Tas5805mComponent::tas5805m_write_byte(uint8_t a_register, uint8_t data) {
    i2c::ErrorCode error_code = this->write_register(a_register, &data, 1, true);
    if (error_code != i2c::ERROR_OK) {
      ESP_LOGE(TAG, "  write register error %i", error_code);
      this->last_i2c_error_ = (uint8_t)error_code;
      return false;
    }
    return true;
}

}  // namespace tas5805m
}  // namespace esphome
