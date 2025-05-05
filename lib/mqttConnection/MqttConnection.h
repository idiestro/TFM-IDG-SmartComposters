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
    const unsigned long reconnectInterval = 5000; // 5 segundos
    const unsigned long keepAliveInterval = 60;   // 60 segundos

    void wifiConnection(const char* wifiSsid, const char* wifiPassword);
    void brokerConnection();
    bool reconnect();
    static void callback(char* topic, byte* payload, unsigned int length);

public:
    // Constructor
    MqttConnection();

    void init();
    void topicSubscription(const char* subscriptionTopic);
    void topicPublication(String payload, const char* publicationTopic);
    void setClientId();
    void loop(); // Nuevo método para manejar el loop

    // Getter para cliente MQTT
    PubSubClient getMqttClient();
    String getClientId();
};

#endif
