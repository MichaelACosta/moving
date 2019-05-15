#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>

#define pwmPinY 5
#define pwmPinX 6
#define stopped 135
#define odometryPin 13

unsigned int left_counter = 0;
bool odometry_state = false;

void getDirectionFromTopicX(const std_msgs::Int16 &pwm) {
  moveX(pwm.data);
}

void getDirectionFromTopicY(const std_msgs::Int16 &pwm) {
  moveY(pwm.data);
}

void clearCounter(const std_msgs::Bool &shouldClear) {
  if (shouldClear.data)
    left_counter = 0;
}

ros::NodeHandle  node;
std_msgs::Int16 value_odometry;
ros::Publisher odometry_pub("left_sensor", &value_odometry);
ros::Subscriber<std_msgs::Int16> movement_x("channel_x", &getDirectionFromTopicX);
ros::Subscriber<std_msgs::Int16> movement_y("channel_y", &getDirectionFromTopicY);
ros::Subscriber<std_msgs::Bool> clear_counter("pattern", &clearCounter);

void setup() {
  Serial.begin(9600);
  pinMode(odometryPin, INPUT);
  pinMode(pwmPinY, OUTPUT);
  pinMode(pwmPinX, OUTPUT);
  analogWrite(pwmPinY, stopped);
  analogWrite(pwmPinX, stopped);
  node.initNode();
  node.advertise(odometry_pub);
  node.subscribe(movement_x);
  node.subscribe(movement_y);
  node.subscribe(clear_counter);
}

void loop() {
  int odometry_sensor = digitalRead(odometryPin);
  if (odometry_sensor == 1 && !odometry_state) {
    odometry_state = true;
    value_odometry.data = left_counter++;
    odometry_pub.publish(&value_odometry);
  } else if (odometry_sensor == 0 && odometry_state) {
    odometry_state = false;
  }
  node.spinOnce();
}

void moveX(int pwm) {
  analogWrite(pwmPinX, pwm);
}

void moveY(int pwm) {
  analogWrite(pwmPinY, pwm);
}
