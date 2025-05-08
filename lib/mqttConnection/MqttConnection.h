/*
    MqttConnection.h - Header for mqtt transfer protocol
    Created by Ignacio Diestro Gil - 2025
*/

#ifndef MQTTCONNECTION_h
#define MQTTCONNECTION_h

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

class MqttConnection {
private:
    String clientId;
    WiFiClient espClient;
    PubSubClient client;
    unsigned long lastReconnectAttempt = 0;
    const unsigned long reconnectInterval = 5000; // 5 sec
    const unsigned long keepAliveInterval = 15;   // 60 sec

    void wifiConnection();
    void brokerConnection();

public:
    // Constructor
    MqttConnection();

    void init();
    void reconnect();
    void topicSubscription();
    void topicPublication(String payload);
    void setClientId();
    void loop();
    void handleCallback(char* topic, byte* payload, unsigned int length);

    // Getter for mqtt client
    PubSubClient getMqttClient();
    String getClientId();

};

#endif
