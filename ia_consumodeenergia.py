import pandas as pd
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt

# Carregar o CSV e combinar as colunas de data e hora
df = pd.read_csv('dataset.csv')
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
print(f'Mean Squared Error: {mse}')

# Exibir um gráfico comparando consumo real e previsto
plt.plot(y_test.values, label='Consumo Real')
plt.plot(y_pred, label='Consumo Previsto', linestyle='--')
plt.legend()
plt.title('Comparação entre Consumo Real e Previsto')
plt.xlabel('Índice')
plt.ylabel('Consumo (KWh)')
plt.show()

# Detectar picos (por exemplo, se o consumo previsto ultrapassar um limite)
threshold = y_pred.mean() + 2 * y_pred.std()  # Limite de 2 desvios padrão
alerts = y_pred > threshold

# Exibir alertas de forma mais amigável e lúdica
alert_indexes = X_test.index[alerts]
print("🚨 ALERTA DE PICO DE CONSUMO 🚨")

if len(alert_indexes) > 0:
    for i, alert_time in enumerate(alert_indexes):
        print(f"⚡ Pico detectado em: {alert_time.strftime('%A, %d de %B de %Y às %H:%M:%S')}")
        print(f"🔴 Consumo estimado: {y_pred[alerts][i]:.2f} KWh")  # Corrigido para usar o índice correto
        print(f"💡 Dica: Para evitar picos como esse, tente usar aparelhos de alto consumo em horários fora do pico, como à noite ou pela manhã.")
        print("-" * 50)  # Separador visual entre alertas
else:
    print("✅ Nenhum pico detectado. Continue monitorando seu consumo de energia.")