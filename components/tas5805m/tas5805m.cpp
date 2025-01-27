#include "tas5805m.h"
#include "tas5805m_config_minimal.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace tas5805m {

static const char *const TAG = "tas5805m";

// tas5805m registers
static const uint8_t DEVICE_CTRL_2_REGISTER = 0x03; // Device state control register
static const uint8_t DIG_VOL_CTRL_REGISTER  = 0x4c;
static const uint8_t AGAIN_REGISTER         = 0x54;

void Tas5805mComponent::setup() {
  this->number_configuration_registers_ = sizeof(tas5805m_registers) / sizeof(tas5805m_registers[0]);
  if (!configure_registers(this->number_configuration_registers_)) {
    this->error_code_ = WRITE_REGISTER_FAILED;
    this->mark_failed();
    return;
  }
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
      ESP_LOGD(TAG, "  Registers configured: %i", this->number_configuration_registers_);
      ESP_LOGD(TAG, "  Setup successful");
      LOG_I2C_DEVICE(this);
      break;
  }
  uint8_t volume;
  if (!this->get_volume(&volume) {
    ESP_LOGD(TAG, "  error reading volume");
  } else {
    ESP_LOGD(TAG, "  volume = %i",volume);
  }
}

void Tas5805mComponent::set_tas5805m_state(bool deep_sleep) {
  uint8_t mode = deep_sleep ? 0x00 : 0x03; // device state Deep Sleep or PLAY
  this->tas5805m_write_byte(DEVICE_CTRL_2_REGISTER, mode);
}

// bool Tas5805mComponent::get_gain(uint8_t* volume) {
//     uint8_t value = 0;
//     esp_err_t ret = _read_byte(TAS5805M_AGAIN_REGISTER, &value);
//     *volume = value << 3;
//     return ret;
// }

bool Tas5805mComponent::get_volume(uint8_t* volume) {
  *volume = 0;
  return this->tas5805m_read_byte(DIG_VOL_CTRL_REGISTER, volume);
}

// 0-255, where 0 = 0 Db, 255 = mute
// bool Tas5805mComponent::::setVolume(uint8_t value)
// {
//     uint8_t volume = value;
//     return _write_byte(TAS5805M_DIG_VOL_CTRL_REGISTER, volume);

bool Tas5805mComponent::tas5805m_write_byte(uint8_t a_register, uint8_t data) {
    i2c::ErrorCode error_code = this->write_register(a_register, &data, 1, true);
    if (error_code != i2c::ERROR_OK) {
      ESP_LOGE(TAG, "  write register error %i", error_code);
      this->last_i2c_error_ = (uint8_t)error_code;
      return false;
    }
    return true;
}

bool Tas5805mComponent::tas5805m_read_byte(uint8_t register, uint8_t* data) {
  i2c::ErrorCode error_code;
  error_code = write(&register, 1);
  if (error_code != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "  read register - first write error %i", error_code);
    this->last_i2c_error_ = (uint8_t)error_code;
    return false;
  }
  error_code = this->read_register(a_register, data, 1, true);
  if (error_code != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "  read register error %i", error_code);
    this->last_i2c_error_ = (uint8_t)error_code;
    return false;
  }
  return true;
}

}  // namespace tas5805m
}  // namespace esphome
