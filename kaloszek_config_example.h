
//=========================================================================================================================================== wifi
const char* ssid_1 = "xxxx";              //your wifi_1 ssid
const char* password_1 = "xxxx";          //your wifi_1 password

const char* ssid_2 = "xxxx";              //your wifi_2 ssid
const char* password_2 = "xxxx";          //your wifi_1 password

//=========================================================================================================================================== accuweather keys
const int ACU_MAX_KEYS = 0;               //number of accuweather keys

const char acu_keys[][33] =               //your accuweather keys
{
  "key_1",
  "key_2",
  "key_3",
  "key_4"
};
//=========================================================================================================================================== airly configuration
const char airly_key[] = "xxx";
const char airly_longitude[] = "xx.xxxxxxxxxxxxx";	//longitude
const char airly_latitude[] = "xx.xxxxxxxxxxxxx";	//latitude
int distance = 5;									//Distance in km in which the sensors will be searched from the given position. The value -1 means no limit.