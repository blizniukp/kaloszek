#define ESP8266 1

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <GxEPD2_BW.h>
#include <JsonListener.h>

#include "weatherapi.h"
#include "kaloszek_config.h"
#include "MAX17048.h"

#define USE_EPD 1
#define USE_WIFI 1

#define USE_WEATHERAPI 1
#define USE_HOURLY_FORCAST 1

#define USE_WIFI_ICO 1

#define PRINT_WEATHER 1

#define USE_MAX17048 1
//#define USE_AIRLY 1

#define UPDATE_PERIOD 1800  //seconds
#define WIFI_ERR_PERIOD 1   //seconds

#include "epd_winddir.h"
#include "epd_iconpack.h"
#include "epd_main_iconpack.h"
#include "epd_info_iconpack.h"
#include "epd_info_small_iconpack.h"

#include "data/fonts/OpenSansBold26ptExt.h"
#include "data/fonts/OpenSansBold56ptExt.h"
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include "data/fonts/RobotoMedPlain18.h"

GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS=D8 ss*/ 15, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));

const char str_sleep[] = "I'm going to sleep for ";
const char str_seconds[] = " seconds";
const char str_weatherapi_err[] = "WeatherApi error";
const char str_wifi_err[] = "Error :(";
const char str_db[] = "dB";
const char str_st1_c[] = "*C";
const char str_uvindex[] = "UV:";
const char str_hpa[] = "hPa";
const char str_percent[] = "% ";
const char str_kmh[] = "km/h";
const char str_bat_error[] = "Battery error";

WeatherApiHourlyData dataH[12];
WeatherApiCurrentData dataC;

int wifi_connection_status;
int weather_status;
#ifdef USE_AIRLY
int airly_status;
#endif

MAX17048 pwr_mgmt;

const uint16_t pos_x_big_ico = 260;

WeatherApi aw(weatherapi_key, 1988803);
#ifdef USE_AIRLY
#include "AirlyApi.h"
AirlyApi airlyApi(airly_key, airly_latitude, airly_longitude, distance);
#endif

int wifi_connect() {
  int i = 100;

  Serial.print("Connecting to: ");
  Serial.println(ssid_1);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_1, password_1);

  do {
    if (WiFi.status() == WL_CONNECTED) break;

    delay(100);
    yield();
    Serial.println("Connecting to WiFi..");
  } while (--i);

  if (i) {
    Serial.println("Connected to the WiFi network :)");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    return 0;
  } else {
    Serial.println("WiFi error");
  }
  return -1;
}

int get_weather() {
#ifdef USE_WEATHERAPI
  int timeStart = millis();

  int ret = aw.getForecast(&dataC);

  if (ret != 0) {
    Serial.print("WeatherApi ERROR: ");
    Serial.println(ret);
    return ret;
  }

  while (aw.continueDownload() > 0) {
  }

#ifdef PRINT_WEATHER
  print_actual_weather();
#endif

  timeStart = millis() - timeStart;

  Serial.printf("Downloaded and parsed in %d ms\n", timeStart);
  Serial.println(String(ESP.getFreeHeap()));

  return 0;
#else  //fake data - epd test
  dataC.WeatherText = "Mostly cloudy";
  dataC.WeatherIcon = 7;
  dataC.Temperature = -16.60;
  dataC.RealFeelTemperature = 16.60;
  dataC.RelativeHumidity = 77.00;
  dataC.WindDirection = 115;
  dataC.WindSpeed = 6.70;
  dataC.UVIndex = 1;
  dataC.Pressure = 1023.00;
  return 0;
#endif
}

void display_forecast(int idx, int x_pos_temp, int y_pos_temp, int x_pos_time, int y_pos_time) {
  // int my_temp = (int)(round(dataH[idx].Temperature));
  char new_date[32];
  char new_data[8];

  display.setFont(&Open_Sans_Bold_26pt_Ext);
  display.setCursor(x_pos_temp + 10, y_pos_temp);
  //  display.print(my_temp);
  display.print("*C");

  display.setFont(&FreeSansBold9pt7b);
  //  dataH[idx].DateTime.toCharArray(new_date, 20);
  memmove(new_date, new_date + 11, 8);
  memcpy(new_data, new_date, 5);
  new_data[5] = 0;
  display.setCursor(x_pos_time, y_pos_time);
  display.print(new_data);

  // display_hourly_weather_icon(dataH[idx].WeatherIcon, x_pos_time - 5, y_pos_temp - 85);
}

