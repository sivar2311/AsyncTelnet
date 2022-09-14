#include <Arduino.h>
#include <WiFi.h>
#include <Telnet.h>

const char* wifi_ssid = "";
const char* wifi_pass = "";

void setup() {
    Serial.begin(115200);

    Serial.print("Connecting wifi...");
    WiFi.begin(wifi_ssid, wifi_pass);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print("."); delay(100);
    }
    Serial.printf("connected! IP is %s\r\n", WiFi.localIP().toString().c_str());
    Telnet.begin(23);
}

void loop() {
    Serial.println("Hello to serial console");
    Telnet.println("Hello to all telnet clients!");
    delay(2000);
}