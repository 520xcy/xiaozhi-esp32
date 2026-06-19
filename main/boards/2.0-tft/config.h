#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/adc.h>
#include <driver/gpio.h>

// ===================== 音频 I2S =====================
#define AUDIO_INPUT_SAMPLE_RATE  24000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000
#define AUDIO_INPUT_REFERENCE    true

#define AUDIO_I2S_GPIO_MCLK GPIO_NUM_12
#define AUDIO_I2S_GPIO_WS   GPIO_NUM_9
#define AUDIO_I2S_GPIO_BCLK GPIO_NUM_11
#define AUDIO_I2S_GPIO_DIN  GPIO_NUM_10
#define AUDIO_I2S_GPIO_DOUT GPIO_NUM_8

// ===================== 音频编解码器 (ES8311) =====================
#define AUDIO_CODEC_PA_PIN        GPIO_NUM_15
#define AUDIO_CODEC_I2C_SDA_PIN   GPIO_NUM_14
#define AUDIO_CODEC_I2C_SCL_PIN   GPIO_NUM_13
#define AUDIO_CODEC_ES8311_ADDR   ES8311_CODEC_DEFAULT_ADDR

// ===================== 按键 / LED =====================
#define BUILTIN_LED_GPIO        GPIO_NUM_NC
#define BOOT_BUTTON_GPIO        GPIO_NUM_0
#define VOLUME_UP_BUTTON_GPIO   GPIO_NUM_47
#define VOLUME_DOWN_BUTTON_GPIO GPIO_NUM_48

// ===================== LCD (ST7789 SPI) =====================
#define ST7789_GPIO_SCLK GPIO_NUM_4
#define ST7789_GPIO_MOSI GPIO_NUM_3
#define ST7789_GPIO_RST  GPIO_NUM_2
#define ST7789_GPIO_DC   GPIO_NUM_6
#define ST7789_GPIO_CS   GPIO_NUM_5

#define DISPLAY_WIDTH       240
#define DISPLAY_HEIGHT      320
#define DISPLAY_SWAP_XY     false
#define DISPLAY_MIRROR_X    false
#define DISPLAY_MIRROR_Y    false
#define DISPLAY_INVERT_COLOR true
#define DISPLAY_RGB_ORDER   LCD_RGB_ELEMENT_ORDER_RGB
#define DISPLAY_OFFSET_X    0
#define DISPLAY_OFFSET_Y    0
#define DISPLAY_SPI_MODE    0

#define DISPLAY_BACKLIGHT_PIN             GPIO_NUM_1
#define DISPLAY_BACKLIGHT_OUTPUT_INVERT   true

// ===================== Otto 机器人舵机 (6 路) =====================
#define RIGHT_LEG_PIN  GPIO_NUM_38
#define RIGHT_FOOT_PIN GPIO_NUM_39
#define LEFT_LEG_PIN   GPIO_NUM_40
#define LEFT_FOOT_PIN  GPIO_NUM_41
#define LEFT_HAND_PIN  GPIO_NUM_42
#define RIGHT_HAND_PIN GPIO_NUM_45

// ===================== 电源管理 =====================
// 充电检测引脚（低电平表示正在充电）
#define POWER_CHARGE_DETECT_PIN  GPIO_NUM_7
// 电池电压采样：ADC1_CHANNEL_6（GPIO7 同时为充电检测，复用引脚）
#define POWER_ADC_UNIT           ADC_UNIT_1
#define POWER_ADC_CHANNEL        ADC_CHANNEL_6

// RTC GPIO 唤醒（用于 PowerSaveTimer）
#define POWER_WAKEUP_GPIO        GPIO_NUM_21

// ===================== 硬件配置结构 =====================
// Otto 控制器需要的统一硬件配置（仅填充 2.0-tft 实际使用的字段）
struct HardwareConfig {
    gpio_num_t power_charge_detect_pin;
    adc_unit_t power_adc_unit;
    adc_channel_t power_adc_channel;

    gpio_num_t right_leg_pin;
    gpio_num_t right_foot_pin;
    gpio_num_t left_leg_pin;
    gpio_num_t left_foot_pin;
    gpio_num_t left_hand_pin;
    gpio_num_t right_hand_pin;
};

constexpr HardwareConfig BOARD_HARDWARE_CONFIG = {
    .power_charge_detect_pin = POWER_CHARGE_DETECT_PIN,
    .power_adc_unit          = POWER_ADC_UNIT,
    .power_adc_channel       = POWER_ADC_CHANNEL,

    .right_leg_pin           = RIGHT_LEG_PIN,
    .right_foot_pin          = RIGHT_FOOT_PIN,
    .left_leg_pin            = LEFT_LEG_PIN,
    .left_foot_pin           = LEFT_FOOT_PIN,
    .left_hand_pin           = LEFT_HAND_PIN,
    .right_hand_pin          = RIGHT_HAND_PIN,
};

#endif // _BOARD_CONFIG_H_
