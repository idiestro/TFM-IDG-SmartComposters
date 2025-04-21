/*
    MqttConnection.h - Header for mqtt transfer protocol
    Created by Ignacio Diestro Gil - 2025
*/

#ifndef MQTTCONNECTION_h
#define MQTTCONNECTION_h

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Declaración de la función callback, para que el cliente la pueda usar
void callback(char* topic, byte* message, unsigned int length);

class MqttConnection {
private:
    String clientId;
    WiFiClient espClient;
    PubSubClient client;

    void wifiConnection(const char* wifiSsid, const char* wifiPassword);
    void brokerConnection();

public:
    // Constructor
    MqttConnection();

    void init();
    void topicSubscription(const char* subscriptionTopic);
    void topicPublication(String payload, const char* publicationTopic);
    void setClientId();

    // Getter para cliente MQTT
    PubSubClient getMqttClient();
    String getClientId();
};

#endif
