#include "weatherapi.h"
#include "JsonListener.h"

#define SIZE_OF_CONST_TABLE(x) sizeof(x) / sizeof(x[0])
#define STACK_HAS_SUFFIX(x) stackSuffix(x, SIZE_OF_CONST_TABLE(x))

/*
 * Parser constants
 */
// A map to transform strings into tokens
static const std::map<const String, const ParserToken> stringToTokenMap = {
  { "location", PARSERlocation },
  { "current", PARSERcurrent },
  { "forecast", PARSERforecast },
  { "forecastday", PARSERforecastday },
  { "day", PARSERday },
  { "hour", PARSERhour },
  { "condition", PARSERcondition },
  { "name", PARSERname },
  { "localtime", PARSERlocaltime },
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
  { "totalprecip_mm", PARSERtotalprecip_mm },
  { "avgvis_km", PARSERavgvis_km },
  { "avghumidity", PARSERavghumidity },
  { "daily_chance_of_rain", PARSERdaily_chance_of_rain },
  { "time", PARSERtime },
  { "time_epoch", PARSERtime_epoch },
  { "chance_of_rain", PARSERchance_of_rain },
};

// Arrays of stack suffixes for the CURRENT weather section
static const ParserToken location_name_suffix[] = { PARSERlocation, PARSERObject, PARSERname };
static const ParserToken location_localtime_suffix[] = { PARSERlocation, PARSERObject, PARSERlocaltime };
static const ParserToken current_last_updated_epoch_suffix[] = { PARSERcurrent, PARSERObject, PARSERlast_updated_epoch };
static const ParserToken current_temp_c_suffix[] = { PARSERcurrent, PARSERObject, PARSERtemp_c };
static const ParserToken current_condition_text_suffix[] = { PARSERcurrent, PARSERObject, PARSERcondition, PARSERObject, PARSERtext };
static const ParserToken current_condition_code_suffix[] = { PARSERcurrent, PARSERObject, PARSERcondition, PARSERObject, PARSERcode };
static const ParserToken current_wind_kph_suffix[] = { PARSERcurrent, PARSERObject, PARSERwind_kph };
static const ParserToken current_wind_degree_suffix[] = { PARSERcurrent, PARSERObject, PARSERwind_degree };
static const ParserToken current_pressure_mb_suffix[] = { PARSERcurrent, PARSERObject, PARSERpressure_mb };
static const ParserToken current_humidity_suffix[] = { PARSERcurrent, PARSERObject, PARSERhumidity };
static const ParserToken current_cloud_suffix[] = { PARSERcurrent, PARSERObject, PARSERcloud };
static const ParserToken current_feelslike_c_suffix[] = { PARSERcurrent, PARSERObject, PARSERfeelslike_c };
static const ParserToken current_vis_km_suffix[] = { PARSERcurrent, PARSERObject, PARSERvis_km };
static const ParserToken current_uv_suffix[] = { PARSERcurrent, PARSERObject, PARSERuv };
static const ParserToken current_gust_kph_suffix[] = { PARSERcurrent, PARSERObject, PARSERgust_kph };

// Suffixes for DAILY forecast section
static const ParserToken daily_date_suffix[] = { PARSERdate };
static const ParserToken daily_date_epoch_suffix[] = { PARSERdate_epoch };
static const ParserToken daily_maxtemp_c_suffix[] = { PARSERday, PARSERObject, PARSERmaxtemp_c };
static const ParserToken daily_mintemp_c_suffix[] = { PARSERday, PARSERObject, PARSERmintemp_c };
static const ParserToken daily_maxwind_kph_suffix[] = { PARSERday, PARSERObject, PARSERmaxwind_kph };
static const ParserToken daily_totalprecip_mm_suffix[] = { PARSERday, PARSERObject, PARSERtotalprecip_mm };
static const ParserToken daily_avgvis_km_suffix[] = { PARSERday, PARSERObject, PARSERavgvis_km };
static const ParserToken daily_avghumidity_suffix[] = { PARSERday, PARSERObject, PARSERavghumidity };
static const ParserToken daily_chance_of_rain_suffix[] = { PARSERday, PARSERObject, PARSERdaily_chance_of_rain };
static const ParserToken daily_condition_text_suffix[] = { PARSERday, PARSERObject, PARSERcondition, PARSERObject, PARSERtext };
static const ParserToken daily_condition_code_suffix[] = { PARSERday, PARSERObject, PARSERcondition, PARSERObject, PARSERcode };