void display_wind_dir(int16_t direct, int x_pos, int y_pos) {
  int size_w = 50;
  int size_h = 50;

  if ((direct >= 23) && (direct < 68))  // ("NE");
    display.drawBitmap(x_pos, y_pos, winddir7, size_w, size_h, GxEPD_BLACK);
  else if ((direct >= 68) && (direct < 113))  // ("E");
    display.drawBitmap(x_pos, y_pos, winddir8, size_w, size_h, GxEPD_BLACK);
  else if ((direct >= 113) && (direct < 158))  // ("SE");
    display.drawBitmap(x_pos, y_pos, winddir4, size_w, size_h, GxEPD_BLACK);
  else if ((direct >= 158) && (direct < 203))  // ("S");
    display.drawBitmap(x_pos, y_pos, winddir2, size_w, size_h, GxEPD_BLACK);
  else if ((direct >= 203) && (direct < 248))  // ("SW");
    display.drawBitmap(x_pos, y_pos, winddir3, size_w, size_h, GxEPD_BLACK);
  else if ((direct >= 248) && (direct < 293))  // ("W");
    display.drawBitmap(x_pos, y_pos, winddir1, size_w, size_h, GxEPD_BLACK);
  else if ((direct >= 293) && (direct < 338))  // ("NW");
    display.drawBitmap(x_pos, y_pos, winddir6, size_w, size_h, GxEPD_BLACK);
  else if ((direct >= 338) || (direct < 23))  // ("N");
    display.drawBitmap(x_pos, y_pos, winddir5, size_w, size_h, GxEPD_BLACK);
}

#ifdef USE_AIRLY
void display_weather(int wifi_connection_status, int w_status, int a_status)
#else
void display_weather(int wifi_connection_status, int w_status)
#endif
{
  char new_date[32];
  char new_data[8];
  float my_temp;

  int pos_y_1_line = 72;   // aktualna temperatura
  int pos_y_2_line = 117;  // temperatura odczuwalna + UV
  int pos_y_w_line = 114;  // opis pogody
  int pos_y_3_line = 144;  // ciśnienie + wilgotność itd
  int pos_y_4_line = 242;
  int pos_y_5_line = 267;
  int pos_y_6_line = 294;

  display.fillScreen(GxEPD_WHITE);
  display.setRotation(0);
  display.setTextColor(GxEPD_BLACK);

  display.fillRect(1, 150, 399, 3, GxEPD_BLACK);
  display.fillRect(1, 278, 399, 2, GxEPD_BLACK);

  if (w_status == 0) {
    display.setFont(&Open_Sans_Bold_56pt_Ext);

    my_temp = round(dataC.Temperature * 10) / 10.0;
    display.setCursor(20, pos_y_1_line);
    display.print(my_temp, 1);
    display.print("*C");

    display.setFont(&Open_Sans_Bold_26pt_Ext);
    display.setCursor(20, pos_y_2_line);

    //   int real_temp = (int)(round(dataC.RealFeelTemperature));
    //  display.print(real_temp);
    //  display.print("*C");

    int info_icon_height = 25;
    show_info_icon(1, 2, pos_y_3_line - info_icon_height);
    display.setFont(&FreeSansBold12pt7b);
    int pressure = int(round(dataC.Pressure));
    display.setCursor(30, pos_y_3_line);
    display.print(pressure);

    show_info_icon(2, 90, pos_y_3_line - info_icon_height);
    //  int humidity = int(round(dataC.RelativeHumidity));
    display.setCursor(120, pos_y_3_line);
    //  display.print(humidity);

    show_info_icon(3, 155, pos_y_3_line - info_icon_height);
    int wind_speed = (int)(round(dataC.WindSpeed));
    display.setCursor(187, pos_y_3_line);
    display.print(wind_speed);

    show_info_icon(4, 240, pos_y_3_line - info_icon_height);
    display_wind_dir(dataC.WindDirection, 268, pos_y_3_line - 30);

    show_info_icon(5, 308, pos_y_3_line - info_icon_height);
    display.setCursor(345, pos_y_3_line);
    //    display.print(((int)(dataH[1].RainProbability + dataH[2].RainProbability + dataH[3].RainProbability) / 3));

    //   display_main_weather_icon(dataC.WeatherIcon, pos_x_big_ico, 4);

    uint16_t pos_x_description = set_weather_description_offset(dataC.WeatherText);

    display.setFont(&Roboto_Medium_18);
    display.setCursor(pos_x_description, pos_y_w_line);
    display.print(dataC.WeatherText);

    display.setFont(&FreeSansBold9pt7b);
    //    dataC.LocalObservationDateTime.toCharArray(new_date, 20);
    //    memmove(new_date, new_date + 11, 8);
    //    memcpy(new_data, new_date, 5);
    new_data[5] = 0;
    display.setCursor(335, pos_y_6_line);
    display.print(new_data);

    display_forecast(2, 10, pos_y_4_line, 25, pos_y_5_line);     //3h
    display_forecast(5, 110, pos_y_4_line, 125, pos_y_5_line);   //6h
    display_forecast(8, 210, pos_y_4_line, 225, pos_y_5_line);   //9h
    display_forecast(11, 310, pos_y_4_line, 325, pos_y_5_line);  //12h
  } else {
    display.setFont(&FreeSansBold9pt7b);
    display.setCursor(232, pos_y_6_line);
    display.print(str_weatherapi_err);
  }
  display.setFont(&FreeSansBold9pt7b);
  display.setCursor(10, pos_y_6_line);

  if (wifi_connection_status == 0)
    display.drawBitmap(6, 281, infoSmallIco1, 19, 19, GxEPD_BLACK);
  else
    display.drawBitmap(6, 281, infoSmallIco2, 19, 19, GxEPD_BLACK);

  display.drawBitmap(30, 281, infoSmallIco3, 19, 19, GxEPD_BLACK);
  display.setCursor(55, pos_y_6_line);
  //int uv_index = (int)(round(dataC.UVIndex));
  //display.print(uv_index);

#ifdef USE_AIRLY
  display.drawBitmap(80, 281, infoSmallIco4, 19, 19, GxEPD_BLACK);
  display.setCursor(105, pos_y_6_line);

  if (a_status == 0) {
    display.print(airlyApi.getAirQualityLevel());
  } else {
    display.print("!");
  }
#endif
  display_battery(pos_y_6_line);

  display.display();
  display.powerOff();
  display.hibernate();

  Serial.println("EPD is sleeping");
}

