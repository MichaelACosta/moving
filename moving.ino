#define pwmY 5
#define pwmX 6
#define light_port 8

bool light_state = false;
unsigned int left_counter = 0; 

void setup() {
  Serial.begin(9600);

  pinMode(pwmY, OUTPUT);
  pinMode(pwmX, OUTPUT);
  analogWrite(pwmY, 135);
  analogWrite(pwmX, 135);
  
  pinMode(light_port, INPUT);
}

void loop() {
  if (Serial.available() > 0) {
    _move(Serial.read());
  }
  
  int light_sensor = digitalRead(light_port);

  if (light_sensor == 1 && !light_state) {
      light_state = true;
      Serial.println(left_counter++);
    } else if (light_sensor == 0 && light_state) {
      light_state = false;
    }
}

void _move(char control){
  switch (control) {
    case 'd':
      analogWrite(pwmX, 80);
      Serial.println("Right");
      break;
    case 'a':
      analogWrite(pwmX, 190);
      Serial.println("Left");
      break;
    case 'w':
      analogWrite(pwmY, 190);
      analogWrite(pwmX, 145);
      Serial.println("Forward");
      break;
    case 's':
      analogWrite(pwmY, 80);
      Serial.println("Backward");
      break;
     case 'p':
      analogWrite(pwmY, 135);
      analogWrite(pwmX, 135);
      break;
  }
}
