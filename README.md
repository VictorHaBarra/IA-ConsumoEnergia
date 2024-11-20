# Projeto de Monitoramento de Consumo Energético com IoT e Node-RED

Este projeto demonstra como monitorar o consumo energético de dispositivos em uma casa utilizando um microcontrolador ESP32, MQTT, Node-RED e um dashboard para visualizar alertas de picos de consumo. O sistema é capaz de detectar quando o consumo de energia ultrapassa um limite predefinido e gerar um alerta visual no dashboard.

## Visão Geral

O sistema é composto pelos seguintes elementos:

- **ESP32**: Responsável por coletar os dados de consumo e publicá-los via MQTT.
- **MQTT**: Protocolo de comunicação utilizado para enviar dados de consumo entre o ESP32 e o Node-RED.
- **Node-RED**: Plataforma de automação que gerencia a lógica de processamento e exibe os alertas de consumo no dashboard.
- **Wokwi**: Ferramenta de simulação para testar o código do ESP32 antes da implementação real.

## Tecnologias Utilizadas

- **ESP32**: Microcontrolador para a coleta e transmissão de dados de consumo.
- **MQTT**: Protocolo de mensagens utilizado para enviar e receber dados entre o ESP32 e o Node-RED.
- **Node-RED**: Plataforma para criar fluxos de automação e integração de dispositivos IoT.
- **Wokwi**: Simulador de circuitos para testar o código do ESP32 sem a necessidade de hardware físico.

## Estrutura do Projeto

1. **Código do ESP32**: Código escrito em C++ para monitorar e enviar dados de consumo via MQTT.
2. **Fluxo do Node-RED**: Fluxo para receber os dados via MQTT, processar e exibir alertas no dashboard.
3. **Configuração do Wokwi**: Diagrama do circuito no Wokwi para simulação do ESP32 e sensores.

## Passo a Passo para Usar o Projeto

### 1. Configuração do Ambiente

#### 1.1. Instalar o Node-RED

Se você ainda não tem o Node-RED instalado, siga os passos abaixo:

- **Node.js**: Certifique-se de ter o [Node.js](https://nodejs.org/) instalado.
- **Instalar Node-RED**:

    ```bash
    npm install -g --unsafe-perm node-red
    ```

- Para iniciar o Node-RED, execute o comando:

    ```bash
    node-red
    ```

    O Node-RED estará disponível em `http://localhost:1880`.

#### 1.2. Configurar o Broker MQTT

Para configurar o broker MQTT, você pode utilizar um broker público como o [HiveMQ](https://www.hivemq.com/), ou configurar seu próprio broker usando Mosquitto ou outros.

- **Broker MQTT Público**: O fluxo foi configurado para usar o broker público `broker.hivemq.com`.
- **Broker Local**: Se você preferir usar um broker local, configure o Node-RED e o ESP32 para apontar para o endereço do seu broker MQTT.

### 2. Código do ESP32

O código do ESP32 é responsável por coletar os dados de consumo e enviá-los via MQTT. O código está disponível no arquivo `esp32_consumo_energia.ino`.

**Instruções de uso**:

1. **Instalar a Biblioteca MQTT**:
   - No Arduino IDE, instale a biblioteca `PubSubClient` para comunicação MQTT.

2. **Configuração do WiFi**:
   - Altere as credenciais WiFi no código (SSID e PASSWORD) para conectar o ESP32 à sua rede.

3. **Configuração MQTT**:
   - Altere o endereço do broker MQTT, caso esteja utilizando um broker diferente.

4. **Conectar o ESP32**:
   - Carregue o código para o seu ESP32 e conecte-o à rede WiFi e ao broker MQTT.

### 3. Fluxo do Node-RED

O fluxo do Node-RED está configurado para receber os dados de consumo via MQTT, processá-los e gerar alertas em um dashboard.

#### 3.1. Importar o Fluxo

1. Abra o Node-RED e no painel de controle, clique no menu (3 linhas no canto superior direito).
2. Selecione **"Importar"** e cole o conteúdo do arquivo `flow.json` no campo de importação.
3. Clique em **"Importar"** para adicionar o fluxo.

#### 3.2. Visualização do Dashboard

O fluxo inclui um nó de **`ui_text`** que exibe os alertas de consumo energético no dashboard do Node-RED. Para visualizar o dashboard:

- Acesse `http://localhost:1880/ui`.
- O alerta será exibido na interface caso o consumo ultrapasse o limite definido (800 kWh, por exemplo).

### 4. Configuração do Wokwi

O Wokwi é utilizado para simular o ESP32, o que permite testar o código antes de carregar no hardware real.

#### 4.1. Importar o Diagrama

1. Vá para [Wokwi](https://wokwi.com/).
2. Crie um novo projeto e importe o diagrama com o ESP32 e os sensores.
3. Importe o código do ESP32 para o Wokwi.
4. Simule o circuito e observe como o código se comporta ao ler o consumo de energia e enviar os dados via MQTT.

#### 4.2. Diagrama do Circuito

O diagrama do circuito pode ser visualizado e editado diretamente no Wokwi. O circuito inclui:

- **ESP32**: Para ler e enviar os dados de consumo via MQTT.
- **Sensor de Consumo (potenciômetro)**: Simula a leitura do consumo energético.
- **LED**: Para indicar o status do sistema (ligado ou desligado).

### 5. Testando o Sistema

Após configurar o ambiente, siga os passos abaixo para testar o sistema:

1. **Simule o Consumo**: No Wokwi, ajuste o valor do potenciômetro para simular o consumo de energia.
2. **Verifique o Alerta**: O Node-RED exibirá um alerta no dashboard sempre que o consumo ultrapassar o limite predefinido.

## Contribuições

Se você quiser contribuir para este projeto, fique à vontade para abrir issues ou enviar pull requests. Ficarei feliz em revisar e integrar melhorias.

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE).
