
## Accessing: "tas5805m" component
Pull component files directly from Github using the following yaml:
```
external_components:
  - source: github://mrtoy-me/esphome-components-test@main
    components: [ tas5805m_enable, tas5805m ]
    refresh: 1s
```

## Follow this example YAML for configuration (ESP32S3 16MB Flash, 8MB PSRAM)
## Note that esp32 board, !secrets, psram configuration (if required)
## and most importantly GPIO pins will need to be configured according to your hardware
```
esphome:
  name: louder-esp32
  friendly_name: louder-esp32
  platformio_options:
    board_build.arduino.memory_type: qio_opi
  on_boot:
  ## use priority 250 so gpio and i2c dac is setup before volume is set
    priority: 250
    then:
    ## Set a volume limit just to be safe...
    - media_player.volume_set:
        id: louder_mediaplayer
        volume: 10%

sp32:
  board: esp32-s3-devkitc-1
  variant: ESP32S3
  flash_size: 16MB
  framework:
    type: arduino

# Enable logging
logger:

# Enable Home Assistant API
api:
  encryption:
    key: !secret esphome_api_key

ota:
  - platform: esphome
    password: !secret esphome_ota_password

wifi:
  ssid: !secret esphome_wifi_ssid
  password: !secret esphome_wifi_password

  ap:
    ssid: "Fallback Hotspot"
    password: !secret esphome_ap_password

captive_portal:

psram:
  mode: octal
  speed: 80Mhz

external_components:
  - source: github://mrtoy-me/esphome-component-test@main
    components: [ tas5805m_enable, tas5805m ]
    refresh: 1s

i2c:
  sda: GPIO8
  scl: GPIO9
  frequency: 100kHz
  timeout: 10ms
  scan: True

tas5805m_enable:
  enable_pin: GPIO17

tas5805m:

switch:
  - platform: tas5805m
    name: "Deep Sleep mode"

i2s_audio:
  i2s_lrclk_pin: GPIO15
  i2s_bclk_pin: GPIO14

media_player:
  - platform: i2s_audio
    name: louder mediaplayer
    id: louder_mediaplayer
    dac_type: external
    i2s_dout_pin: GPIO16
    mode: stereo
```