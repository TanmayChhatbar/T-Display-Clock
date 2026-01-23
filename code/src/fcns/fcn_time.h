#include <Arduino.h>
char *ntpServer = "time1.google.com";
const String timezone = "EST5EDT,M3.2.0,M11.1.0"; // get from https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv

int lasthour;
int time_hr = 0;
int time_min = 0;
String stime_hr = "";
String stime_min = "";
struct tm timeinfo;
String sep = " ";

const char *dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char *monthNames[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
char ctime_hr[2];
char ctime_min[2];

#include "credentials.h"

const int conlen = 2;
int con = 0;
unsigned long timer1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setTimezone(String timezone)
{
  // Serial.printf("  Setting Timezone to %s\n",timezone.c_str());
  setenv("TZ", timezone.c_str(), 1); //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void syncWiFi()
{
y:
  WiFi.begin(ssid[con], password);
  con++;
  if (con >= conlen)
    con = 0;
  timer1 = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    if (millis() - timer1 > 10000)
    {
      goto y;
    }
  }
  int ip = WiFi.localIP()[3];
  delay(1);
  configTzTime(timezone.c_str(), ntpServer);
  while (!getLocalTime(&timeinfo))
  {
    delay(100);
  }
  lasthour = timeinfo.tm_hour;
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

String yearstr()
{
  String month = monthNames[timeinfo.tm_mon];
  return month + " " + timeinfo.tm_mday + ", " + (1900 + timeinfo.tm_year);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void  update_time()
{
  getLocalTime(&timeinfo);
  sprintf(ctime_hr, "%02d", (timeinfo.tm_hour % 12 == 0) ? 12 : timeinfo.tm_hour % 12);
  stime_hr = String(ctime_hr);

  sprintf(ctime_min, "%02d", timeinfo.tm_min);
  stime_min = String(ctime_min);

  // separator
  if (int(timeinfo.tm_sec) % 2 == 0)
    sep = ":";
  else
    sep = " ";

  // construct string
  String time = stime_hr + sep + stime_min;

  // wipe screen
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_9x15_tr);
  u8g2.drawStr(xOffset + 0, yOffset + 30, time.c_str());

  // weekday
  u8g2.setFont(u8g2_font_4x6_tr);
  u8g2.drawStr(xOffset + 0, yOffset + 40, dayNames[timeinfo.tm_wday]);
  u8g2.drawStr(xOffset + 0, yOffset + 50, yearstr().c_str());
  u8g2.sendBuffer();
}

//{
//   int tm_sec;         /* seconds,  range 0 to 59          */
//   int tm_min;         /* minutes, range 0 to 59           */
//   int tm_hour;        /* hours, range 0 to 23             */
//   int tm_mday;        /* day of the month, range 1 to 31  */
//   int tm_mon;         /* month, range 0 to 11             */
//   int tm_year;        /* The number of years since 1900   */
//   int tm_wday;        /* day of the week, range 0 to 6    */
//   int tm_yday;        /* day in the year, range 0 to 365  */
//   int tm_isdst;       /* daylight saving time             */
//}
