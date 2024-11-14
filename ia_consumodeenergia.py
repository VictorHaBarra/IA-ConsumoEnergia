import streamlit as st
import pandas as pd
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt

# Título da página
st.title('Previsão de Consumo de Energia')

# Sidebar para upload de arquivo CSV
st.sidebar.header('Carregar Dataset')
uploaded_file = st.sidebar.file_uploader("Escolha um arquivo CSV", type=['csv'])

if uploaded_file is not None:
    # Carregar o CSV e combinar as colunas de data e hora
    df = pd.read_csv(uploaded_file)
    df['Timestamp'] = pd.to_datetime(df['TxnDate'] + ' ' + df['TxnTime'])
    df.set_index('Timestamp', inplace=True)

    # Criar novas features baseadas no tempo
    df['Hour'] = df.index.hour
    df['DayOfWeek'] = df.index.dayofweek
    df['Month'] = df.index.month

    # Definir o consumo futuro para prever (exemplo: 1 hora à frente)
    df['Future_Consumption'] = df['Consumption'].shift(-1)

    # Remover a última linha (sem valor para previsão)
    df = df.dropna()

    # Features (X) e target (y)
    X = df[['Hour', 'DayOfWeek', 'Month', 'Consumption']]
    y = df['Future_Consumption']

    # Dividir os dados em treinamento e teste
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    # Criar e treinar o modelo
    model = RandomForestRegressor(n_estimators=100, random_state=42)
    model.fit(X_train, y_train)

    # Previsões
    y_pred = model.predict(X_test)

    # Avaliar o modelo
    mse = mean_squared_error(y_test, y_pred)
    st.write(f'Mean Squared Error: {mse:.2f}')

    # Exibir gráfico comparando consumo real e previsto
    st.subheader('Gráfico de Comparação entre Consumo Real e Previsto')

    plt.figure(figsize=(10, 6))
    plt.plot(y_test.values, label='Consumo Real')
    plt.plot(y_pred, label='Consumo Previsto', linestyle='--')
    plt.legend()
    plt.title('Comparação entre Consumo Real e Previsto')
    plt.xlabel('Índice')
    plt.ylabel('Consumo (KWh)')
    st.pyplot()  # Exibe o gráfico no Streamlit

    # Slider para ajustar o limiar de picos (em múltiplos de desvios padrão)
    st.sidebar.subheader('Ajustar Limiar de Pico')
    multiplier = st.sidebar.slider('Multiplicador de Desvio Padrão', 1, 5, 2)

    # Calcular o limiar de pico com base no multiplicador
    threshold = y_pred.mean() + multiplier * y_pred.std()  # Limite ajustável
    alerts = y_pred > threshold

    st.subheader(f'Alertas de Pico de Consumo (Multiplicador: {multiplier}x)')

    # Exibir alertas de forma interativa
    if alerts.any():
        for i, alert in enumerate(alerts):
            if alert:
                st.markdown(f"🚨 **Pico detectado em:** {X_test.index[i].strftime('%A, %d de %B de %Y às %H:%M:%S')}")
                st.markdown(f"🔴 **Consumo estimado:** {y_pred[i]:.2f} KWh")
                st.markdown("💡 **Dica:** Para evitar picos como esse, tente usar aparelhos de alto consumo em horários fora do pico.")
                st.markdown("-" * 50)
    else:
        st.write("✅ Nenhum pico detectado. Continue monitorando seu consumo de energia.")
else:
    st.write("Carregue um arquivo CSV para começar.")
