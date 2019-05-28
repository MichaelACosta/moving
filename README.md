# Moving

Controle de movimento do robô que utiliza PWM para controle de aceleração.

## Controles PWM

pwmX movimento para os lados

pwmY movimento para frente e ré

---

pwm +-135 --> parado

---

pwm 55 --> máximo ré e direita

pwm 100 --> mínimo ré e direita

---

pwm 170 --> mínimo frente e esquerda

pwm 205 --> máximo frente e esquerda

## Controles de Movimento

O movimento é dado pelo envio de comandos do ROS no canal channel_x e channel_y, interpretado pela função getDirectionFromTopicX e getDirectionFromTopicY.
O valor recebido nos canais citados acima são passados para as função moveX e moveY, na qual coloca o valor em suas respectivas portas PWM.
