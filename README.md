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



