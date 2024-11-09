#include "main.h"

// WiFi credentials
const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";
const char* BROKER_MQTT = "mqtt-dashboard.com";
int BROKER_PORT = 1883;

// Global objects
WiFiClient wifiClient;
PubSubClient MQTT(wifiClient);
DHT dht22(PIN_DHT, DHT_MODEL);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Function to send values via MQTT
void EnviaValores(const char* topic, float value1, float value2) {
    DynamicJsonDocument doc(200);
    if (value1 != 0) doc["value1"] = value1;
    if (value2 != 0) doc["value2"] = value2;

    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);
    MQTT.publish(topic, jsonBuffer);
}

// Function to measure and display temperature and humidity
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

// Function to measure and display water level
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

// Function to measure and display light intensity
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

// Function to detect and display motion
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

// Function to update WiFi and MQTT connections
void AtualizaConexoes() {
    if (!MQTT.connected()) {
        ConectaMQTT();
    }
    ConectaWiFi();
}

// Function to connect to WiFi
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

// Function to connect to MQTT broker
void ConectaMQTT() {
    while (!MQTT.connected()) {
        Serial.print("Conectando ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) {
            Serial.println("Conectado ao Broker com sucesso!");
            MQTT.subscribe(pubSensorMovi);
        } else {
            Serial.println("Falha de conexao, tentativa em 10s");
            delay(10000);
        }
    }
}

// Callback to receive MQTT packets
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

// Initial setup
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

// Main loop
void loop() {
    AtualizaConexoes();
    MQTT.loop();
    humidity_temperature();
    sound();
    lux();
    movi();
}
