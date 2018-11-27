# Moving

Controle de movimento do robô que utiliza PWM para controle de aceleração.

## Controles PWM

pwmX movimento para os lados

pwmY movimento para frente e ré

------

pwm +-135 --> parado

------

pwm 55 --> máximo ré e direita

pwm 100 --> mínimo ré e direita

------

pwm 170 --> mínimo frente e esquerda

pwm 205 --> máximo frente e esquerda

## Controles de Movimento

O movimento é dado pelo envio de comandos do ROS no canal movement, interpretado pela função getDirectionFromTopic. Este possui a base:

p: Parado;
w: Frente;
s: Ré;
d: Direita;
a: Esquerda;

Cada troca de estágio é executada independente com velocidade estimada pelo PWM já citado em dois canais, X e Y.

## Odômetro

O cálculo do odômetro é zerado em cada troca de estágio, assim, se é dado o comando de movimento para frente, o contador do odômetro inicia em zero, quando posto em neutro (parado), o contador volta para zero.

A ideia é manter o controle de movimento por estágios nos arduinos para então manter o controle geral do odômetro no ROS.

## ROS

O ROS utiliza o canal left_sensor para captura dos dados da roda esquerda.

Esse valor é zerado no arduino a cada troca de comando, como citado acima, o código do ROS que  recebe estes valores mantêm um contador geral para tomada de decisão e avaliação de LOG de execução.
