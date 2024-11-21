#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

// Configurações de WiFi
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";  // Substitua pela sua senha

// Configurações de MQTT
const char *BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char *ID_MQTT = "esp32_mqtt";
const char *TOPIC_PUBLISH_ALERT = "fiap/iot/alert";
const char *TOPIC_PUBLISH_CONSUMO = "fiap/iot/consumo";

// Configurações de Hardware
#define PIN_LED 15
#define PUBLISH_DELAY 2000  // Intervalo de publicação em milissegundos
#define CONSUMO_PICO 1.5    // Defina o limite de pico em kWh

// Configurações de Conversão
#define MAX_POTENCIA_W 2000  // Potência máxima em Watts simulada

unsigned long publishUpdate = 0;  // Variável para controlar o tempo de publicação
float totalEnergy = 0.0;          // Energia acumulada em kWh
float lastPower = 0.0;            // Potência da última leitura

WiFiClient espClient;
PubSubClient MQTT(espClient);

// Protótipos de funções
void initWiFi();
void initMQTT();
void checkWiFIAndMQTT();
void reconnectWiFi();
void reconnectMQTT();

void initWiFi() {
  Serial.print("Conectando com a rede: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso: ");
  Serial.println(SSID);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
}

void checkWiFIAndMQTT() {
  if (WiFi.status() != WL_CONNECTED) reconnectWiFi();
  if (!MQTT.connected()) reconnectMQTT();
}

void reconnectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Wifi conectado com sucesso: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Tentando conectar com o Broker MQTT: ");
    Serial.println(BROKER_MQTT);

    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao broker MQTT!");
    } else {
      Serial.println("Falha na conexão com MQTT. Tentando novamente em 2 segundos.");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  initWiFi();
  initMQTT();

  // Inicializa a semente para valores aleatórios
  randomSeed(analogRead(0));
}

void loop() {
  checkWiFIAndMQTT();
  MQTT.loop();

  // Simula leitura de potência em Watts (valores aleatórios)
  float power = random(100, 2000);  // Potência simulada em Watts

  // Cálculo de energia acumulada (kWh)
  float energyIncrement = (power * (PUBLISH_DELAY / 3600000.0)) / 1000.0;  // Incremento em kWh
  totalEnergy += energyIncrement;

  // Exibição no console
  Serial.printf("Potência atual: %.2f W\n", power);
  Serial.printf("Consumo total acumulado: %.4f kWh\n", totalEnergy);

  // Verificação de pico de consumo
  if (power > (CONSUMO_PICO * 1000) && lastPower <= (CONSUMO_PICO * 1000)) {
    Serial.println("Pico de consumo detectado!");
    digitalWrite(PIN_LED, HIGH);  // Acende o LED para indicar o pico

    // Publica alerta no MQTT
    StaticJsonDocument<200> doc;
    doc["alert"] = "Pico de consumo detectado!";
    char buffer[200];
    serializeJson(doc, buffer);
    MQTT.publish(TOPIC_PUBLISH_ALERT, buffer);
  }

  // Se o consumo cair abaixo do limiar de pico, apaga o LED
  if (power <= (CONSUMO_PICO * 1000)) {
    digitalWrite(PIN_LED, LOW);
  }

  // Publica os dados de consumo a cada intervalo
  if ((millis() - publishUpdate) >= PUBLISH_DELAY) {
    publishUpdate = millis();

    StaticJsonDocument<200> doc;
    doc["power"] = power;         // Potência atual (W)
    doc["totalEnergy"] = totalEnergy;  // Energia acumulada (kWh)
    char buffer[200];
    serializeJson(doc, buffer);
    MQTT.publish(TOPIC_PUBLISH_CONSUMO, buffer);
    Serial.println("Dados publicados no MQTT:");
    Serial.println(buffer);
  }

  lastPower = power;  // Atualiza a última potência lida
}
