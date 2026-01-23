#include <U8g2lib.h>

#define OLED_SDA 5
#define OLED_SCL 6
#define OLED_RESET U8X8_PIN_NONE

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_RESET, OLED_SCL, OLED_SDA);
int width = 40;
int height = 72;
int xOffset = 0;
int yOffset = height / 2;

void disp_init()
{
	u8g2.begin();
	u8g2.setContrast(255);
	u8g2.setBusClock(400000);
	u8g2.setDisplayRotation(U8G2_R3);
	u8g2.setFontPosTop();
	u8g2.setFontMode(0);
}
