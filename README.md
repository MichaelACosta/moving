# Moving

Controle de movimento do robô que utiliza PWM para controle de aceleração.

## Controles de Movimento

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

## Odômetro

O cálculo do odômetro é zerado em cada troca de estágio, assim, se é dado o comando de movimento para frente, o contador do odômetro inicia em zero, quando posto em neutro (parado), o contador volta para zero.

A ideia é manter o controle de movimento por estágios nos arduinos para então manter o controle geral do odômetro no ROS.
