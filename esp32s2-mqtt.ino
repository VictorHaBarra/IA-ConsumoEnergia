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

// Configurações de Hardware
#define PIN_POTENTIOMETER 34  // Pino analógico onde o potenciômetro está conectado
#define PIN_LED 15
#define PUBLISH_DELAY 2000
#define CONSUMO_PICO 800  // Defina o valor de pico para disparar o alerta (pode ajustar conforme necessário)

unsigned long publishUpdate = 0;  // Variável para controlar o tempo de publicação
int lastReading = 0;  // Variável para armazenar a última leitura do potenciômetro

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
}

void loop() {
  checkWiFIAndMQTT();
  MQTT.loop();

  int reading = analogRead(PIN_POTENTIOMETER);  // Leitura do potenciômetro

  // Verifique se houve um pico de consumo
  if (reading > CONSUMO_PICO && lastReading <= CONSUMO_PICO) {
    Serial.println("Pico de consumo detectado!");
    digitalWrite(PIN_LED, HIGH);  // Acende o LED para indicar o pico
    // Publica alerta no MQTT
    StaticJsonDocument<200> doc;
    doc["alert"] = "Pico de consumo detectado!";
    char buffer[200];
    serializeJson(doc, buffer);
    MQTT.publish(TOPIC_PUBLISH_ALERT, buffer);
  }

  // Se o valor do potenciômetro cair abaixo do limiar de pico, apaga o LED
  if (reading <= CONSUMO_PICO) {
    digitalWrite(PIN_LED, LOW);
  }

  lastReading = reading;  // Atualiza a última leitura

  if ((millis() - publishUpdate) >= PUBLISH_DELAY) {
    publishUpdate = millis();
    // A cada intervalo, podemos enviar a leitura de consumo também
    StaticJsonDocument<200> doc;
    doc["consumo"] = reading;  // Publica o valor do potenciômetro
    char buffer[200];
    serializeJson(doc, buffer);
    MQTT.publish("fiap/iot/consumo", buffer);
    Serial.println(buffer);
  }
}
