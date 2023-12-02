#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <BH1750.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

BH1750 lightMeter;
#define USE_BH1750_LIB

#define DHT_PIN 4
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

const char *ssid = "Pe";
const char *password = "1w3r5y7i";
int lastRequest = 0;
const size_t capacity = JSON_OBJECT_SIZE(2);
char message[1024];

TaskHandle_t telegramTaskHandle;
TaskHandle_t luxTaskHandle;
DynamicJsonDocument doc(capacity);
HTTPClient http;

float lux;

void setupWifi();
void telegramTask(void *parameter);
void luxTask(void *parameter);
void teleSendMessage(String payload);

void setup()
{
  Serial.begin(9600);

  Wire.begin();

  dht.begin();

  lightMeter.begin();
  Serial.println(F("BH1750 Test begin"));

  pinMode(BUILTIN_LED, OUTPUT);
  vTaskDelay(1000);

  setupWifi();

  ESP_LOGI("SETUP", "Create freertos task!");
  // Create RTOS task
  xTaskCreate(telegramTask, "Telegram Task", 4096, NULL, 1, &telegramTaskHandle);
  xTaskCreate(luxTask, "LUX Task", 4096, NULL, 2, &luxTaskHandle);
  delay(1000);
}

void loop()
{

  // put your main code here, to run repeatedly:
  if (millis() - lastRequest > 10000)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      setupWifi();
    }
    else
    {
      ESP_LOGI("WIFI", "WiFi is already connected...");
    }

    lastRequest = millis();
  }
}

void telegramTask(void *parameter)
{
  // EventBits_t clientBits;
  float tempFloat = 0.0, humidFloat = 0.0;

  dht.begin();

  for (;;)
  {
    tempFloat = dht.readTemperature();
    humidFloat = dht.readHumidity();
    lux = lightMeter.readLightLevel();

    String pesan = "Light = " + String(lux) + " lx\nTemperature = " + String(tempFloat) + " °C\nHumidity = " + String(humidFloat) + " %";

    doc["chat_id"] = 5656754523;
    doc["text"] = pesan.c_str();

    serializeJson(doc, message);
    teleSendMessage(message);
    Serial.println(pesan);

    digitalWrite(BUILTIN_LED, HIGH);
    delay(1000);
    digitalWrite(BUILTIN_LED, LOW);

    delay(60000);
  }
}

void luxTask(void *parameter)
{
  for (;;)
  {
    lux = lightMeter.readLightLevel();
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");
    delay(1000);
  }
}

void setupWifi()
{
  vTaskDelay(10);
  // We start by connecting to a WiFi network
  ESP_LOGI("WIFI", "Connecting to %s", ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    vTaskDelay(500);
    ESP_LOGI("WIFI", ".");
  }
  ESP_LOGI("WIFI", "WiFi is connected!");
}

void teleSendMessage(String payload)
{
  ESP_LOGI("TELE", "HTTP Payload: %s", payload.c_str());
  http.begin("https://api.telegram.org/bot6463878279:AAHjPa9egdSbvbc63xhMetcfj5gvUiwmtIQ/sendMessage");
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0)
  {
    String response = http.getString(); // Get the response to the request

    ESP_LOGI("TELE", "HTTP Response code: %d", httpResponseCode); // Print return code
    ESP_LOGI("TELE", "Response: %s", response.c_str());           // Print request answer
  }
  else
  {
    ESP_LOGI("TELE", "Error on sending POST: %d", httpResponseCode);
  }

  http.end();
}