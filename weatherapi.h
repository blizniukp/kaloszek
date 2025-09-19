#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "JsonStreamingParser.h"
#include "JsonListener.h"
#include <limits.h>
#include <vector>
#include <map>

// Structures for holding the received data
typedef struct {
  String Name;
} WeatherApiResponseLocation;

typedef struct {
  WeatherApiResponseLocation location;
  String LocalTime;
  String WeatherText;
  float CloudCover;
  float Pressure;
  float FeelsLike;
  float Humidity;
  float Temperature;
  float Visibility;
  float UvIndex;
  float WindGustSpeed;
  float WindSpeed;
  int EpochTime;
  int16_t WindDirection;
  uint16_t WeatherCode;
} WeatherApiCurrentData;

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
  // New tokens for WeatherAPI.com
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
};

// I do this to save memory - by default enums are ints, so to save a bit of memory I use chars instead.
// WARNING: change this if you will need more than 256 tokens
typedef uint8_t ParserToken;

// The parser creates a stack while parsing the JSON response.
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

// Descendant classes for parsing particular types of responses
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

// Main class for sending requests and parsing responses
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

  // This function is now adapted to get current weather
  int getForecast(WeatherApiCurrentData* data_ptr);
  // You would create similar functions for daily/hourly forecasts
  // e.g. int getDailyForecast(WeatherApiDailyData* data_ptr, int days);

  int continueDownload();
  void freeConnection();
};