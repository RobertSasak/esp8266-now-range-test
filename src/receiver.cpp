#include <ESP8266WiFi.h>
#include <espnow.h>

#define LED 2

struct __attribute__((packed)) SENSOR_DATA
{
    int count;
} sensorData;
uint8_t mac[] = {0x1A, 0xFE, 0x34, 0xD5, 0xFA, 0x39};

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_AP);
    wifi_set_macaddr(SOFTAP_IF, &mac[0]);

    Serial.print("This node AP mac: ");
    Serial.println(WiFi.softAPmacAddress());
    Serial.print("This node STA mac: ");
    Serial.println(WiFi.macAddress());

    if (esp_now_init() != 0)
    {
        Serial.println("*** ESP_Now init failed");
        ESP.restart();
    }
    pinMode(LED, OUTPUT);
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

    esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len)
                             {
                                 digitalWrite(LED, LOW);
                                 Serial.print("$$ Received from MAC: ");
                                 for (int i = 0; i < 6; i++)
                                 {
                                     Serial.printf("%02X", mac[i]);
                                     if (i < 5)
                                         Serial.print(":");
                                 }
                                 Serial.print(" ");
                                 Serial.print(len);
                                 SENSOR_DATA *d = (SENSOR_DATA *)data;
                                 Serial.print(d->count);
                                 Serial.println();
                             });
}

int heartBeat;

void loop()
{
    digitalWrite(LED, HIGH);
    if (millis() - heartBeat > 30000)
    {
        Serial.println("Waiting for ESP-NOW messages...");
        heartBeat = millis();
    }
}
