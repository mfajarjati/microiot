#include <Arduino.h>
#include <Preferences.h>

// #define STRING_DEMO_ENABLE

#define STORAGE_NAME "storage"
#define LED_STATUS_KEY "led"
#define SSID_KEY "ssid"
#define BUTTON_PIN 21

bool ledStatus = LOW;
bool changeLedStatus = false;
portMUX_TYPE gpioIntMux = portMUX_INITIALIZER_UNLOCKED;

Preferences storage;
String ssid;
uint32_t dataIndex = 0;

void IRAM_ATTR gpioISR()
{
  portENTER_CRITICAL(&gpioIntMux);
  changeLedStatus = true;
  portEXIT_CRITICAL(&gpioIntMux);
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUILTIN_LED, OUTPUT);
  attachInterrupt(BUTTON_PIN, &gpioISR, FALLING);

  Serial.begin(9600);

  // Initialize Preferences and read LED status
  storage.begin(STORAGE_NAME);
  delay(100);
  ledStatus = storage.getBool(LED_STATUS_KEY);
  digitalWrite(BUILTIN_LED, ledStatus);

  // Print current SSID
  ssid = storage.getString(SSID_KEY);
  ESP_LOGI("SETUP", "SSID name: %s", ssid);
  ssid.clear();
  storage.end();
}

void loop()
{
  // put string data
  if (Serial.available())
  {
    ssid[dataIndex] = Serial.read();
    dataIndex++;

    if (ssid[dataIndex - 1] == '\n')
    {
      dataIndex = 0;
      storage.begin(STORAGE_NAME);
      storage.putString(SSID_KEY, ssid);
      ssid.clear();
      storage.end();
    }
  }
}