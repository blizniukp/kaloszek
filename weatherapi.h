#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "JsonStreamingParser.h"
#include "JsonListener.h"
#include <limits.h>
#include <vector>
#include <map>

// Structures for holding the received data (as defined by you)
typedef struct {
  int16_t Code;
} WeatherApiResponseCurrentCondition;

typedef struct {
  uint32_t LastUpdatedEpoch;
  float TempC;
  float WindKph;
  int16_t WindDegree;
  float PressureMb;
  int8_t Humidity;
  float FeelsLikeC;
  WeatherApiResponseCurrentCondition Condition;
} WeatherApiResponseCurrent;

typedef struct {
  float AvgTempC;
  float MaxWindKph;
} WeatherApiResponseForecastdayDay;

typedef struct {
  uint32_t DateEpoch;
  WeatherApiResponseForecastdayDay day;
} WeatherApiResponseForecastday;

typedef struct {
  // Note: The API returns an array for 'forecastday', we will parse the first element.
  WeatherApiResponseForecastday Forecastday;
} WeatherApiResponseForecast;

typedef struct {
  WeatherApiResponseCurrent Current;
  WeatherApiResponseForecast Forecast;
} WeatherApiCurrentData;

// Unused in getForecast, but kept for potential future use
typedef struct {
  String Time;
  String WeatherText;
  float FeelsLike;
  float Gust;
  float Humidity;
  float Precip;
  float Pressure;
  float Temp;
  float UvIndex;
  float Visibility;
  float WindDir;
  float WindSpeed;
  int TimeEpoch;
  uint16_t WeatherCode;
  uint8_t ChanceOfRain;
  uint8_t Cloud;
} WeatherApiHourlyData;

typedef struct {
  String WeatherText;
  float AvgHumidity;
  float AvgVisKm;
  float MaxTemp;
  float MaxWindKph;
  float MinTemp;
  float TotalPrecipMm;
  uint16_t WeatherCode;
  uint8_t ChanceOfRain;
} ForecastDayData;

typedef struct {
  String Date;
  int DateEpoch;
  ForecastDayData Day;
} WeatherApiDailyData;

// Tokens for different keys that can be found in the JSON responses
enum ParserTokens_ {
  PARSERUnknown,
  PARSERBase,
  PARSERList,
  PARSERObject,
  PARSERlocation,
  PARSERcurrent,
  PARSERforecast,
  PARSERforecastday,
  PARSERday,
  PARSERhour,
  PARSERcondition,
  PARSERname,
  PARSERlocaltime,
  PARSERlast_updated_epoch,
  PARSERtemp_c,
  PARSERfeelslike_c,
  PARSERpressure_mb,
  PARSERprecip_mm,
  PARSERhumidity,
  PARSERcloud,
  PARSERwind_kph,
  PARSERwind_degree,
  PARSERgust_kph,
  PARSERvis_km,
  PARSERuv,
  PARSERtext,
  PARSERcode,
  PARSERdate,
  PARSERdate_epoch,
  PARSERmaxtemp_c,
  PARSERmintemp_c,
  PARSERmaxwind_kph,
  PARSERtotalprecip_mm,
  PARSERavgvis_km,
  PARSERavghumidity,
  PARSERdaily_chance_of_rain,
  PARSERtime,
  PARSERtime_epoch,
  PARSERchance_of_rain,
  PARSERavgtemp_c,  // <-- Added missing token
};

typedef uint8_t ParserToken;

class WeatherApiParser : public JsonListener {
public:
  WeatherApiParser(int maxListLength_);
  virtual void whitespace(char c);
  virtual void key(String key);
  virtual void value(String value);
  virtual void startDocument();
  virtual void endDocument();
  virtual void startArray();
  virtual void endArray();
  virtual void startObject();
  virtual void endObject();

protected:
  std::vector<ParserToken> tokenStack;
  void DEBUG_printStack();
  bool stackSuffix(const ParserToken suffix[], int suffix_len);
  bool stackContains(const ParserToken token);
  void popAllKeys();
  int baseListIdx = -1;
  int maxListLength = INT_MAX;
  bool listFull = false;
};

class CurrentParser : public WeatherApiParser {
public:
  CurrentParser(WeatherApiCurrentData* data_ptr_);
  virtual void value(String value);
protected:
  WeatherApiCurrentData* data_ptr;
};

class HourlyParser : public WeatherApiParser {
public:
  HourlyParser(WeatherApiHourlyData* data_ptr_, int maxListLength_);
  virtual void startObject();
  virtual void value(String value);
protected:
  WeatherApiHourlyData* data_ptr;
};

class DailyParser : public WeatherApiParser {
public:
  DailyParser(WeatherApiDailyData* data_ptr_, int maxListLength_);
  virtual void startObject();
  virtual void value(String value);
protected:
  WeatherApiDailyData* data_ptr;
};

class WeatherApi {
public:
  WiFiClient client;
  HTTPClient http;
  JsonStreamingParser parser;
  WeatherApiParser* listener = NULL;
  const int locationID;
  const char* apiKey;
  int length;

  WeatherApi(const char* apiKey_, const int locationID_)
    : locationID(locationID_),
      apiKey(apiKey_) {
  }

  int getForecast(WeatherApiCurrentData* data_ptr);
  int continueDownload();
  void freeConnection();
};