// Suffixes for HOURLY forecast section
static const ParserToken hourly_time_epoch_suffix[] = { PARSERtime_epoch };
static const ParserToken hourly_time_suffix[] = { PARSERtime };
static const ParserToken hourly_temp_c_suffix[] = { PARSERtemp_c };
static const ParserToken hourly_condition_text_suffix[] = { PARSERcondition, PARSERObject, PARSERtext };
static const ParserToken hourly_condition_code_suffix[] = { PARSERcondition, PARSERObject, PARSERcode };
static const ParserToken hourly_wind_kph_suffix[] = { PARSERwind_kph };
static const ParserToken hourly_wind_degree_suffix[] = { PARSERwind_degree };
static const ParserToken hourly_pressure_mb_suffix[] = { PARSERpressure_mb };
static const ParserToken hourly_precip_mm_suffix[] = { PARSERprecip_mm };
static const ParserToken hourly_humidity_suffix[] = { PARSERhumidity };
static const ParserToken hourly_cloud_suffix[] = { PARSERcloud };
static const ParserToken hourly_feelslike_c_suffix[] = { PARSERfeelslike_c };
static const ParserToken hourly_vis_km_suffix[] = { PARSERvis_km };
static const ParserToken hourly_gust_kph_suffix[] = { PARSERgust_kph };
static const ParserToken hourly_uv_suffix[] = { PARSERuv };
static const ParserToken hourly_chance_of_rain_suffix[] = { PARSERchance_of_rain };

// Suffixes for identifying lists
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
  // This base function does nothing, it's overridden by child classes
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
  //ignore
}

//Housekeeping functions
void WeatherApiParser::DEBUG_printStack() {
  for (auto it = tokenStack.begin(); it != tokenStack.end(); ++it) {
    Serial.print(">");
    Serial.print(*it);
  }
  Serial.println("*");
}