uint16_t set_weather_description_offset(String str) {
  int16_t tbx, tby;
  uint16_t tbw, tbh;

  display.setFont(&Roboto_Medium_18);
  display.getTextBounds(str.c_str(), 0, 0, &tbx, &tby, &tbw, &tbh);

  uint16_t x_center = pos_x_big_ico + (90 / 2);
  uint16_t pos_x_napisu = (x_center - (tbw / 2)) - tbx;

  return pos_x_napisu;
}

void set_icon_offset(uint8_t w_number, int *x_pos, int *y_pos) {
#ifdef ICON_PACK_3
  switch (w_number) {
    case 3:
      {
        *y_pos += 2;
      }
      break;
    case 38:
      {
        *y_pos += 8;
      }
      break;
  }
#endif
}

void display_hourly_weather_icon(uint8_t w_number, int x_pos, int y_pos) {
  int size_w = 50;
  int size_h = 50;

  set_icon_offset(w_number, &x_pos, &y_pos);

  switch (w_number) {
    case 1: display.drawBitmap(x_pos, y_pos, weatherIco1, size_w, size_h, GxEPD_BLACK); break;
    case 2: display.drawBitmap(x_pos, y_pos, weatherIco2, size_w, size_h, GxEPD_BLACK); break;
    case 3: display.drawBitmap(x_pos, y_pos, weatherIco3, size_w, size_h, GxEPD_BLACK); break;
    case 4: display.drawBitmap(x_pos, y_pos, weatherIco4, size_w, size_h, GxEPD_BLACK); break;
    case 5: display.drawBitmap(x_pos, y_pos, weatherIco5, size_w, size_h, GxEPD_BLACK); break;
    case 6: display.drawBitmap(x_pos, y_pos, weatherIco6, size_w, size_h, GxEPD_BLACK); break;
    case 7: display.drawBitmap(x_pos, y_pos, weatherIco7, size_w, size_h, GxEPD_BLACK); break;
    case 8: display.drawBitmap(x_pos, y_pos, weatherIco8, size_w, size_h, GxEPD_BLACK); break;

    case 11: display.drawBitmap(x_pos, y_pos, weatherIco11, size_w, size_h, GxEPD_BLACK); break;
    case 12: display.drawBitmap(x_pos, y_pos, weatherIco12, size_w, size_h, GxEPD_BLACK); break;
    case 13: display.drawBitmap(x_pos, y_pos, weatherIco13, size_w, size_h, GxEPD_BLACK); break;
    case 14: display.drawBitmap(x_pos, y_pos, weatherIco14, size_w, size_h, GxEPD_BLACK); break;
    case 15: display.drawBitmap(x_pos, y_pos, weatherIco15, size_w, size_h, GxEPD_BLACK); break;
    case 16: display.drawBitmap(x_pos, y_pos, weatherIco16, size_w, size_h, GxEPD_BLACK); break;
    case 17: display.drawBitmap(x_pos, y_pos, weatherIco17, size_w, size_h, GxEPD_BLACK); break;
    case 18: display.drawBitmap(x_pos, y_pos, weatherIco18, size_w, size_h, GxEPD_BLACK); break;
    case 19: display.drawBitmap(x_pos, y_pos, weatherIco19, size_w, size_h, GxEPD_BLACK); break;

    case 20: display.drawBitmap(x_pos, y_pos, weatherIco20, size_w, size_h, GxEPD_BLACK); break;
    case 21: display.drawBitmap(x_pos, y_pos, weatherIco21, size_w, size_h, GxEPD_BLACK); break;
    case 22: display.drawBitmap(x_pos, y_pos, weatherIco22, size_w, size_h, GxEPD_BLACK); break;
    case 23: display.drawBitmap(x_pos, y_pos, weatherIco23, size_w, size_h, GxEPD_BLACK); break;
    case 24: display.drawBitmap(x_pos, y_pos, weatherIco24, size_w, size_h, GxEPD_BLACK); break;
    case 25: display.drawBitmap(x_pos, y_pos, weatherIco25, size_w, size_h, GxEPD_BLACK); break;
    case 26: display.drawBitmap(x_pos, y_pos, weatherIco26, size_w, size_h, GxEPD_BLACK); break;
    case 29: display.drawBitmap(x_pos, y_pos, weatherIco29, size_w, size_h, GxEPD_BLACK); break;

    case 30: display.drawBitmap(x_pos, y_pos, weatherIco30, size_w, size_h, GxEPD_BLACK); break;
    case 31: display.drawBitmap(x_pos, y_pos, weatherIco31, size_w, size_h, GxEPD_BLACK); break;
    case 32: display.drawBitmap(x_pos, y_pos, weatherIco32, size_w, size_h, GxEPD_BLACK); break;
    case 33: display.drawBitmap(x_pos, y_pos, weatherIco33, size_w, size_h, GxEPD_BLACK); break;
    case 34: display.drawBitmap(x_pos, y_pos, weatherIco34, size_w, size_h, GxEPD_BLACK); break;
    case 35: display.drawBitmap(x_pos, y_pos, weatherIco35, size_w, size_h, GxEPD_BLACK); break;
    case 36: display.drawBitmap(x_pos, y_pos, weatherIco36, size_w, size_h, GxEPD_BLACK); break;
    case 37: display.drawBitmap(x_pos, y_pos, weatherIco37, size_w, size_h, GxEPD_BLACK); break;
    case 38: display.drawBitmap(x_pos, y_pos, weatherIco38, size_w, size_h, GxEPD_BLACK); break;
    case 39: display.drawBitmap(x_pos, y_pos, weatherIco39, size_w, size_h, GxEPD_BLACK); break;

    case 40: display.drawBitmap(x_pos, y_pos, weatherIco40, size_w, size_h, GxEPD_BLACK); break;
    case 41: display.drawBitmap(x_pos, y_pos, weatherIco41, size_w, size_h, GxEPD_BLACK); break;
    case 42: display.drawBitmap(x_pos, y_pos, weatherIco42, size_w, size_h, GxEPD_BLACK); break;
    case 43: display.drawBitmap(x_pos, y_pos, weatherIco43, size_w, size_h, GxEPD_BLACK); break;
    case 44: display.drawBitmap(x_pos, y_pos, weatherIco44, size_w, size_h, GxEPD_BLACK); break;
  }
}
void display_main_weather_icon(uint8_t w_number, int x_pos, int y_pos) {
  int size_w = 100;
  int size_h = 100;

  set_icon_offset(w_number, &x_pos, &y_pos);

  switch (w_number) {
    case 1: display.drawBitmap(x_pos, y_pos, bigWeatherIco1, size_w, size_h, GxEPD_BLACK); break;
    case 2: display.drawBitmap(x_pos, y_pos, bigWeatherIco2, size_w, size_h, GxEPD_BLACK); break;
    case 3: display.drawBitmap(x_pos, y_pos, bigWeatherIco3, size_w, size_h, GxEPD_BLACK); break;
    case 4: display.drawBitmap(x_pos, y_pos, bigWeatherIco4, size_w, size_h, GxEPD_BLACK); break;
    case 5: display.drawBitmap(x_pos, y_pos, bigWeatherIco5, size_w, size_h, GxEPD_BLACK); break;
    case 6: display.drawBitmap(x_pos, y_pos, bigWeatherIco6, size_w, size_h, GxEPD_BLACK); break;
    case 7: display.drawBitmap(x_pos, y_pos, bigWeatherIco7, size_w, size_h, GxEPD_BLACK); break;
    case 8: display.drawBitmap(x_pos, y_pos, bigWeatherIco8, size_w, size_h, GxEPD_BLACK); break;

    case 11: display.drawBitmap(x_pos, y_pos, bigWeatherIco11, size_w, size_h, GxEPD_BLACK); break;
    case 12: display.drawBitmap(x_pos, y_pos, bigWeatherIco12, size_w, size_h, GxEPD_BLACK); break;
    case 13: display.drawBitmap(x_pos, y_pos, bigWeatherIco13, size_w, size_h, GxEPD_BLACK); break;
    case 14: display.drawBitmap(x_pos, y_pos, bigWeatherIco14, size_w, size_h, GxEPD_BLACK); break;
    case 15: display.drawBitmap(x_pos, y_pos, bigWeatherIco15, size_w, size_h, GxEPD_BLACK); break;
    case 16: display.drawBitmap(x_pos, y_pos, bigWeatherIco16, size_w, size_h, GxEPD_BLACK); break;
    case 17: display.drawBitmap(x_pos, y_pos, bigWeatherIco17, size_w, size_h, GxEPD_BLACK); break;
    case 18: display.drawBitmap(x_pos, y_pos, bigWeatherIco18, size_w, size_h, GxEPD_BLACK); break;
    case 19: display.drawBitmap(x_pos, y_pos, bigWeatherIco19, size_w, size_h, GxEPD_BLACK); break;

    case 20: display.drawBitmap(x_pos, y_pos, bigWeatherIco20, size_w, size_h, GxEPD_BLACK); break;
    case 21: display.drawBitmap(x_pos, y_pos, bigWeatherIco21, size_w, size_h, GxEPD_BLACK); break;
    case 22: display.drawBitmap(x_pos, y_pos, bigWeatherIco22, size_w, size_h, GxEPD_BLACK); break;
    case 23: display.drawBitmap(x_pos, y_pos, bigWeatherIco23, size_w, size_h, GxEPD_BLACK); break;
    case 24: display.drawBitmap(x_pos, y_pos, bigWeatherIco24, size_w, size_h, GxEPD_BLACK); break;
    case 25: display.drawBitmap(x_pos, y_pos, bigWeatherIco25, size_w, size_h, GxEPD_BLACK); break;
    case 26: display.drawBitmap(x_pos, y_pos, bigWeatherIco26, size_w, size_h, GxEPD_BLACK); break;
    case 29: display.drawBitmap(x_pos, y_pos, bigWeatherIco29, size_w, size_h, GxEPD_BLACK); break;

    case 30: display.drawBitmap(x_pos, y_pos, bigWeatherIco30, size_w, size_h, GxEPD_BLACK); break;
    case 31: display.drawBitmap(x_pos, y_pos, bigWeatherIco31, size_w, size_h, GxEPD_BLACK); break;
    case 32: display.drawBitmap(x_pos, y_pos, bigWeatherIco32, size_w, size_h, GxEPD_BLACK); break;
    case 33: display.drawBitmap(x_pos, y_pos, bigWeatherIco33, size_w, size_h, GxEPD_BLACK); break;
    case 34: display.drawBitmap(x_pos, y_pos, bigWeatherIco34, size_w, size_h, GxEPD_BLACK); break;
    case 35: display.drawBitmap(x_pos, y_pos, bigWeatherIco35, size_w, size_h, GxEPD_BLACK); break;
    case 36: display.drawBitmap(x_pos, y_pos, bigWeatherIco36, size_w, size_h, GxEPD_BLACK); break;
    case 37: display.drawBitmap(x_pos, y_pos, bigWeatherIco37, size_w, size_h, GxEPD_BLACK); break;
    case 38: display.drawBitmap(x_pos, y_pos, bigWeatherIco38, size_w, size_h, GxEPD_BLACK); break;
    case 39: display.drawBitmap(x_pos, y_pos, bigWeatherIco39, size_w, size_h, GxEPD_BLACK); break;

    case 40: display.drawBitmap(x_pos, y_pos, bigWeatherIco40, size_w, size_h, GxEPD_BLACK); break;
    case 41: display.drawBitmap(x_pos, y_pos, bigWeatherIco41, size_w, size_h, GxEPD_BLACK); break;
    case 42: display.drawBitmap(x_pos, y_pos, bigWeatherIco42, size_w, size_h, GxEPD_BLACK); break;
    case 43: display.drawBitmap(x_pos, y_pos, bigWeatherIco43, size_w, size_h, GxEPD_BLACK); break;
    case 44: display.drawBitmap(x_pos, y_pos, bigWeatherIco44, size_w, size_h, GxEPD_BLACK); break;
  }
}

