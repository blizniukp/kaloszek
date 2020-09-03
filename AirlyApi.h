/*
  The MIT License (MIT)

  Airly is 'Airly sp. z o.o.' trademark.
  More About Airly https://airly.eu/en/company/

*/
#define DEBUG_ESP_HTTP_CLIENT
#define DEBUG_ESP_PORT

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <JsonListener.h>
#include <JsonStreamingParser.h>

#include <Arduino.h>
#include <ArduinoJson.h>

#define AILRLY_API_ADDRESS "http://airapi.airly.eu"



class AirlyApi: public JsonListener {
  public:
    AirlyApi (const char* apiKey, const char* lat, const char* lng, int distance);
    bool getSensorValues(int locationId);
    bool getNearestSensor();

    int getLocationId();
    float getAirQualityIndex();
    String getAirQualityLevel();

  private:
    bool doUpdate(String url);
    const char* _apiKey;
    const char* _lat;
    const char* _lng;
    int _distance;
    String currentKey;
    String currentParent = "";

    int locationId;
    float airQualityIndex;
    String airQualityLevel;

    HTTPClient http;

    virtual void whitespace(char c);

    virtual void startDocument();

    virtual void key(String key);

    virtual void value(String value);

    virtual void endArray();

    virtual void endObject();

    virtual void endDocument();

    virtual void startArray();

    virtual void startObject();
};
