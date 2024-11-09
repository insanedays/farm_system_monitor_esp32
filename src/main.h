#ifndef MAIN_H
#define MAIN_H

#ifdef UNIT_TEST
// Mock includes
#include "mock_Arduino.h"
#include "mock_Serial.h"
#include "mock_DHT.h"
#include "mock_Wire.h"
#include "mock_LiquidCrystal_I2C.h"
#include "mock_WiFi.h"
#include "mock_WiFiClient.h"
#include "mock_PubSubClient.h"
#include "mock_ArduinoJson.h"
#include "mock_Adafruit_Sensor.h"
#else
// Actual includes
#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#endif

// Pin definitions and other code remains the same
#define PIN_DHT 23
#define DHT_MODEL DHT22
#define PIN_PIR 15
#define PIN_LDR 34
#define PIN_HC_TRIG 5
#define PIN_HC_ECHO 22
#define SOUND_SPEED 0.034
#define ID_MQTT "FIAP_CAP12"
#define pubSensorHumidity "humidity_temperature"
#define pubSensorSound "sound"
#define pubSensorLux "lux"
#define pubSensorMovi "movi"

// WiFi credentials
extern const char* SSID;
extern const char* PASSWORD;
extern const char* BROKER_MQTT;
extern int BROKER_PORT;

// Global objects
extern WiFiClient wifiClient;
extern PubSubClient MQTT;
extern DHT dht22;
extern LiquidCrystal_I2C lcd;

// Function declarations
void AtualizaConexoes();
void ConectaWiFi();
void ConectaMQTT();
void EnviaValores(const char* topic, float value1, float value2 = 0);
void RecebePacote(char* topic, byte* payload, unsigned int length);

// Sensor functions
void humidity_temperature();
void sound();
void lux();
void movi();

#endif // MAIN_H
