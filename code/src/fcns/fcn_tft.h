TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
unsigned long scr_del = 0, scr_up = 0;
bool up = 0;
int brightness = 32;

#ifndef LIGHTMODE
#define TXT_PRIMARY TFT_WHITE
#define TXT_BACKGROUND TFT_BLACK
#define TXT_POSITIVE TFT_GREEN
#define TXT_NEGATIVE TFT_ORANGE
#define TXT_NEUTRAL TFT_ORANGE
#define TXT_SECONDARY TFT_WHITE
#else
#define TXT_PRIMARY TFT_BLACK
#define TXT_BACKGROUND TFT_WHITE
#define TXT_POSITIVE TFT_DARKGREEN
#define TXT_NEGATIVE TFT_RED
#define TXT_NEUTRAL TFT_ORANGE
#define TXT_SECONDARY TFT_DARKGREY
#endif

void tft_init() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TXT_BACKGROUND);
  spr.createSprite(TFT_HEIGHT, TFT_WIDTH);
  spr.fillScreen(TXT_BACKGROUND);
  spr.setTextColor(TXT_PRIMARY);

  pinMode(TFT_BL, OUTPUT);  
  analogWrite(TFT_BL, brightness);
}