#include <Arduino.h>
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>
#include <ESP8266WiFi.h>
#include "settings.h"
#include "wifi.h"
#include "board.h"

WiFiClient wifiClient;
String MAC_ADDR = WiFi.macAddress();

unsigned long int lastConnectionAttempt = 0;
taskid_t wifiTask = 0; 

void waitForConnection(void(*onConnection)()) {
    if(WiFi.status() != WL_CONNECTED) {
        auto retryTask = new ExecWithParameter<void(*)()>(waitForConnection, onConnection);
        taskManager.scheduleOnce(600, retryTask, TIME_MILLIS, true);
        blink(2);
        return;
    }

    Serial.print("WiFi connected in ");
    Serial.print(millis());
    Serial.print("ms since startup, IP address: ");
    Serial.println(WiFi.localIP());
    taskManager.execute(onConnection);
}

void assertWifiConnection(void(*onConnection)()) {
    if(WiFi.status() == WL_CONNECTED) {
        return;
    }

    if(millis() - lastConnectionAttempt < RECONNECTION_COOLDOWN && lastConnectionAttempt != 0) {
        return;
    }
    lastConnectionAttempt = millis();

    Serial.print("Connecting to WiFI: ");
    Serial.println(WIFI_SSID);
    Serial.print("MAC Address: ");
    Serial.println(MAC_ADDR);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    waitForConnection(onConnection);
}

void connectWifi(void(*onConnection)()) {
    if(wifiTask) {
        return;
    }

    auto wifiAssertionTask = new ExecWithParameter<void(*)()>(assertWifiConnection, onConnection);
    
    taskManager.execute(wifiAssertionTask);
    wifiTask = taskManager.scheduleFixedRate(RECONNECTION_INTERVAL, wifiAssertionTask, TIME_MILLIS);
}
