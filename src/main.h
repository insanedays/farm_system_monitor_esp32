#ifndef MAIN_H
#define MAIN_H

#ifdef UNIT_TEST
#include "mock_ArduinoJson.h"
#else
#include <ArduinoJson.h>
#endif

#ifdef UNIT_TEST
#include "mock_Arduino.h"
#endif

#ifdef UNIT_TEST
// Inclua os mocks no ambiente de teste
#include "mock_Serial.h"
#include "mock_WiFi.h"
#include "mock_MQTT.h"
#include "mock_DHT.h"
#include "mock_LiquidCrystal_I2C.h"
typedef unsigned char byte;
#else
// Inclua as bibliotecas reais para o ESP32
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

extern HardwareSerial Serial;
extern WiFiClass WiFi;
extern PubSubClient MQTT;
#endif

// Definições de pinos e outras configurações
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



// Credenciais WiFi
extern const char* SSID;
extern const char* PASSWORD;
extern const char* BROKER_MQTT;
extern int BROKER_PORT;

// Objetos globais
extern DHT dht22;
extern LiquidCrystal_I2C lcd;

// Funções globais
void AtualizaConexoes();
void ConectaWiFi();
void ConectaMQTT();
void EnviaValores(const char* topic, float value1, float value2 = 0);
void RecebePacote(char* topic, byte* payload, unsigned int length);
void humidity_temperature();
void sound();
void lux();
void movi();

#endif // MAIN_H
