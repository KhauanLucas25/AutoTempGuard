# AutoTemp Guard - Monitoramento de Temperatura Automotiva

Projeto introdutório de sistemas embarcados em C/C++ usando Arduino Uno e Wokwi.

## Problema

Monitorar a temperatura do motor e acionar a ventoinha antes de uma condição crítica, além de gerar alertas visuais/sonoros.

## Solução

- potenciômetro linear no A0;
- LED verde = temperatura normal;
- LED amarelo = ventoinha acionada;
- LED vermelho = alerta;
- buzzer = condição crítica ou falha do sensor;
- LED branco = sinal de comando da ventoinha;
- Serial Monitor = diagnóstico.

## Limiares da simulacao

- Ventoinha liga em >= 90 C;
- Ventoinha desliga em <= 85 C;
- Alerta em >= 95 C;
- Critico em >= 105 C.

Os limites são didáticos para a simulação e não devem ser usados diretamente em um veículo real.

## Arquivos

- `src/auto_temp_guard.ino` - firmware em C++;
- `diagram.json` - circuito do Wokwi;
- `wokwi.toml` - configuração opcional para Wokwi for VS Code;
- `README.md` - documentação.

## Como executar no Wokwi

1. Crie um projeto novo de Arduino Uno no Wokwi.
2. Cole o conteúdo de `diagram.json` no arquivo de diagrama.
3. Cole `src/auto_temp_guard.ino` no editor de código.
4. Inicie a simulação.
5. Clique no sensor NTC e altere a temperatura.
6. Observe os LEDs, o buzzer e o Serial Monitor.

## Portfólio

O projeto demonstra leitura de sensor analógico, conversão matemática, máquina de estados simples, histerese, acionamento de saídas, diagnóstico e testes por cenários.
