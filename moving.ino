const int pwmY = 5;
const int pwmX = 6;
char directions = 'p';
char control;

void setup() {
  pinMode(pwmY, OUTPUT);
  pinMode(pwmX, OUTPUT);
  analogWrite(pwmY, 135);
  analogWrite(pwmX, 135);
  Serial.begin(9600);
}

void setDirections() {
    if (control == 'd'){
      directions = 'd';
    }
    else if (control == 'a'){
      directions = 'a';
    }
    else if (control == 'w'){
      directions = 'w';
    }
    else if (control == 's'){
      directions = 's';
    }
    else if (control == 'p'){
      directions = 'p';
    }
}

void moving(){
  switch (directions) {
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
    case 'p':
      analogWrite(pwmY, 135);
      analogWrite(pwmX, 135);
      break;
    default:
      analogWrite(pwmY, 135);
      analogWrite(pwmX, 135);
      break;
  }
}

void loop() {
  if (Serial.available() > 0) {
    control = Serial.read();
  }
  setDirections();
  moving();
}
