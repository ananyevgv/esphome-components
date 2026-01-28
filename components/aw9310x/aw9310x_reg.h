#ifndef AW9310X_REG_H
#define AW9310X_REG_H

// Основные регистры AW9310X
#define REG_SCANCTRL0          0x0000
#define REG_HOSTCTRL2          0xFF0C
#define REG_CHIP_ID            0xFF10
#define REG_CMD                0xF008
#define REG_HOSTIRQSRC         0xF080
#define REG_HOSTIRQEN          0xF084
#define REG_STAT0              0x0090

#define REG_DIFF_CH0           0x0240
#define REG_DIFF_CH1           0x0244
#define REG_DIFF_CH2           0x0248
#define REG_DIFF_CH3           0x024c
#define REG_DIFF_CH4           0x0250
#define REG_DIFF_CH5           0x0254

#define REG_PROXTH0_CH0        0x00B8
#define REG_PROXTH0_CH1        0x00F4
#define REG_PROXTH0_CH2        0x0130
#define REG_PROXTH0_CH3        0x016C
#define REG_PROXTH0_CH4        0x01A8
#define REG_PROXTH0_CH5        0x01E4

#define AW9310X_CHIP_ID        0xA961

#endif // AW9310X_REG_H