bool WeatherApiParser::stackSuffix(const ParserToken suffix[], int suffix_len) {
  int stackSize = tokenStack.size();
  if (stackSize < suffix_len) {
    return false;
  }
  if (suffix_len == 0) {
    return true;
  }
  // Compare the end of the stack with the suffix
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
 * Parsers for specific endpoints
 */
CurrentParser::CurrentParser(WeatherApiCurrentData* data_ptr_)
  : WeatherApiParser(1) {
  data_ptr = data_ptr_;
}

void CurrentParser::value(String value) {
  // Only parse location and current sections
  if (!stackContains(PARSERlocation) && !stackContains(PARSERcurrent)) {
    popAllKeys();
    return;
  }

  if (STACK_HAS_SUFFIX(location_name_suffix)) {
    data_ptr->location.Name = value;
  } else if (STACK_HAS_SUFFIX(location_localtime_suffix)) {
    data_ptr->LocalTime = value;
  } else if (STACK_HAS_SUFFIX(current_last_updated_epoch_suffix)) {
    data_ptr->EpochTime = value.toInt();
  } else if (STACK_HAS_SUFFIX(current_temp_c_suffix)) {
    data_ptr->Temperature = value.toFloat();
  } else if (STACK_HAS_SUFFIX(current_condition_text_suffix)) {
    data_ptr->WeatherText = value;
  } else if (STACK_HAS_SUFFIX(current_condition_code_suffix)) {
    data_ptr->WeatherCode = value.toInt();
  } else if (STACK_HAS_SUFFIX(current_wind_kph_suffix)) {
    data_ptr->WindSpeed = value.toFloat();
  } else if (STACK_HAS_SUFFIX(current_wind_degree_suffix)) {
    data_ptr->WindDirection = value.toInt();
  } else if (STACK_HAS_SUFFIX(current_pressure_mb_suffix)) {
    data_ptr->Pressure = value.toFloat();
  } else if (STACK_HAS_SUFFIX(current_humidity_suffix)) {
    data_ptr->Humidity = value.toFloat();
  } else if (STACK_HAS_SUFFIX(current_cloud_suffix)) {
    data_ptr->CloudCover = value.toFloat();
  } else if (STACK_HAS_SUFFIX(current_feelslike_c_suffix)) {
    data_ptr->FeelsLike = value.toFloat();
  } else if (STACK_HAS_SUFFIX(current_vis_km_suffix)) {
    data_ptr->Visibility = value.toFloat();
  } else if (STACK_HAS_SUFFIX(current_uv_suffix)) {
    data_ptr->UvIndex = value.toFloat();
  } else if (STACK_HAS_SUFFIX(current_gust_kph_suffix)) {
    data_ptr->WindGustSpeed = value.toFloat();
  }

  popAllKeys();
}

HourlyParser::HourlyParser(WeatherApiHourlyData* data_ptr_, int maxListLength_)
  : WeatherApiParser(maxListLength_) {
  data_ptr = data_ptr_;
}

void HourlyParser::startObject() {
  tokenStack.push_back(PARSERObject);
  // Increment index when entering a new object in the 'hour' list
  if (STACK_HAS_SUFFIX(hourList_suffix)) {
    baseListIdx++;
  }
}

void HourlyParser::value(String value) {
  if (baseListIdx >= maxListLength) {
    return;
  }
  // We only care about values inside the 'hour' list
  if (!stackContains(PARSERhour)) {
    popAllKeys();
    return;
  }

  if (STACK_HAS_SUFFIX(hourly_time_epoch_suffix)) {
    data_ptr[baseListIdx].TimeEpoch = value.toInt();
  } else if (STACK_HAS_SUFFIX(hourly_time_suffix)) {
    data_ptr[baseListIdx].Time = value;
  } else if (STACK_HAS_SUFFIX(hourly_temp_c_suffix)) {
    data_ptr[baseListIdx].Temp = value.toFloat();
  } else if (STACK_HAS_SUFFIX(hourly_condition_text_suffix)) {
    data_ptr[baseListIdx].WeatherText = value;
  } else if (STACK_HAS_SUFFIX(hourly_condition_code_suffix)) {
    data_ptr[baseListIdx].WeatherCode = value.toInt();
  } else if (STACK_HAS_SUFFIX(hourly_wind_kph_suffix)) {
    data_ptr[baseListIdx].WindSpeed = value.toFloat();
  } else if (STACK_HAS_SUFFIX(hourly_wind_degree_suffix)) {
    data_ptr[baseListIdx].WindDir = value.toFloat();
  } else if (STACK_HAS_SUFFIX(hourly_pressure_mb_suffix)) {
    data_ptr[baseListIdx].Pressure = value.toFloat();
  } else if (STACK_HAS_SUFFIX(hourly_precip_mm_suffix)) {
    data_ptr[baseListIdx].Precip = value.toFloat();
  } else if (STACK_HAS_SUFFIX(hourly_humidity_suffix)) {
    data_ptr[baseListIdx].Humidity = value.toFloat();
  } else if (STACK_HAS_SUFFIX(hourly_cloud_suffix)) {
    data_ptr[baseListIdx].Cloud = value.toInt();
  } else if (STACK_HAS_SUFFIX(hourly_feelslike_c_suffix)) {
    data_ptr[baseListIdx].FeelsLike = value.toFloat();
  } else if (STACK_HAS_SUFFIX(hourly_vis_km_suffix)) {
    data_ptr[baseListIdx].Visibility = value.toFloat();
  } else if (STACK_HAS_SUFFIX(hourly_gust_kph_suffix)) {
    data_ptr[baseListIdx].Gust = value.toFloat();
  } else if (STACK_HAS_SUFFIX(hourly_uv_suffix)) {
    data_ptr[baseListIdx].UvIndex = value.toFloat();
  } else if (STACK_HAS_SUFFIX(hourly_chance_of_rain_suffix)) {
    data_ptr[baseListIdx].ChanceOfRain = value.toInt();
  }

  popAllKeys();
}


DailyParser::DailyParser(WeatherApiDailyData* data_ptr_, int maxListLength_)
  : WeatherApiParser(maxListLength_) {
  data_ptr = data_ptr_;
}

void DailyParser::startObject() {
  tokenStack.push_back(PARSERObject);
  // Increment index when entering a new object in the 'forecastday' list
  if (STACK_HAS_SUFFIX(forecastdayList_suffix)) {
    baseListIdx++;
  }
}

void DailyParser::value(String value) {
  if (baseListIdx >= maxListLength) {
    return;
  }
  // We only care about values inside the 'forecastday' list
  if (!stackContains(PARSERforecastday)) {
    popAllKeys();
    return;
  }

  if (STACK_HAS_SUFFIX(daily_date_suffix)) {
    data_ptr[baseListIdx].Date = value;
  } else if (STACK_HAS_SUFFIX(daily_date_epoch_suffix)) {
    data_ptr[baseListIdx].DateEpoch = value.toInt();
  } else if (STACK_HAS_SUFFIX(daily_maxtemp_c_suffix)) {
    data_ptr[baseListIdx].Day.MaxTemp = value.toFloat();
  } else if (STACK_HAS_SUFFIX(daily_mintemp_c_suffix)) {
    data_ptr[baseListIdx].Day.MinTemp = value.toFloat();
  } else if (STACK_HAS_SUFFIX(daily_maxwind_kph_suffix)) {
    data_ptr[baseListIdx].Day.MaxWindKph = value.toFloat();
  } else if (STACK_HAS_SUFFIX(daily_totalprecip_mm_suffix)) {
    data_ptr[baseListIdx].Day.TotalPrecipMm = value.toFloat();
  } else if (STACK_HAS_SUFFIX(daily_avgvis_km_suffix)) {
    data_ptr[baseListIdx].Day.AvgVisKm = value.toFloat();
  } else if (STACK_HAS_SUFFIX(daily_avghumidity_suffix)) {
    data_ptr[baseListIdx].Day.AvgHumidity = value.toFloat();
  } else if (STACK_HAS_SUFFIX(daily_chance_of_rain_suffix)) {
    data_ptr[baseListIdx].Day.ChanceOfRain = value.toInt();
  } else if (STACK_HAS_SUFFIX(daily_condition_text_suffix)) {
    data_ptr[baseListIdx].Day.WeatherText = value;
  } else if (STACK_HAS_SUFFIX(daily_condition_code_suffix)) {
    data_ptr[baseListIdx].Day.WeatherCode = value.toInt();
  }

  popAllKeys();
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
      // Use the new parser for current weather
      listener = new CurrentParser(data_ptr);
      parser.setListener(listener);
      return 0;
    }
  }
  // If we got here, we failed to get data
  http.end();
  return httpCode;
}

void WeatherApi::freeConnection() {
  http.end();
  delete listener;
  listener = NULL;
}

/*
 * continueDownload() function downloads data in 128 byte chunks.
 * Returns <0 on download error, 0 on download finished, >0 if the download can be continued.
 */
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
      return c;  // Return bytes read
    }
    return 1;  // No data available right now, but connection is open
  } else if (length == 0) {
    freeConnection();
    return 0;  // Finished
  } else {
    freeConnection();  // Free resources on error
    return -1;         // Error
  }
}