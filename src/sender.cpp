#include <ESP8266WiFi.h>
#include <espnow.h>

#define LED 2

uint8_t remoteMac[] = {0x1A, 0xFE, 0x34, 0xD5, 0xFA, 0x39};

#define WIFI_CHANNEL 1
#define SEND_TIMEOUT 245 // 245 millis seconds timeout

struct __attribute__((packed)) SENSOR_DATA
{
  int count;
} sensorData;

void setup()
{
  Serial.begin(115200);
  Serial.println("ESP_Now Controller");
  Serial.printf("This mac: %s, ", WiFi.macAddress().c_str());
  Serial.printf("target mac: %02x%02x%02x%02x%02x%02x", remoteMac[0], remoteMac[1], remoteMac[2], remoteMac[3], remoteMac[4], remoteMac[5]);
  Serial.printf(", channel: %i\n", WIFI_CHANNEL);

  pinMode(LED, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0)
  {
    Serial.println("*** ESP_Now init failed");
    ESP.restart();
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(remoteMac, ESP_NOW_ROLE_SLAVE, WIFI_CHANNEL, NULL, 0);
  esp_now_register_send_cb([](uint8_t *mac, uint8_t status)
                           {
                             if (status == 0)
                             {
                               digitalWrite(LED, LOW);
                             }
                             Serial.printf("Sending %i, status = %s\n", sensorData.count, status == 0 ? "Success" : "Fail");
                           });
}

void loop()
{
  digitalWrite(LED, HIGH);
  sensorData.count++;
  esp_now_send(NULL, (uint8_t *)&sensorData, sizeof(sensorData));
  delay(100);
}