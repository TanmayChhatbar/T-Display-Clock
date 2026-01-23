// Standard libraries
#include <Arduino.h>
#include <WiFi.h>
#include "time.h"

#include "fcn_tft.h"
#include "fcn_time.h"

void task_time(void *parameters)
{
  for (;;)
  {
    update_time();
    if (timeinfo.tm_hour >= lasthour + 4) // update every 4 hours
      syncWiFi();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  disp_init();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_9x15_tr);
  u8g2.drawStr(xOffset + 0, yOffset + 40, "WiFi");
  u8g2.sendBuffer();

  syncWiFi();
  delay(100);

  xTaskCreate(task_time, "Update display", 4000, NULL, 1, NULL);
}

void loop(void)
{
  delay(1000);
}
