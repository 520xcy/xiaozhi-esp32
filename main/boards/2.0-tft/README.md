# 2.0-TFT 小智AI 机器人

`2.0-tft` 板子是基于 ESP32-S3 的一款小智AI 硬件。它在保留小智AI 语音对话能力的同时，集成了：

- ST7789 240x320 TFT 屏幕（Otto 表情显示）
- ES8311 音频编解码器（通过 I2C 控制）
- 6 路 SG90 舵机（左/右腿、左/右脚、左/右手），支持完整的 Otto 机器人动作库
- 锂电池 + 充电检测
- 3 颗物理按键（BOOT / VOL_UP / VOL_DOWN）

## 引脚定义

| 模块 | 信号 | GPIO |
|------|------|------|
| I2S | MCLK | 12 |
| I2S | BCLK | 11 |
| I2S | WS   | 9  |
| I2S | DOUT | 8  |
| I2S | DIN  | 10 |
| Codec | PA  | 15 |
| Codec I2C | SDA | 14 |
| Codec I2C | SCL | 13 |
| LCD (ST7789) | SCLK | 4  |
| LCD | MOSI | 3  |
| LCD | RST  | 2  |
| LCD | DC   | 6  |
| LCD | CS   | 5  |
| LCD 背光 | BL | 1 (反相) |
| 按键 | BOOT  | 0  |
| 按键 | VOL+  | 47 |
| 按键 | VOL-  | 48 |
| 舵机 | RIGHT_LEG  | 38 |
| 舵机 | RIGHT_FOOT | 39 |
| 舵机 | LEFT_LEG   | 40 |
| 舵机 | LEFT_FOOT  | 41 |
| 舵机 | LEFT_HAND  | 42 |
| 舵机 | RIGHT_HAND | 45 |
| 电源 | 充电检测 | 7 (低电平 = 充电中) |
| 电源 | 电池 ADC | ADC1_CH6 (与充电共用) |
| RTC | 唤醒保持 | GPIO 21 |

## 按键操作

- **BOOT** 单击：唤醒/进入对话
- **BOOT** 单击（启动阶段）：进入 Wi-Fi 配网
- **BOOT** 按住：开始聆听
- **VOL+** 单击：音量 +10
- **VOL+** 长按：静音
- **VOL-** 单击：音量 -10
- **VOL-** 长按：最大音量

## 编译与烧录

1. 选择 board type：`Board Type -> 小智AI 2.0-TFT (Otto 机器人)`
2. 选择目标芯片：ESP32-S3
3. 编译：`idf.py build`
4. 烧录：`idf.py -p <PORT> flash monitor`

## Otto 动作说明

完整动作能力由 `otto_controller.cc` + `otto_movements.cc` 提供，并通过 MCP 工具 `self.otto.action` 暴露给 AI。
支持基础动作（walk / turn / jump / swing / moonwalk / bend / shake_leg / updown / whirlwind_leg）、
固定动作（sit / showcase / home）和手部动作（hands_up / hands_down / hand_wave / windmill /
takeoff / fitness / greeting / shy / radio_calisthenics / magic_circle）。

舵机微调通过 NVS（`otto_trims` 命名空间）持久化，可调用 `self.otto.set_trim` 校准每个舵机。

## 文件结构

```
boards/2.0-tft/
├── 2.0-tft.cc           # 板级主入口
├── config.h             # 引脚 / 硬件配置 + HardwareConfig 结构
├── config.json          # 构建配置
├── oscillator.h / .cc   # LEDC 舵机正弦振荡
├── otto_movements.h/.cc # 舵机运动库（Walk / Turn / Jump / Hand ...）
├── otto_controller.cc   # MCP 工具注册 + 动作队列
├── otto_emoji_display.h/.cc  # Otto 表情显示
├── otto_icon_font.c     # Otto 状态图标
├── power_manager.h      # ADC 电池 + 充电检测
└── README.md
```

## 与 xiaozhi-tft2.0 仓库 2.0-tft 的差异

| 项目 | xiaozhi-tft2.0 | xiaozhi-esp32 |
|------|----------------|---------------|
| 框架 | 旧版 application | 新版 application + mcp_server |
| 屏幕 | OttoEmojiDisplay | OttoEmojiDisplay（继承自 SpiLcdDisplay） |
| 网络 | WifiBoard | WifiBoard |
| 动作注册 | iot::Thing + DECLARE_THING | McpServer::AddTool |
| 电池管理 | PowerManager (源仓库版本) | PowerManager (otto-robot 版本) |
| 电量统计 | 多档位表查 | 线性插值 |
