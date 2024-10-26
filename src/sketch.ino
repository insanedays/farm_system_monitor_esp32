#include <DHT.h>  // Biblioteca para o sensor de umidade e temperatura DHT
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Biblioteca para o LCD I2C

// Definições de pinos e modelo dos sensores
#define PIN_DHT 23      // Pino GPIO do sensor DHT
#define DHT_MODEL DHT22 // Modelo do sensor DHT (DHT22)
#define PIN_PIR 15      // Pino GPIO conectado ao pino OUT do sensor PIR
#define PIN_LDR 34      // Pino GPIO do sensor LDR
#define PIN_HC_TRIG 5   // Pino GPIO conectado ao Trig do HC-SR04
#define PIN_HC_ECHO 22  // Pino GPIO conectado ao Echo do HC-SR04
#define PIN_LED 2       // Pino GPIO para o LED indicador (caso queira usar)

#define SOUND_SPEED 0.034 // Velocidade do som em cm/us
#define CM_TO_INCH 0.393701 // Fator de conversão de cm para polegadas

// LDR Characteristics
const float GAMMA = 0.7;
const float RL10 = 50;

// Inicialização do sensor de umidade e temperatura
DHT dht22(PIN_DHT, DHT_MODEL);

// Inicialização do LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço do LCD I2C com 16 colunas e 2 linhas

void setup() {
    // Inicializações necessárias
    Serial.begin(9600);          // Inicia a comunicação serial para depuração (opcional)
    dht22.begin();               // Inicia o sensor de umidade e temperatura DHT
    Wire.begin(19, 18);  // Define os novos pinos SDA e SCL
    lcd.init();                  // Inicia o display LCD
    lcd.backlight();             // Liga a luz de fundo do LCD

    // Configuração dos pinos dos sensores
    pinMode(PIN_PIR, INPUT);       // Configura o pino do sensor PIR como entrada
    pinMode(PIN_LDR, INPUT);       // Configura o pino do sensor LDR como entrada
    pinMode(PIN_HC_TRIG, OUTPUT);  // Configura o pino TRIG do sensor ultrassônico como saída
    pinMode(PIN_HC_ECHO, INPUT);   // Configura o pino ECHO do sensor ultrassônico como entrada
    pinMode(PIN_LED, OUTPUT);      // Configura o pino do LED como saída
}

// Função para medir a distância com o HC-SR04
void sound() {
    digitalWrite(PIN_HC_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_HC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_HC_TRIG, LOW);
  
    long duration = pulseIn(PIN_HC_ECHO, HIGH);    
    float distanceCm = duration * SOUND_SPEED / 2;

    // Exibe a distância no LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Nivel Agua: ");
    lcd.print(distanceCm);
    lcd.print("cm");

    delay(2000); // Espera 2 segundos antes da próxima leitura
}

// Função para medir a luminosidade com o LDR
void lux() {
    int analogValue = analogRead(PIN_LDR);
    float voltage = analogValue / 4095.0 * 3.3; // Conversão para tensão (para ESP32)
    float resistance = 2000 * voltage / (3.3 - voltage);
    float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));

    // Exibe a luminosidade no LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Luminosidade: ");
    lcd.print(lux);

    delay(2000);
}

// Função para medir umidade e temperatura com o DHT22
void humidity_temperature() {
    float umidade = dht22.readHumidity();             // Lê umidade do sensor DHT
    float temperatura = dht22.readTemperature();      // Lê temperatura do sensor DHT
    
    if (isnan(umidade) || isnan(temperatura)) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Erro no sensor DHT");
    } else {
        // Exibe temperatura e umidade no LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(temperatura);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("Umid: ");
        lcd.print(umidade);
        lcd.print("%");

        delay(2000);
    }
}

// Função para detectar movimento com o PIR
void movi() {
  int movimento = digitalRead(PIN_PIR);             // Lê o estado do sensor de movimento PIR
  lcd.clear();
  lcd.setCursor(0, 0);
  if (movimento == HIGH) {
        lcd.print("Movimento detectado!");
        digitalWrite(PIN_LED, HIGH); // Acende o LED quando movimento for detectado
  } else {
        lcd.print("Nenhum movimento.");
        digitalWrite(PIN_LED, LOW);  // Apaga o LED quando não houver movimento
  }

  delay(2000);
}

void loop() {
    humidity_temperature(); // Monitora o clima
    sound();                // Verifica o nível de água
    lux();                  // Monitora a luminosidade
    movi();                 // Detecta movimento
}

git config --global user.email "kild_bf@hotmail.com"
git config --global user.name "KildFernandes"