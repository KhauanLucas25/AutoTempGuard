// AutoTemp Guard - monitoramento de temperatura do motor (simulacao Wokwi)

// Mapeamento dos pinos de acordo com a sua montagem
const int PINO_VENTOINHA = 9; // LED Branco representa a Ventoinha
const int PINO_VERMELHO  = 6;
const int PINO_AMARELO   = 5;
const int PINO_VERDE     = 3;
const int PINO_BUZZER    = 8;
const int PINO_NTC       = A0;

// Constante padrão do termístor no Wokwi
const float BETA = 3950;

// Variável para guardar o estado da ventoinha (histerese)
bool estadoVentoinha = false; 

void setup() {
  pinMode(PINO_VENTOINHA, OUTPUT);
  pinMode(PINO_VERMELHO, OUTPUT);
  pinMode(PINO_AMARELO, OUTPUT);
  pinMode(PINO_VERDE, OUTPUT);
  pinMode(PINO_BUZZER, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Sistema de Monitorizacao Iniciado.");
}

void loop() {
  int valorADC = analogRead(PINO_NTC);

  // REGRA: Leitura ADC inválida -> FALHA SENSOR (LED Vermelho + Buzzer)
  if (valorADC <= 0 || valorADC >= 1023) {
    desligarTodosLEDs();
    digitalWrite(PINO_VERMELHO, HIGH);
    tone(PINO_BUZZER, 1000);
    Serial.println("Estado: FALHA SENSOR (Leitura invalida)");
    delay(1000);
    return; // Para o código aqui até o sensor voltar
  }

  // Converter a leitura analógica para Graus Celsius
  float temperatura = 1 / (log(1 / (1023.0 / valorADC - 1)) / BETA + 1.0 / 298.15) - 273.15;
  int tempC = round(temperatura); // Arredondar para facilitar as regras

  // Imprimir no Monitor Serial
  Serial.print("Temperatura: ");
  Serial.print(tempC);
  Serial.print(" C | ");

  // Desligar saídas antes de aplicar as novas regras
  desligarTodosLEDs();
  noTone(PINO_BUZZER);

  // Lógica de controlo da Ventoinha (Liga aos 90C, Desliga aos 85C)
  if (tempC >= 90) {
    estadoVentoinha = true;
  } else if (tempC <= 85) {
    estadoVentoinha = false;
  }

  // Ligar fisicamente a ventoinha (LED Branco) se o estado for verdadeiro
  if (estadoVentoinha) {
    digitalWrite(PINO_VENTOINHA, HIGH);
  }

  // --- APLICAÇÃO DAS REGRAS DO ESTADO ---

  if (tempC >= 105) {
    // REGRA: 105 C -> LED vermelho + buzzer; estado CRITICO
    digitalWrite(PINO_VERMELHO, HIGH);
    tone(PINO_BUZZER, 1000);
    Serial.println("Estado: CRITICO");
  } 
  else if (tempC >= 95 && tempC <= 104) {
    // REGRA: 95 C a 104 C -> LED amarelo + vermelho; estado ATENCAO
    digitalWrite(PINO_AMARELO, HIGH);
    digitalWrite(PINO_VERMELHO, HIGH);
    Serial.println("Estado: ATENCAO");
  } 
  else if (tempC >= 90 && tempC <= 94) {
    // REGRA: 90 C a 94 C -> Ventoinha ON; LED amarelo; estado VENTOINHA ON
    digitalWrite(PINO_AMARELO, HIGH);
    Serial.println("Estado: VENTOINHA ON");
  } 
  else {
    // REGRA: Abaixo de 89 C -> LED verde ligado; estado NORMAL
    digitalWrite(PINO_VERDE, HIGH);
    if (!estadoVentoinha) {
      Serial.println("Estado: NORMAL");
    } else {
      Serial.println("Estado: RESFRIANDO (Ventoinha ainda ON, aguardando 85 C)");
    }
  }

  delay(1000); // Aguarda 1 segundo para a próxima leitura
}

// Função auxiliar para limpar os LEDs
void desligarTodosLEDs() {
  digitalWrite(PINO_VERMELHO, LOW);
  digitalWrite(PINO_AMARELO, LOW);
  digitalWrite(PINO_VERDE, LOW);
  // A ventoinha é gerida pela sua própria lógica de histerese
}