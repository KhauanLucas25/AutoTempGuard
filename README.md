# AutoTemp Guard

Sistema embarcado introdutório para monitoramento de temperatura do motor e controle simulado da ventoinha.

## Objetivo

Desenvolver uma lógica de proteção que identifica a faixa de temperatura, aciona a ventoinha com histerese e gera alerta em temperatura crítica.

## Tecnologias

- C++ / Arduino
- ATmega328P / Arduino Uno
- Wokwi
- ADC / analogRead
- potenciômetro linear / Beta 3950
- Serial Monitor

## Destaques técnicos

1. Leitura de sensor analógico.
2. Conversão de ADC para temperatura.
3. Máquina de estados simples.
4. Histerese para evitar oscilação no acionamento da ventoinha.
5. Detecção básica de falha de leitura.
6. Diagnóstico por Serial.

## Resultado esperado

Ao aumentar a temperatura no potenciômetro linear:

- abaixo de 90 C: sistema normal;
- a partir de 90 C: ventoinha ligada;
- a partir de 95 C: alerta visual;
- a partir de 105 C: estado crítico + buzzer.

## Aprendizados

O problema foi tratado como uma pequena ECU didática: entrada -> processamento -> decisão -> saída -> diagnóstico.

## Limitação

A simulação representa o princípio da lógica. Um módulo automotivo real exigiria validação elétrica, térmica, EMC/EMI, diagnóstico mais robusto, watchdog, fail-safe, proteção de alimentação e requisitos de qualidade automotiva.
