# Sistema De Acesso

Projeto de um sistema de uma porta automática usando:

- ESP32
- RFID
- SISTEMA WEB (Back-End: Django[Python], Front-End: BootStrap)
- API(Django Rest Framework [Python]). 
- Protocolo MQTT (Inserido no Sistema Web)

## Objetivo

Automatizar um tranca elétrica desse modelo integrando um microcontrolador a um sistema web que permite gerenciar as pessoas que possui acesso, dias que o acesso a essas pessoas esta liberado, exibir histórico (logs) de acesso e liberar o acesso via sistema(a distância).

Tudo isso inicialmente utilizando uma mescla de protocolos (MQTT e HTTP). Mas futuramente, prentendo aperfeiçoar o sistema utilizando apenas MQTT.


## Etapas

- Criação do Sistema Web [FEITO!]
  - Interface do Sistema [FEITO!]
  - Enviando dados para o microcontrolador via protocolo MQTT (Atualmente utilizando o serviço do www.cloudmqtt.com/ , mas pretendo realizar a criação de um servidor próprio MQTT)[FEITO!]

- Desenvolvimento da API [FEITO!]
- Montagem do sketch do circuito [FEITO!]
- Desenvolvimento do código do microcontrolador [EM DESENVOLVIMENTO!]

## Apresentação


## Observações

Como o projeto ainda está em fase de desenvolvimento e é totalmente desenvolvido por interesse pessoal a fim de aprendizado, é possível que haja erros.





