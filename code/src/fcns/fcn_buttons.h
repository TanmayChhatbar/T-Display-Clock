#include <Button2.h>
#include <Ticker.h>
// with USB side as top
// pos - state
// top - 1
// mid - 2
// bot - 3

// buttons
uint8_t state = 0;
Button2 *pBtns = nullptr;
uint8_t g_btns[] =  BUTTONS_MAP;
char buff[512];
Ticker btnscanT;

void button_handle(uint8_t gpio) {
  switch (gpio) {
#ifdef BUTTON_1
    case BUTTON_1: {
        state = 1;
        brightness = brightness + 20;
        if (brightness > 255)
          brightness = 255;
      }
      break;
#endif

#ifdef BUTTON_2
    case BUTTON_2: {
        state = 2;
        brightness = brightness - 20;
        if (brightness < 1)
          brightness = 1;
      }
      break;
#endif

#ifdef BUTTON_3
    case BUTTON_3: {
        state = 3;
        brightness = 0;
      }
      break;
#endif

#ifdef BUTTON_4
    case BUTTON_4: {
        state = 4;
      }
      break;
#endif
    default:
      break;
  }
  Serial.print("Brightness = ");
  Serial.println(brightness);
  analogWrite(TFT_BL, brightness);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void button_callback(Button2 &b) {
  for (int i = 0; i < sizeof(g_btns) / sizeof(g_btns[0]); ++i) {
    if (pBtns[i] == b) {
      button_handle(pBtns[i].getAttachPin());
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void button_init() {
  uint8_t args = sizeof(g_btns) / sizeof(g_btns[0]);
  pBtns = new Button2 [args];
  for (int i = 0; i < args; ++i) {
    pBtns[i] = Button2(g_btns[i]);
    pBtns[i].setPressedHandler(button_callback);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void button_loop() {
  for (int i = 0; i < sizeof(g_btns) / sizeof(g_btns[0]); ++i) {
    pBtns[i].loop();
  }
}