void show_info_icon(uint8_t w_number, int x_pos, int y_pos) {
  int size_w = 35;
  int size_h = 35;

  switch (w_number) {
    case 1: display.drawBitmap(x_pos, y_pos, infoIco1, size_w, size_h, GxEPD_BLACK); break;
    case 2: display.drawBitmap(x_pos, y_pos, infoIco2, size_w, size_h, GxEPD_BLACK); break;
    case 3: display.drawBitmap(x_pos, y_pos, infoIco3, size_w, size_h, GxEPD_BLACK); break;
    case 4: display.drawBitmap(x_pos, y_pos, infoIco4, size_w, size_h, GxEPD_BLACK); break;
    case 5: display.drawBitmap(x_pos, y_pos, infoIco5, size_w, size_h, GxEPD_BLACK); break;
  }
}

void display_battery(uint16_t pos_y) {
  display.setFont(&FreeSansBold9pt7b);
  display.setCursor(250, pos_y);

  uint16_t percent = pwr_mgmt.percent();

  if ((percent > 100) && (percent < 250)) percent = 100;

  int pos_x_ico = 220;

  if (percent > 100) {
    display.drawBitmap(pos_x_ico, 281, bat_empty, 24, 16, GxEPD_BLACK);
    display.print(str_bat_error);
    return;
  } else if ((percent > 85) && (percent < 101))
    display.drawBitmap(pos_x_ico, 281, bat_100, 24, 16, GxEPD_BLACK);
  else if ((percent > 60) && (percent < 86))
    display.drawBitmap(pos_x_ico, 281, bat_75, 24, 16, GxEPD_BLACK);
  else if ((percent > 40) && (percent < 61))
    display.drawBitmap(pos_x_ico, 281, bat_50, 24, 16, GxEPD_BLACK);
  else if ((percent > 10) && (percent < 41))
    display.drawBitmap(pos_x_ico, 281, bat_25, 24, 16, GxEPD_BLACK);
  else if (percent < 11)
    display.drawBitmap(pos_x_ico, 281, bat_empty, 24, 16, GxEPD_BLACK);

  display.print(percent);
  display.print("%");
}

