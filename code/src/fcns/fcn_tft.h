#include <U8g2lib.h>

#define OLED_SDA 5
#define OLED_SCL 6
#define OLED_RESET U8X8_PIN_NONE

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_RESET, OLED_SCL, OLED_SDA);
int width = 72;
int height = 40;
int xOffset = 30;  // = (132-w)/2
int yOffset = 12;  // = (64-h)/2
int brightness = 32;

#ifndef LIGHTMODE
#define TXT_PRIMARY TFT_WHITE
#define TXT_BACKGROUND TFT_BLACK
#else
#define TXT_PRIMARY TFT_BLACK
#define TXT_BACKGROUND TFT_WHITE
#endif

void disp_init() {
  u8g2.begin();
  u8g2.setContrast(255);     // set contrast to maximum
  u8g2.setBusClock(400000);  //400kHz I2C
}
