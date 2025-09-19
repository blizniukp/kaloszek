#include "weatherapi.h"
#include "JsonListener.h"

#define SIZE_OF_CONST_TABLE(x) sizeof(x) / sizeof(x[0])
#define STACK_HAS_SUFFIX(x) stackSuffix(x, SIZE_OF_CONST_TABLE(x))

/*
 * Parser constants
 */
// Restored the full map of strings to tokens
static const std::map<const String, const ParserToken> stringToTokenMap = {
  { "current", PARSERcurrent },
  { "forecast", PARSERforecast },
  { "forecastday", PARSERforecastday },
  { "day", PARSERday },
  { "hour", PARSERhour },
  { "condition", PARSERcondition },
  { "last_updated_epoch", PARSERlast_updated_epoch },
  { "temp_c", PARSERtemp_c },
  { "feelslike_c", PARSERfeelslike_c },
  { "pressure_mb", PARSERpressure_mb },
  { "precip_mm", PARSERprecip_mm },
  { "humidity", PARSERhumidity },
  { "cloud", PARSERcloud },
  { "wind_kph", PARSERwind_kph },
  { "wind_degree", PARSERwind_degree },
  { "gust_kph", PARSERgust_kph },
  { "vis_km", PARSERvis_km },
  { "uv", PARSERuv },
  { "text", PARSERtext },
  { "code", PARSERcode },
  { "date", PARSERdate },
  { "date_epoch", PARSERdate_epoch },
  { "maxtemp_c", PARSERmaxtemp_c },
  { "mintemp_c", PARSERmintemp_c },
  { "maxwind_kph", PARSERmaxwind_kph },
  { "avgtemp_c", PARSERavgtemp_c },  // <-- Added mapping
  { "totalprecip_mm", PARSERtotalprecip_mm },
  { "avgvis_km", PARSERavgvis_km },
  { "avghumidity", PARSERavghumidity },
  { "daily_chance_of_rain", PARSERdaily_chance_of_rain },
  { "time", PARSERtime },
  { "time_epoch", PARSERtime_epoch },
  { "chance_of_rain", PARSERchance_of_rain },
};

static const ParserToken current_last_updated_epoch_suffix[] = { PARSERcurrent, PARSERObject, PARSERlast_updated_epoch };
static const ParserToken current_temp_c_suffix[] = { PARSERcurrent, PARSERObject, PARSERtemp_c };
static const ParserToken current_wind_kph_suffix[] = { PARSERcurrent, PARSERObject, PARSERwind_kph };
static const ParserToken current_wind_degree_suffix[] = { PARSERcurrent, PARSERObject, PARSERwind_degree };
static const ParserToken current_pressure_mb_suffix[] = { PARSERcurrent, PARSERObject, PARSERpressure_mb };
static const ParserToken current_humidity_suffix[] = { PARSERcurrent, PARSERObject, PARSERhumidity };
static const ParserToken current_feelslike_c_suffix[] = { PARSERcurrent, PARSERObject, PARSERfeelslike_c };
static const ParserToken current_condition_code_suffix[] = { PARSERcurrent, PARSERObject, PARSERcondition, PARSERObject, PARSERcode };

static const ParserToken forecast_date_epoch_suffix[] = { PARSERforecast, PARSERObject, PARSERforecastday, PARSERList, PARSERObject, PARSERdate_epoch };
static const ParserToken forecast_day_avgtemp_c_suffix[] = { PARSERforecast, PARSERObject, PARSERforecastday, PARSERList, PARSERObject, PARSERday, PARSERObject, PARSERavgtemp_c };
static const ParserToken forecast_day_maxwind_kph_suffix[] = { PARSERforecast, PARSERObject, PARSERforecastday, PARSERList, PARSERObject, PARSERday, PARSERObject, PARSERmaxwind_kph };

static const ParserToken forecastdayList_suffix[] = { PARSERBase, PARSERObject, PARSERforecast, PARSERObject, PARSERforecastday, PARSERList, PARSERObject };
static const ParserToken hourList_suffix[] = { PARSERforecastday, PARSERList, PARSERObject, PARSERhour, PARSERList, PARSERObject };

/*
 * Parser base class
 */
WeatherApiParser::WeatherApiParser(int maxListLength_) {
  maxListLength = maxListLength_;
}

void WeatherApiParser::startDocument() {
  tokenStack.push_back(PARSERBase);
}

void WeatherApiParser::endDocument() {
  if (tokenStack.back() != PARSERBase) {
    Serial.println(F("ERROR: Document token not found"));
  }
  popAllKeys();
}

void WeatherApiParser::key(String key) {
  if (baseListIdx >= maxListLength) {
    return;
  }
  auto it = stringToTokenMap.find(key);
  if (it != stringToTokenMap.end()) {
    tokenStack.push_back(it->second);
  } else {
    tokenStack.push_back(PARSERUnknown);
  }
}

void WeatherApiParser::value(String value) {
  if (baseListIdx >= maxListLength) {
    return;
  }
  popAllKeys();
}

void WeatherApiParser::startArray() {
  tokenStack.push_back(PARSERList);
}

void WeatherApiParser::endArray() {
  if (tokenStack.back() != PARSERList) {
    Serial.println(F("ERROR: List token not found"));
  }
  tokenStack.pop_back();

  popAllKeys();
}

void WeatherApiParser::startObject() {
  tokenStack.push_back(PARSERObject);
}