void go_to_sleep(int seconds) {
  Serial.print(str_sleep);
  Serial.print(seconds);
  Serial.println(str_seconds);

  ESP.deepSleep(seconds * 1000000, WAKE_RF_DEFAULT);
  delay(2000);
}

void print_actual_weather() {
  Serial.println("actual weather:");
  Serial.println(dataC.location.Name);
  //Serial.println(dataC.LocalObservationDateTime);
  Serial.println(dataC.EpochTime);
  Serial.println(dataC.WeatherText);
  //Serial.println(dataC.WeatherIcon);
  //Serial.println(dataC.IsDayTime);
  Serial.println(dataC.Temperature);
  //Serial.println(dataC.RealFeelTemperature);
  //Serial.println(dataC.RealFeelTemperatureShade);
  //Serial.println(dataC.RelativeHumidity);
  Serial.println(dataC.WindDirection);
  Serial.println(dataC.WindSpeed);
  Serial.println(dataC.WindGustSpeed);
  //Serial.println(dataC.UVIndex);
  //Serial.println(dataC.UVIndexText);
  Serial.println(dataC.Visibility);
  Serial.println(dataC.CloudCover);
  Serial.println(dataC.Pressure);
  Serial.println(dataC.WindDirection);
}
void print_dataH() {
  for (int i = 0; i <= 3; i += 3) {
    Serial.print("Czas: ");
    //Serial.println(dataH[i].DateTime);
    //Serial.println(dataH[i]->EpochDateTime);
    //Serial.println(dataH[i]->WeatherIcon);
    Serial.print("Pogoda: ");
    //Serial.println(dataH[i].IconPhrase);
    //Serial.println(dataH[i]->IsDaylight);
    Serial.print("Temp: ");
    //Serial.println(dataH[i].Temperature);
    //Serial.println(dataH[i]->RealFeelTemperature);
    Serial.print("Wind speed: ");
    Serial.println(dataH[i].WindSpeed);
    //Serial.println(dataH[i]->WindDirection);
    //Serial.println(dataH[i]->WindGustSpeed);
    Serial.print("Hum: ");
    //Serial.println(dataH[i].RelativeHumidity);
    //Serial.println(dataH[i]->Visibility);
    Serial.print("UV index: ");
    //Serial.println(dataH[i].UVIndex);
    //Serial.println(dataH[i]->UVIndexText);
    //Serial.println(dataH[i]->PrecipitationProbability);
    Serial.print("Rain prob: ");
    //Serial.println(dataH[i].RainProbability);
    //Serial.println(dataH[i]->SnowProbability);
    //Serial.println(dataH[i]->IceProbability);
    //Serial.println(dataH[i]->TotalLiquid);
    //Serial.println(dataH[i]->Rain);
    //Serial.println(dataH[i]->Snow);
    //Serial.println(dataH[i]->Ice);
    //Serial.println(dataH[i]->CloudCover);
    Serial.println("  ");
    Serial.println("  ");
  }
}
#ifdef USE_AIRLY
int checkNearestSensor() {
  if (airlyApi.getNearestSensor()) {
    int locationId = airlyApi.getLocationId();
#ifdef USE_SERIAL_PORT
    Serial.println("LocationId: " + String(locationId));
#endif
    if (airlyApi.getSensorValues(locationId)) {
#ifdef USE_SERIAL_PORT
      Serial.print("AirQualityInde: ");
      Serial.println(airlyApi.getAirQualityIndex());
      Serial.print("AirQualityLevel: ");
      Serial.println(airlyApi.getAirQualityLevel());
#endif
      return 0;
    } else {
#ifdef USE_SERIAL_PORT
      Serial.println("getSensorValues error");
#endif
    }
  }
  return 1;
}
#endif

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Setup");
  delay(100);

#ifdef USE_EPD
  display.init(115200);
#endif

#ifdef USE_WIFI
  wifi_connection_status = wifi_connect();
#endif

#ifdef USE_MAX17048
  Wire.begin(D1, D6);  //sda,scl
  pwr_mgmt.attatch(Wire);

  Serial.print("VCELL V   : ");
  Serial.println(pwr_mgmt.voltage());
  Serial.print("VCELL SOC : ");
  Serial.print(pwr_mgmt.percent());
  Serial.println(" \%");
#endif

  if (wifi_connection_status == 0) {
    do {
      weather_status = get_weather();
      Serial.print("Accu status:");
      Serial.println(weather_status);

      if (weather_status == 0) break;
    } while (weather_status != 0);

#ifdef USE_AIRLY
    airly_status = checkNearestSensor();
#endif

#ifdef USE_EPD
    Serial.println("display_weather");
#ifdef USE_AIRLY
    display_weather(wifi_connection_status, weather_status, airly_status);
#else
    display_weather(wifi_connection_status, weather_status);
#endif
#endif
  }

  if (wifi_connection_status == 0)
    go_to_sleep(UPDATE_PERIOD);
  else
    go_to_sleep(WIFI_ERR_PERIOD);
}
void loop() {
}
