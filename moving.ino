#include <ros.h>
#include <std_msgs/Int16.h>
#define pwmY 5
#define pwmX 6
#define light_port 12

void getDirectionFromTopicX(const std_msgs::Int16 &pwm) {
  moveX(pwm.data);
}

void getDirectionFromTopicY(const std_msgs::Int16 &pwm) {
  moveY(pwm.data);
}

ros::NodeHandle  node;
std_msgs::Int16 light_msg;
ros::Publisher light_pub("left_sensor", &light_msg);
ros::Subscriber<std_msgs::Int16> movement_x("channel_x", &getDirectionFromTopicX);
ros::Subscriber<std_msgs::Int16> movement_y("channel_y", &getDirectionFromTopicY);
unsigned int left_counter = 0; 
bool light_state = false;

void setup() {
  Serial.begin(9600);
  pinMode(light_port, INPUT);
  pinMode(pwmY, OUTPUT);
  pinMode(pwmX, OUTPUT);
  analogWrite(pwmY, 135);
  analogWrite(pwmX, 135);
  node.initNode();
  node.advertise(light_pub);
  node.subscribe(movement_x);
  node.subscribe(movement_y);
}

void loop() {
  int light_sensor = digitalRead(light_port);
  if (light_sensor == 1 && !light_state) {
    light_state = true;
    light_msg.data = left_counter++;
    light_pub.publish(&light_msg);
  } else if (light_sensor == 0 && light_state) {
    light_state = false;
  }
  node.spinOnce();
}

void moveX(int pwm){
  analogWrite(pwmX, pwm);
}

void moveY(int pwm){
  analogWrite(pwmY, pwm);
}
