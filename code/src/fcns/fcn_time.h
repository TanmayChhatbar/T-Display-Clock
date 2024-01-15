const char* ntpServer = "time1.google.com";
int lasthour;
int time_hr = 0;
int time_min = 0;
String stime_hr = "";
String stime_min = "";
const long  gmtOffset_sec = -18000;
const int   daylightOffset_sec = 0;
struct tm timeinfo;
String sep = " ";

const char * dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char * monthNames[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
char ctime_hr[2];
char ctime_min[2];

#if __has_include("credentials.h")
#include "credentials.h"
#else
#error "Network credentials need setup. Comment line out once done"
const char* ssid[] = {"SSID1", "SSID2"};
const char* password   = "E701D204";
#endif

const int conlen = 2;
int con = 0;
unsigned long timer1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void syncWiFi() {
y:
  Serial.printf("Connecting to %s", ssid[con]);
  WiFi.begin(ssid[con], password);
  con++;
  if (con >= conlen)
    con = 0;
  timer1 = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() - timer1 > 10000)
    {
      goto y;
    }
  }
  int ip = WiFi.localIP()[3];
  Serial.println("");
  Serial.print("WiFi Connected\nIP Address: ");
  Serial.println(WiFi.localIP());
  delay(1);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  while (!getLocalTime(&timeinfo)) {
    delay(100);
  }
  lasthour = timeinfo.tm_hour;

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int serialPrintLocalTime() {          //returns 1 if error, else 0
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    Serial.println("Changing WiFi");
    syncWiFi();
    return 1;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

String yearstr() {
  String month = monthNames[timeinfo.tm_mon];
  return month + " " + timeinfo.tm_mday + ", " + (1900+timeinfo.tm_year);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_time(){
  sprintf(ctime_hr, "%02d", (timeinfo.tm_hour%12==0)?12:timeinfo.tm_hour%12);
  stime_hr = String(ctime_hr);

  sprintf(ctime_min, "%02d", timeinfo.tm_min);
  stime_min = String(ctime_min);

  // separator
  if (timeinfo.tm_sec % 2 == 0)
    sep = ":";
  else
    sep = " ";

  // construct string
  String time = stime_hr + sep + stime_min;
  
  // pre-print
  spr.setTextDatum(TL_DATUM); // Set datum to bottom centre
  spr.fillRect(12, 4, 120, 20, TXT_BACKGROUND);
  spr.setTextColor(TXT_POSITIVE, TXT_BACKGROUND);
  
  // time
  spr.setTextFont(7);
  spr.setTextSize(1);
  spr.drawString(time, 10, 16);

  // weekday
  spr.setTextFont(1);
  spr.setTextSize(2);
  spr.drawString(dayNames[timeinfo.tm_wday], 10, 78);
  spr.drawString(yearstr(), 8, 106);
  spr.pushSprite(0,0);
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