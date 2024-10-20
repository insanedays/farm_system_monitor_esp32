# Nome do projeto
## Objetivo

### Sensores utilizados
#### 1. Sensor de Umidade e Temperatura (DHT22)
- **Descrição**: Sensor que mede a temperatura e a umidade do ambiente.
- **Pinos**:
  - **VCC**: Conectar ao pino VCC (5V ou 3.3V)
  - **GND**: Conectar ao pino GND
  - **Data**: Conectar a um pino digital 
- **Uso**: Fornece dados críticos para controle de irrigação.

#### 2. Sensor de Ultrassom (HC-SR04)
- **Descrição**: Sensor que mede a distância de objetos, usado para monitorar o nível de água.
- **Pinos**:
  - **VCC**: Conectar ao pino VCC (5V)
  - **GND**: Conectar ao pino GND
  - **Trig**: Conectar ao pino digital 
  - **Echo**: Conectar ao pino digital 
- **Uso**: Monitora o nível de água do reservatório, permitindo utilizar a irrigação apenas quando o nível está adequado, evitando desperdício de água.

#### 3. Sensor de Movimento (PIR)
- **Descrição**: Sensor que detecta movimento, útil para segurança e vigilância.
- **Pinos**:
  - **VCC**: Conectar ao pino VCC (5V)
  - **GND**: Conectar ao pino GND
  - **Out**: Conectar a um pino digital 
- **Uso**: Detecta presença de animais ou pessoas na fazenda ativando alarmes.

#### 4. Sensor de Luz (LDR)
- **Descrição**: Resistor dependente de luz que mede a intensidade da luz solar.
- **Pinos**:
  - **VCC**: Conectar ao pino VCC (3.3V)
  - **GND**: Conectar ao pino GND
  - **AO**: Conectar a um pino analógico (ex: GPIO 34)
- **Uso**: Ajusta a irrigação automaticamente conforme a luz recebida, diminuindo a quantidade de água em dias mais ensolarados e aumentando em dias nublados.

### Gabarito de cores dos fios

| Função    | Cor do Fio              |
|-----------|--------------------------|
| **VCC**   | Vermelho                 |
| **GND**   | Preto ou Azul            |
| **Echo**  | Amarelo                  |
| **Trig**  | Verde                    |
| **Out**   | Laranja                  |
| **SDA**   | Branco ou Azul Claro     |
| **AO (Analógico)** | Verde Claro ou Azul Claro |
| **DO (Digital)** | Roxo ou Lilás        |
