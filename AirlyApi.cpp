/*
  The MIT License (MIT)

  Airly is 'Airly sp. z o.o.' trademark.
  More About Airly https://airly.eu/en/company/

*/
#include "AirlyApi.h"
#define HTTP_DATA_CHUNK (128)

AirlyApi::AirlyApi(const char* apiKey, const char* lat, const char* lng, int distance)  {
  _apiKey = apiKey;
  _lat = lat;
  _lng = lng;
  _distance = distance;
}

bool AirlyApi::getNearestSensor() {
  String command = "/v2/installations/nearest?lat=" + String(_lat) + "&lng=" + String(_lng) + "&maxDistance=" + String(_distance) + "&maxResults=1";
  return doUpdate(command);
}

bool AirlyApi::getSensorValues(int locationId) {
  String command = "/v2/measurements/installation?installationId=" + String(locationId);
  return doUpdate(command);
}

bool AirlyApi::doUpdate(String url) {
  yield();
  JsonStreamingParser parser;
  parser.setListener(this);
  bool result = false;

  String full_url = String(AILRLY_API_ADDRESS + url);
#ifdef USE_SERIAL_PORT
  Serial.println(full_url);
#endif

  if (!http.begin(String(AILRLY_API_ADDRESS + url)))
  {
#ifdef USE_SERIAL_PORT
    Serial.println("AirlyApi: http.begin error");
#endif
    return false;
  }

  http.addHeader("apikey", _apiKey, true, true);
  http.addHeader("Accept", "application/json");

  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {

      int len = http.getSize();

      char char_buff[HTTP_DATA_CHUNK];
      WiFiClient * stream = http.getStreamPtr();

      while (http.connected() && (len > 0 || len == -1)) {
        size_t size = stream->available();
        if (size) {
          int c = stream->readBytes(char_buff, ((size > sizeof(char_buff)) ? sizeof(char_buff) : size));
          if (len > 0)
            len -= c;

          for (int i = 0; i < c; i++)
            parser.parse(char_buff[i]);
        }
      }
      if (len > 0)
        result = false;
      else
        result = true;
    }
  } else
  {
#ifdef USE_SERIAL_PORT
    Serial.printf("AirlyApi: GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
#endif
  }
  http.end();

  return result;
}

void AirlyApi::whitespace(char c) {
}

void AirlyApi::startDocument() {
}

void AirlyApi::key(String key) {
  // Serial.println("*----------------------------------------*\ncurrentParent: " + currentParent);
  //  Serial.println("key: " + key);
  currentKey = String(key);
}

void AirlyApi::value(String value) {
  //Serial.println("value: " + value);
  if (currentParent == "") {
    if (currentKey == "id") {
      locationId = value.toInt();
    }
  } else if (currentParent == "indexes") {
    if (currentKey == "value") {
      airQualityIndex = value.toFloat();
    } else if (currentKey == "level") {
      airQualityLevel = value;
    }
  }
}

void AirlyApi::endArray() {
}

void AirlyApi::endObject() {
  currentParent = "";
  currentKey = "";
}

void AirlyApi::endDocument() {
}

void AirlyApi::startArray() {
}

void AirlyApi::startObject() {
  currentParent = currentKey;
}
/////////////////////////g e t t e r s

int AirlyApi::getLocationId() {
  return locationId;
}
float AirlyApi::getAirQualityIndex() {
  return airQualityIndex;
}
String AirlyApi::getAirQualityLevel() {
  return airQualityLevel;
}
