#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h> 
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>

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

const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";
const char* BROKER_MQTT = "mqtt-dashboard.com";
int BROKER_PORT = 1883;
WiFiClient wifiClient;
PubSubClient MQTT(wifiClient);

DHT dht22(PIN_DHT, DHT_MODEL);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//----------------------Declaração das Funções
void AtualizaConexoes();            // Atualiza conexões com WiFi e Broker MQTT
void ConectaWiFi();                 // Faz conexão com WiFi
void ConectaMQTT();                 // Faz conexão com Broker MQTT
void EnviaValores(const char* topic, float value1, float value2);  // Envia valores ao tópico MQTT específico
void RecebePacote(char* topic, byte* payload, unsigned int length);    // Callback para receber pacotes MQTT
void humidity_temperature();        // Função para medir e exibir temperatura e umidade
void sound();                       // Função para medir e exibir nível de água (sensor ultrassônico)
void lux();                         // Função para medir e exibir luminosidade (LDR)
void movi();                        // Função para detectar e exibir movimento (PIR)
//-----------------------------------------------

void setup() {
    Serial.begin(9600);
    dht22.begin();
    Wire.begin(19, 18);
    lcd.init();
    lcd.backlight();

    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_LDR, INPUT);
    pinMode(PIN_HC_TRIG, OUTPUT);
    pinMode(PIN_HC_ECHO, INPUT);

    ConectaWiFi();
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);  
    MQTT.setCallback(RecebePacote);  
}

// Implementação das funções

void EnviaValores(const char* topic, float value1, float value2 = 0) {
    StaticJsonDocument<200> doc;
    if (value1 != 0) doc["value1"] = value1;
    if (value2 != 0) doc["value2"] = value2;

    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);
    MQTT.publish(topic, jsonBuffer);
}

void humidity_temperature() {
    float umidade = dht22.readHumidity();
    float temperatura = dht22.readTemperature();
    if (isnan(umidade) || isnan(temperatura)) {
        lcd.clear();
        lcd.print("Erro no sensor DHT");
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(temperatura);
        lcd.setCursor(0, 1);
        lcd.print("Umid: ");
        lcd.print(umidade);
    }
    EnviaValores(pubSensorHumidity, umidade, temperatura);
    delay(2000);
}

void sound() {
    digitalWrite(PIN_HC_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_HC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_HC_TRIG, LOW);
    long duration = pulseIn(PIN_HC_ECHO, HIGH);
    float distanceCm = duration * SOUND_SPEED / 2;
    lcd.clear();
    lcd.print("Nivel Agua:");
    lcd.setCursor(0, 1);
    lcd.print(distanceCm);
    EnviaValores(pubSensorSound, distanceCm);
    delay(2000);
}

void lux() {
    int analogValue = analogRead(PIN_LDR);
    float voltage = analogValue / 4095.0 * 3.3;
    float lux = 500 / (3.3 - voltage);
    lcd.clear();
    lcd.print("Luminosidade:");
    lcd.setCursor(0, 1);
    lcd.print(lux);
    EnviaValores(pubSensorLux, lux);
    delay(2000);
}

void movi() {
    int movimento = digitalRead(PIN_PIR);
    lcd.clear();
    if (movimento == HIGH) {
        lcd.print("Movimento detectado");
    } else {
        lcd.print("Nenhum movimento");
    }
    EnviaValores(pubSensorMovi, movimento);
    delay(2000);
}

void AtualizaConexoes() {
    if (!MQTT.connected()) {
       ConectaMQTT(); 
    }
    ConectaWiFi();
}

void ConectaWiFi() {
    if (WiFi.status() == WL_CONNECTED) return;
    Serial.print("Conectando-se na rede: ");
    Serial.print(SSID);
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Conectado com sucesso, na rede: ");
    Serial.println(WiFi.localIP());
}

void ConectaMQTT() { 
    while (!MQTT.connected()) {
        Serial.print("Conectando ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) {
            Serial.println("Conectado ao Broker com sucesso!");
            MQTT.subscribe(pubSensorMovi);  // Adjust if there are topics to subscribe to
        } else {
            Serial.println("Falha de conexao, tentativa em 10s");
            delay(10000);
        }
    }
}

void RecebePacote(char* topic, byte* payload, unsigned int length) {
    String msg;
    for (int i = 0; i < length; i++) {
        msg += (char)payload[i];
    }
    Serial.print("Mensagem recebida [");
    Serial.print(topic);
    Serial.print("]: ");
    Serial.println(msg);
}

void loop() {
    AtualizaConexoes();
    MQTT.loop();
    humidity_temperature();
    sound();
    lux();
    movi();
}
