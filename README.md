# Projeto IoT: Monitoramento e Controle de Consumo com ESP32 e MQTT

## 📋 Sobre o Projeto

Este projeto integra dois dispositivos IoT (um ESP32 com potenciômetro e buzzer) para monitorar o consumo de energia simulado e enviar alertas via MQTT. Os dados são enviados a um broker MQTT e integrados ao Node-RED, onde são exibidos em gráficos e controlados em tempo real.

### 🛠 Funcionalidades
- Monitoramento do consumo de energia (kWh) e envio de alertas.
- Integração com Node-RED para visualização e controle via dashboard.
- Configuração de limites para alertar sobre consumo excessivo.

---

## 🖼 Arquitetura do Sistema

A solução é composta pelos seguintes elementos:
1. **Hardware**:
   - ESP32 (controlador principal).
   - Potenciômetro (simulador de consumo).
   - Buzzer (alerta sonoro).
2. **Software**:
   - Código em Arduino C++ rodando no ESP32.
   - Dashboard e fluxo de controle no Node-RED.
   - Comunicação via protocolo MQTT.

### Diagrama de Montagem

(Insira aqui a imagem do diagrama de montagem)

### Fluxo de Dados

1. O ESP32 lê dados do potenciômetro
2. Os dados são publicados em tópicos MQTT:
   - `esp32/consumo`: Consumo de energia (kWh).
3. O Node-RED recebe os dados e exibe gráficos em um dashboard.
4. O buzzer é ativado quando o consumo excede o limite.

---

## 🚀 Como Executar o Projeto

### 1. Pré-requisitos
- Hardware:
  - ESP32, potenciômetro, buzzer.
- Software:
  - [Arduino IDE](https://www.arduino.cc/en/software) ou [PlatformIO](https://platformio.org/).
  - Node-RED instalado no computador.
  - Broker MQTT (pode ser o [HiveMQ](https://www.hivemq.com/public-mqtt-broker/) ou local).

### 2. Configuração do ESP32
1. Baixe ou clone este repositório:
   ```bash
   git clone [https://github.com/seu-repositorio/projeto-iot](https://github.com/VictorHaBarra/IA-ConsumoEnergia).git
   cd IA-ConsumoEnergia


# Previsão de Consumo de Energia

Este projeto utiliza **Machine Learning** para prever o consumo de energia com base em dados históricos. Através de um modelo de **Random Forest Regressor**, o código prevê o consumo de energia em horários futuros e detecta picos de consumo, oferecendo dicas para otimização do uso de energia. A aplicação é interativa e permite que o usuário ajuste parâmetros, como o limite de detecção de picos.

## Funcionalidades

- **Previsão de Consumo**: Utiliza o modelo de machine learning para prever o consumo futuro com base em dados históricos.
- **Detecção de Picos**: Alerta o usuário quando um pico de consumo é detectado com base nas previsões.
- **Ajuste de Picos**: Permite ao usuário ajustar o multiplicador de desvios padrão para modificar o limite de pico de consumo e ver como os alertas mudam.
- **Gráficos Interativos**: Exibe gráficos comparando o consumo real e o previsto, e uma lista de alertas de pico.

## Como Usar

1. **Carregar o Dataset**: Carregue um arquivo CSV contendo dados de consumo de energia. O arquivo deve ter, pelo menos, as colunas `TxnDate`, `TxnTime` e `Consumption`.
2. **Ajustar Parâmetros**: Use o controle deslizante para ajustar o multiplicador de desvios padrão, que determina o limiar para a detecção de picos de consumo.
3. **Visualizar Resultados**: O gráfico será atualizado com as previsões e o consumo real. Os alertas de pico serão exibidos na interface, caso o limite seja ultrapassado.

## Requisitos

Este projeto utiliza as seguintes bibliotecas Python:

- **pandas**: Para manipulação de dados.
- **scikit-learn**: Para o modelo de machine learning.
- **matplotlib**: Para visualização de gráficos.
- **streamlit**: Para a criação da interface web interativa.

Link para o Streamlit
Você também pode acessar a versão do app Streamlit online no seguinte link:

## Streamlit

[https://ia-consumoenergia-any8zsbxyvfxhj5zvjlfwn.streamlit.app/](https://ia-consumoenergia-any8zsbxyvfxhj5zvjlfwn.streamlit.app/)



