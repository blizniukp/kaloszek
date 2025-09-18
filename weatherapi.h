#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "JsonStreamingParser.h"
#include "JsonListener.h"
#include <limits.h>
#include <vector>
#include <map>

typedef struct{
    String Name;
}WeatherApiResponseLocation;

//Structures for holding the received data
typedef struct {
    WeatherApiResponseLocation location;
    String LocalObservationDateTime;
    String UVIndexText;
    String WeatherText;
    float CloudCover;
    float Pressure;
    float RealFeelTemperature;
    float RealFeelTemperatureShade;
    float RelativeHumidity;
    float Temperature;
    float Visibility;
    float WindGustSpeed;
    float WindSpeed;
    int EpochTime;
    int16_t WindDirection;
    uint8_t IsDayTime;
    uint8_t UVIndex;
    uint8_t WeatherIcon;
}
WeatherApiCurrentData;

typedef struct {
    String DateTime;
    String IconPhrase;
    String UVIndexText;
    float Ice;
    float Rain;
    float RealFeelTemperature;
    float RelativeHumidity;
    float Snow;
    float Temperature;
    float TotalLiquid;
    float Visibility;
    float WindGustSpeed;
    float WindSpeed;
    int EpochDateTime;
    int16_t WindDirection;
    uint8_t CloudCover;
    uint8_t IceProbability;
    uint8_t IsDaylight;
    uint8_t PrecipitationProbability;
    uint8_t RainProbability;
    uint8_t SnowProbability;
    uint8_t UVIndex;
    uint8_t WeatherIcon;
}
WeatherApiHourlyData;

typedef struct {
    String IconPhrase;
    String LongPhrase;
    float Ice;
    float Rain;
    float RelativeHumidity;
    float Snow;
    float TotalLiquid;
    float Visibility;
    float WindGustSpeed;
    float WindSpeed;
    int16_t WindDirection;
    uint8_t CloudCover;
    uint8_t IceProbability;
    uint8_t PrecipitationProbability;
    uint8_t RainProbability;
    uint8_t SnowProbability;
    uint8_t ThunderstormProbability;
    uint8_t WeatherIcon;
}
AccuweatherForecastData;

typedef struct {
    String Date;
    float TempMin;
    float TempMax;
    float RealFeelTempMin;
    float RealFeelTempMax;
    float HoursOfSun;
    int EpochDate;
    int SunRise;
    int SunSet;
    AccuweatherForecastData Day;
    AccuweatherForecastData Night;
}
AccuweatherDailyData;

//Tokens for different keys that can be found in the JSON responses
//To extend the functionality, first a new token should be added to the enum below,
//then a mapping from String to that token in the map.
enum AccuParserTokens_ {
    ACCUPARSERUnknown,
    ACCUPARSERBase,
    ACCUPARSERList,
    ACCUPARSERObject,
    ACCUPARSERUnitPlaceholder,
    ACCUPARSERCloudCover,
    ACCUPARSERDateTime,
    ACCUPARSERDay,
    ACCUPARSERDegrees,
    ACCUPARSERDirection,
    ACCUPARSEREnglish,
    ACCUPARSEREpochDateTime,
    ACCUPARSEREpochRise,
    ACCUPARSEREpochSet,
    ACCUPARSEREpochTime,
    ACCUPARSERHoursOfSun,
    ACCUPARSERIce,
    ACCUPARSERIceProbability,
    ACCUPARSERIconPhrase,
    ACCUPARSERImperial,
    ACCUPARSERIsDaylight,
    ACCUPARSERIsDayTime,
    ACCUPARSERLocalObservationDateTime,
    ACCUPARSERLongPhrase,
    ACCUPARSERMaximum,
    ACCUPARSERMetric,
    ACCUPARSERMinimum,
    ACCUPARSERMoon,
    ACCUPARSERNight,
    ACCUPARSERPrecip1hr,
    ACCUPARSERPrecipitationProbability,
    ACCUPARSERPressure,
    ACCUPARSERRain,
    ACCUPARSERRainProbability,
    ACCUPARSERRealFeelTemperature,
    ACCUPARSERRealFeelTemperatureShade,
    ACCUPARSERRelativeHumidity,
    ACCUPARSERShortPhrase,
    ACCUPARSERSnow,
    ACCUPARSERSnowProbability,
    ACCUPARSERSpeed,
    ACCUPARSERSun,
    ACCUPARSERTemperature,
    ACCUPARSERThunderstormProbability,
    ACCUPARSERTotalLiquid,
    ACCUPARSERUnit,
    ACCUPARSERUVIndex,
    ACCUPARSERUVIndexText,
    ACCUPARSERValue,
    ACCUPARSERVisibility,
    ACCUPARSERWeatherIcon,
    ACCUPARSERWeatherText,
    ACCUPARSERWind,
    ACCUPARSERWindGust,
    ACCUPARSERDailyForecasts,
    ACCUPARSERDate,
    ACCUPARSEREpochDate,
    ACCUPARSERIcon,
};

//I do this to save memory - by default enums are ints, so to save a bit of memory I use chars instead.
//WARNING: change this if you will need more than 256 tokens
typedef uint8_t AccuParserTokens;

//The parser creates a stack while parsing the JSON response. This allows a lot of flexibility when creating a parser (e.g. we can infer all previous keys and objects before a given value)
//The stack contains tokens instead of strings. This greatly reduces memory usage and allows us to compare stack contents much quicker.
class WeatherApiParser: public JsonListener {
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
        std::vector<AccuParserTokens> tokenStack;
        void DEBUG_printStack();
        bool stackSuffix(const AccuParserTokens suffix[], int suffix_len);
        bool stackContains(const AccuParserTokens token);
        void popAllKeys();
        int baseListIdx = -1;
        int maxListLength = INT_MAX;
        bool listFull = false;
};

//Descendant classes for parsing particular types of responses
class AccuweatherCurrentParser: public WeatherApiParser {
    public:
        AccuweatherCurrentParser(WeatherApiCurrentData* data_ptr_);
        virtual void value(String value);
    protected:
        WeatherApiCurrentData* data_ptr;
};

class AccuweatherHourlyParser: public WeatherApiParser {
    public:
        AccuweatherHourlyParser(WeatherApiHourlyData* data_ptr_, int maxListLength_);
        virtual void value(String value);
    protected:
        WeatherApiHourlyData* data_ptr;
};

class AccuweatherDailyParser: public WeatherApiParser {
    public:
        AccuweatherDailyParser(AccuweatherDailyData* data_ptr_, int maxListLength_);
        virtual void startObject();
        virtual void value(String value);
    protected:
        AccuweatherDailyData* data_ptr;
};

//Main class for sending requests and parsing responses
class WeatherApi {
public:
    WiFiClient client;
    HTTPClient http;
    JsonStreamingParser parser;
    WeatherApiParser* listener = NULL;
    const int locationID;
    const char* apiKey;
    int length;

    WeatherApi(const char* apiKey_, const int locationID_):
        locationID(locationID_),
        apiKey(apiKey_){
    }

    int getForecast(WeatherApiCurrentData* data_ptr);
    int continueDownload();
    void freeConnection();
};
