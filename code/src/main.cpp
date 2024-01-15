// Standard libraries
#include <Arduino.h>
#include "T10_V20.h"
#include <TFT_eSPI.h>
#include <WiFi.h>
#include "time.h"

#include "fcn_tft.h"
#include "fcn_time.h"
#include "fcn_buttons.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void task_time(void * parameters){
  for (;;){
    update_time();
    serialPrintLocalTime();
    if (timeinfo.tm_hour >= lasthour + 4)   //update every 4 hours
      syncWiFi();
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);
  button_init();
  tft_init();     
  syncWiFi();
  serialPrintLocalTime();
  delay(100);

  xTaskCreate(task_time, "Update display", 4000, NULL, 1, NULL);
}

void loop()
{
  button_loop();
  delay(50);
}
