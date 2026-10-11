# AutoTemp Guard

**Descrição:** Desenvolvi um monitor de temperatura automotiva em C++ para Arduino Uno, simulando no Wokwi a leitura de um sensor NTC, controle de ventoinha com histerese, alarmes e diagnostico via Serial Monitor.[cite: 10]

## 1. Qual problema o sistema resolve?
O AutoTemp Guard atua como um pequeno módulo embarcado para monitorar a temperatura de um motor simulado[cite: 1, 2]. O objetivo principal é detectar um aquecimento excessivo e acionar uma ventoinha de arrefecimento antes que o sistema atinja uma condição crítica, mantendo sempre o comportamento estável[cite: 2].

## 2. Qual hardware foi simulado?
Todo o circuito foi montado no simulador online Wokwi, utilizando a seguinte arquitetura de hardware[cite: 3]:
* **Microcontrolador:** Arduino Uno (ATmega328P)[cite: 2, 3].
* **Entrada:** Sensor analógico de temperatura NTC[cite: 3].
* **Saídas Visuais e Sonoras:** 4 LEDs (Verde, Amarelo, Vermelho e Branco) com resistores de 220 ohm para limitação de corrente, e 1 buzzer[cite: 3]. (O LED branco atua como simulador do comando da ventoinha)[cite: 4].

## 3. Como o algoritmo toma a decisão?
O firmware separa as responsabilidades de leitura, processamento e atuação[cite: 7]:
* **Leitura e Conversão:** A função lê o valor do pino analógico A0 e utiliza a equação do termistor (Beta 3950) para transformar a leitura ADC num valor em graus Celsius[cite: 6, 7].
* **Histerese:** Para evitar que a ventoinha fique a ligar e desligar repetidamente no limite de temperatura, o algoritmo implementa histerese[cite: 7]. A ventoinha liga aos 90 ºC, mas só desliga quando a temperatura desce para os 85 ºC[cite: 6, 7].
* **Máquina de Estados:** O sistema classifica a temperatura em estados (NORMAL, VENTOINHA ON, ATENÇÃO, CRÍTICO e FALHA SENSOR), decidindo quais indicadores ativar com base neste estado[cite: 7].

## 4. Como testar e reproduzir o comportamento?
1. Abra o projeto no Wokwi utilizando o ficheiro `diagram.json` incluído neste repositório[cite: 4].
2. Inicie a simulação e abra o **Serial Monitor** (configurado para a taxa de 115200 baud) para acompanhar os dados de telemetria e diagnósticos em tempo real[cite: 4, 9].
3. Clique no sensor NTC no diagrama e deslize a barra para alterar a temperatura simulada[cite: 8].
4. Verifique os limites de acionamento:
   * **90 ºC:** A ventoinha liga (LED Amarelo + LED Branco)[cite: 8].
   * **95 ºC:** Estado de Atenção (LED Amarelo + LED Vermelho)[cite: 8].
   * **105 ºC:** Estado Crítico (LED Vermelho + Buzzer)[cite: 8].
   * **Queda para 85 ºC:** A ventoinha desliga e retorna ao estado Normal[cite: 8].

## 5. Quais são as limitações e próximos passos?
* **Limitações:** Este é um projeto puramente didático[cite: 1]. Os limiares de temperatura e a arquitetura elétrica não podem ser utilizados diretamente num veículo real sem engenharia rigorosa, testes automotivos e proteção elétrica adequada[cite: 1]. O hardware simulado utiliza um LED no pino D9 para representar a ventoinha, enquanto num cenário real seria necessário um MOSFET, transístor ou relé para suportar a carga[cite: 5].
* **Próximos Passos (Evolução):** 
  * Implementar sinal **PWM** com `analogWrite()` no pino D9 para variar a velocidade da ventoinha[cite: 5, 11].
  * Substituir o LED branco por um **módulo relé** no simulador[cite: 11].
  * Adicionar um display **LCD 16x2 ou OLED** para exibir informações locais[cite: 11].
  * Criar Códigos de Falha de Diagnóstico (**DTC**) e preparar o sistema para uma futura integração com o protocolo **CAN**[cite: 11].