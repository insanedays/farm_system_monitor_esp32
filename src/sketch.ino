#include <DHT.h>  // Biblioteca sensor umidade

// Definições de pinos e modelo dos sensores
#define PIN_DHT 23      // Pino GPIO do sensor DHT
#define DHT_MODEL DHT22 // Modelo do sensor DHT
#define PIN_PIR 34      // Pino GPIO conectado ao pino OUT do sensor PIR
#define PIN_LDR 15      // Pino GPIO do sensor LDR
#define PIN_HC_TRIG 5   // Pino GPIO conectado ao Trig do HC-SR04
#define PIN_HC_ECHO 22  // Pino GPIO conectado ao Echo do HC-SR04
//#define PIN_LED        

// Inicialização do sensor de umidade
DHT dht22(PIN_DHT, DHT_MODEL);

void setup() {
    // Inicializaçoes necessárias 
    Serial.begin(9600);    // Inicia conexão com computador
    dht22.begin();         // Inicia sensor de umidade DHT

    // Configuração dos pinos dos sensores
    pinMode(PIN_PIR, INPUT);       // Configura o pino do sensor PIR como entrada
    pinMode(PIN_LDR, INPUT);       // Configura o pino do sensor LDR como entrada
    pinMode(PIN_HC_TRIG, OUTPUT);  // Configura o pino TRIG do sensor ultrassônico como saída
    pinMode(PIN_HC_ECHO, INPUT);   // Configura o pino ECHO do sensor ultrassônico como entrada
    // pinMode(PIN_LED, OUTPUT);   // Configura o pino do LED como saída (se necessário)
}

void loop() {
    // Inicia uma medição do sensor ultrassônico HC-SR04
    digitalWrite(PIN_HC_TRIG, HIGH); 
    delayMicroseconds(10);
    digitalWrite(PIN_HC_TRIG, LOW);
   
    // Leitura dos resultados dos sensores
    float umidade = dht22.readHumidity();             // Lê umidade do sensor DHT
    float temperatura = dht22.readTemperature();      // Lê temperatura do sensor DHT
    int movimento = digitalRead(PIN_PIR);             // Lê o estado do sensor de movimento PIR
    int luz = analogRead(PIN_LDR);                    // Lê o valor do sensor de luz LDR
    int duracao_sinal = pulseIn(PIN_HC_ECHO, HIGH);   // Lê o tempo do sinal do sensor ultrassônico HC-SR04
    float distancia = duracao_sinal/58;               // Calcula a distância do sinal medido pelo sensor ultrassônico HC-SR04 em cm

    // Verificação de erro de leitura do sensor de umidade e temperatura
    if (isnan(umidade) || isnan(temperatura)) {
        Serial.println("Falha ao ler do sensor DHT!");
        return;
    }
    
    delay(2000);  // Aguarda 2 segundos antes de ler novamente
}
