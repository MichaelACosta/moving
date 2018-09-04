const int pwmY = 5;
const int pwmX = 6;
char control;

void setup() {
  pinMode(pwmY, OUTPUT);
  pinMode(pwmX, OUTPUT);
  analogWrite(pwmY, 135);
  analogWrite(pwmX, 135);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    control = Serial.read();

    switch (control) {
      case 'd':
        analogWrite(pwmX, 80);
        break;
      case 'a':
        analogWrite(pwmX, 190);
        break;
      case 'w':
        analogWrite(pwmY, 190);
        break;
      case 's':
        analogWrite(pwmY, 80);
        break;
      default:
        analogWrite(pwmY, 135);
        analogWrite(pwmX, 135);
        break;
    }
    delay(1000);
  }
}