void WeatherApiParser::endObject() {
  if (tokenStack.back() != PARSERObject) {
    Serial.println(F("ERROR: Object token not found"));
  }
  tokenStack.pop_back();

  popAllKeys();
}

void WeatherApiParser::whitespace(char c) {
}

bool WeatherApiParser::stackSuffix(const ParserToken suffix[], int suffix_len) {
  if (tokenStack.size() < suffix_len) {
    return false;
  }
  return std::equal(tokenStack.end() - suffix_len, tokenStack.end(), suffix);
}

bool WeatherApiParser::stackContains(const ParserToken token) {
  for (auto it = tokenStack.rbegin(); it != tokenStack.rend(); it++)
    if (*it == token)
      return true;
  return false;
}

void WeatherApiParser::popAllKeys() {
  while (!(tokenStack.back() == PARSERObject || tokenStack.back() == PARSERList || tokenStack.back() == PARSERBase)) {
    tokenStack.pop_back();
  }
}

/*
 * CurrentParser - Corrected and fully implemented
 */
CurrentParser::CurrentParser(WeatherApiCurrentData* data_ptr_)
  : WeatherApiParser(1) {
  data_ptr = data_ptr_;
}

void CurrentParser::value(String value) {
  // Only parse values from 'current' or 'forecast' objects
  if (!stackContains(PARSERcurrent) && !stackContains(PARSERforecast)) {
    popAllKeys();
    return;
  }

  // --- Current Weather Data ---
  if (STACK_HAS_SUFFIX(current_last_updated_epoch_suffix)) {
    data_ptr->Current.LastUpdatedEpoch = value.toInt();
  } else if (STACK_HAS_SUFFIX(current_temp_c_suffix)) {
    data_ptr->Current.TempC = value.toFloat();
  } else if (STACK_HAS_SUFFIX(current_condition_code_suffix)) {
    data_ptr->Current.Condition.Code = value.toInt();
  } else if (STACK_HAS_SUFFIX(current_wind_kph_suffix)) {
    data_ptr->Current.WindKph = value.toFloat();
  } else if (STACK_HAS_SUFFIX(current_wind_degree_suffix)) {
    data_ptr->Current.WindDegree = value.toInt();
  } else if (STACK_HAS_SUFFIX(current_pressure_mb_suffix)) {
    data_ptr->Current.PressureMb = value.toFloat();
  } else if (STACK_HAS_SUFFIX(current_humidity_suffix)) {
    data_ptr->Current.Humidity = value.toInt();
  } else if (STACK_HAS_SUFFIX(current_feelslike_c_suffix)) {
    data_ptr->Current.FeelsLikeC = value.toFloat();
  }
  // --- Forecast Data (first day) ---
  else if (STACK_HAS_SUFFIX(forecast_date_epoch_suffix)) {
    data_ptr->Forecast.Forecastday.DateEpoch = value.toInt();
  } else if (STACK_HAS_SUFFIX(forecast_day_avgtemp_c_suffix)) {
    data_ptr->Forecast.Forecastday.day.AvgTempC = value.toFloat();
  } else if (STACK_HAS_SUFFIX(forecast_day_maxwind_kph_suffix)) {
    data_ptr->Forecast.Forecastday.day.MaxWindKph = value.toFloat();
  }

  popAllKeys();
}

/*
 * Other parsers (unchanged, for potential future use)
 */
HourlyParser::HourlyParser(WeatherApiHourlyData* data_ptr_, int maxListLength_)
  : WeatherApiParser(maxListLength_) {
  data_ptr = data_ptr_;
}

void HourlyParser::startObject() {
  tokenStack.push_back(PARSERObject);
  if (STACK_HAS_SUFFIX(hourList_suffix)) {
    baseListIdx++;
  }
}

void HourlyParser::value(String value) {
  // Not implemented, requires a dedicated getHourlyForecast function
}

DailyParser::DailyParser(WeatherApiDailyData* data_ptr_, int maxListLength_)
  : WeatherApiParser(maxListLength_) {
  data_ptr = data_ptr_;
}

void DailyParser::startObject() {
  tokenStack.push_back(PARSERObject);
  if (STACK_HAS_SUFFIX(forecastdayList_suffix)) {
    baseListIdx++;
  }
}

void DailyParser::value(String value) {
  // Not implemented, requires a dedicated getDailyForecast function
}

/*
 * Data retrieval over HTTP
 */
static const char forecastURLTemplate[] PROGMEM = "http://api.weatherapi.com/v1/forecast.json?key=%s&q=id:%d&days=1&aqi=no&alerts=no";

int WeatherApi::getForecast(WeatherApiCurrentData* data_ptr) {
  char url[256];
  snprintf_P(url, 256, forecastURLTemplate, apiKey, locationID);

  http.begin(client, url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      length = http.getSize();
      parser.reset();
      listener = new CurrentParser(data_ptr);
      parser.setListener(listener);
      return 0;
    }
  }
  http.end();
  return httpCode;
}

void WeatherApi::freeConnection() {
  http.end();
  delete listener;
  listener = NULL;
}

int WeatherApi::continueDownload() {
  if (http.connected() && (length > 0 || length == -1)) {
    uint8_t buff[128] = { 0 };
    WiFiClient* stream = http.getStreamPtr();
    size_t size = stream->available();

    if (size) {
      int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
      for (int i = 0; i < c; i++) {
        parser.parse(buff[i]);
      }
      if (length > 0) {
        length -= c;
      }
      return c;
    }
    return 1;
  } else if (length == 0) {
    freeConnection();
    return 0;
  } else {
    freeConnection();
    return -1;
  }
}