#ifndef AW9310X_REG_H
#define AW9310X_REG_H

#include <stdint.h>

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

struct aw9310x_reg_default_val {
  uint16_t addr;
  uint32_t data;
};

static const struct aw9310x_reg_default_val aw9310x_reg_default[] = {
  { .addr = 0x0000, .data = 0x00001F1F },
  { .addr = 0x0004, .data = 0x03F0000A },
  { .addr = 0x0008, .data = 0x0017A13E },
  { .addr = 0x000C, .data = 0x05000000 },
  { .addr = 0x0010, .data = 0x00063ffd },
  { .addr = 0x0014, .data = 0x00000009 },
  { .addr = 0x0018, .data = 0xD81C8207 },
  { .addr = 0x001C, .data = 0xFF000000 },
  { .addr = 0x0020, .data = 0x00000000 },
  { .addr = 0x0024, .data = 0x00063ff7 },
  { .addr = 0x0028, .data = 0x00000009 },
  { .addr = 0x002C, .data = 0xD81C8207 },
  { .addr = 0x0030, .data = 0xFF000000 },
  { .addr = 0x0034, .data = 0x00000000 },
  { .addr = 0x0038, .data = 0x00063fdf },
  { .addr = 0x003C, .data = 0x00000009 },
  { .addr = 0x0040, .data = 0xD81C8207 },
  { .addr = 0x0044, .data = 0xFF000000 },
  { .addr = 0x0048, .data = 0x00000000 },
  { .addr = 0x004C, .data = 0x00063f7f },
  { .addr = 0x0050, .data = 0x00000009 },
  { .addr = 0x0054, .data = 0xD81C8207 },
  { .addr = 0x0058, .data = 0xFF000000 },
  { .addr = 0x005C, .data = 0x00000000 },
  { .addr = 0x0060, .data = 0x00063dff },
  { .addr = 0x0064, .data = 0x00000009 },
  { .addr = 0x0068, .data = 0xD81C8207 },
  { .addr = 0x006C, .data = 0xFF000000 },
  { .addr = 0x0070, .data = 0x00000000 },
  { .addr = 0x0074, .data = 0x00050000 },
  { .addr = 0x0078, .data = 0x00000009 },
  { .addr = 0x007C, .data = 0xD81C8207 },
  { .addr = 0x0080, .data = 0xFF000000 },
  { .addr = 0x0084, .data = 0x00000000 },
  { .addr = 0x00A0, .data = 0xE0400000 },
  { .addr = 0x00A4, .data = 0x00000000 },
  { .addr = 0x00A8, .data = 0x000008D2 },
  { .addr = 0x00AC, .data = 0x00000000 },
  { .addr = 0x00B0, .data = 0x00000000 },
  { .addr = 0x00B8, .data = 0x000186A0 },
  { .addr = 0x00BC, .data = 0x00000000 },
  { .addr = 0x00C0, .data = 0x00000000 },
  { .addr = 0x00C4, .data = 0x00000000 },
  { .addr = 0x00C8, .data = 0x00000000 },
  { .addr = 0x00CC, .data = 0x00000000 },
  { .addr = 0x00D0, .data = 0x00000000 },
  { .addr = 0x00D4, .data = 0x00000000 },
  { .addr = 0x00D8, .data = 0x00000000 },
  { .addr = 0x00DC, .data = 0xE0400000 },
  { .addr = 0x00E0, .data = 0x00000000 },
  { .addr = 0x00E4, .data = 0x000008D2 },
  { .addr = 0x00E8, .data = 0x00000000 },
  { .addr = 0x00EC, .data = 0x00000000 },
  { .addr = 0x00F4, .data = 0x000186A0 },
  { .addr = 0x00F8, .data = 0x00000000 },
  { .addr = 0x00FC, .data = 0x00000000 },
  { .addr = 0x0100, .data = 0x00000000 },
  { .addr = 0x0104, .data = 0x00000000 },
  { .addr = 0x0108, .data = 0x00000000 },
  { .addr = 0x010C, .data = 0x00000000 },
  { .addr = 0x0110, .data = 0x00000000 },
  { .addr = 0x0114, .data = 0x00000000 },
  { .addr = 0x0118, .data = 0xE0400000 },
  { .addr = 0x011C, .data = 0x00000000 },
  { .addr = 0x0120, .data = 0x000008D2 },
  { .addr = 0x0124, .data = 0x00000000 },
  { .addr = 0x0128, .data = 0x00000000 },
  { .addr = 0x0130, .data = 0x000186A0 },
  { .addr = 0x0134, .data = 0x00000000 },
  { .addr = 0x0138, .data = 0x00000000 },
  { .addr = 0x013C, .data = 0x00000000 },
  { .addr = 0x0140, .data = 0x00000000 },
  { .addr = 0x0144, .data = 0x00000000 },
  { .addr = 0x0148, .data = 0x00000000 },
  { .addr = 0x014C, .data = 0x00000000 },
  { .addr = 0x0150, .data = 0x00000000 },
  { .addr = 0x0154, .data = 0xE0400000 },
  { .addr = 0x0158, .data = 0x00000000 },
  { .addr = 0x015C, .data = 0x000008D2 },
  { .addr = 0x0160, .data = 0x00000000 },
  { .addr = 0x0164, .data = 0x00000000 },
  { .addr = 0x016C, .data = 0x000186A0 },
  { .addr = 0x0170, .data = 0x00000000 },
  { .addr = 0x0174, .data = 0x00000000 },
  { .addr = 0x0178, .data = 0x00000000 },
  { .addr = 0x017C, .data = 0x00000000 },
  { .addr = 0x0180, .data = 0x00000000 },
  { .addr = 0x0184, .data = 0x00000000 },
  { .addr = 0x0188, .data = 0x00000000 },
  { .addr = 0x018C, .data = 0x00000000 },
  { .addr = 0x0190, .data = 0xE0400000 },
  { .addr = 0x0194, .data = 0x00000000 },
  { .addr = 0x0198, .data = 0x000008D2 },
  { .addr = 0x019C, .data = 0x00000000 },
  { .addr = 0x01A0, .data = 0x00000000 },
  { .addr = 0x01A8, .data = 0x000186A0 },
  { .addr = 0x01AC, .data = 0x00000000 },
  { .addr = 0x01B0, .data = 0x00000000 },
  { .addr = 0x01B4, .data = 0x00000000 },
  { .addr = 0x01B8, .data = 0x00000000 },
  { .addr = 0x01BC, .data = 0x00000000 },
  { .addr = 0x01C0, .data = 0x00000000 },
  { .addr = 0x01C4, .data = 0x00000000 },
  { .addr = 0x01C8, .data = 0x00000000 },
  { .addr = 0x01CC, .data = 0xE0400000 },
  { .addr = 0x01D0, .data = 0x00000000 },
  { .addr = 0x01D4, .data = 0x000008D2 },
  { .addr = 0x01D8, .data = 0x00000000 },
  { .addr = 0x01DC, .data = 0x00000000 },
  { .addr = 0x01E4, .data = 0x00000000 },
  { .addr = 0x01E8, .data = 0x00000000 },
  { .addr = 0x01EC, .data = 0x00000000 },
  { .addr = 0x01F0, .data = 0x00000000 },
  { .addr = 0x01F4, .data = 0x00000000 },
  { .addr = 0x01F8, .data = 0x00000000 },
  { .addr = 0x01FC, .data = 0x00000000 },
  { .addr = 0x0200, .data = 0x00000000 },
  { .addr = 0x0204, .data = 0x00000000 },
  { .addr = 0x0208, .data = 0x00000005 },
  { .addr = 0x020C, .data = 0x00000005 },
  { .addr = 0x41FC, .data = 0x00000000 },
  { .addr = 0x4400, .data = 0x00000000 },
  { .addr = 0x4410, .data = 0x00000000 },
  { .addr = 0x4420, .data = 0x00000000 },
  { .addr = 0x4430, .data = 0x00000000 },
  { .addr = 0x4440, .data = 0x00000000 },
  { .addr = 0x4450, .data = 0x00000000 },
  { .addr = 0x4460, .data = 0x00000000 },
  { .addr = 0x4470, .data = 0x00000000 },
  { .addr = 0xF084, .data = 0x00000006 },
  { .addr = 0xF800, .data = 0x00000000 },
  { .addr = 0xF804, .data = 0x00004C00 },
  { .addr = 0xF8C0, .data = 0x00000000 },
  { .addr = 0xF8D0, .data = 0x00000000 },
  { .addr = 0xF8D4, .data = 0x00000000 },
  { .addr = 0xFF00, .data = 0x00000301 },
  { .addr = 0xFF0C, .data = 0x01000000 },
  { .addr = 0xFFE0, .data = 0x00000000 },
  { .addr = 0xFFF0, .data = 0x00000000 },
  { .addr = 0xFFF4, .data = 0x00004011 },
  { .addr = 0xFFF8, .data = 0x00000000 },
  { .addr = 0xFFFC, .data = 0x00000000 },
  { .addr = 0x009C, .data = 0x3F3F3F3F },
};

#endif // AW9310X_REG_H
