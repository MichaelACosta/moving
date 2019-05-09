#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>

#define pwmPinY 5
#define pwmPinX 6
#define stopped 135
#define odometryPin 13

void getDirectionFromTopicX(const std_msgs::Int16 &pwm) {
  moveX(pwm.data);
}

void getDirectionFromTopicY(const std_msgs::Int16 &pwm) {
  moveY(pwm.data);
}

void getStatusMoviment(const std_msgs::Bool &status) {
  stopCounter(status.data);
}

ros::NodeHandle  node;
std_msgs::Int16 value_odometry;
ros::Publisher odometry_pub("left_sensor", &value_odometry);
ros::Subscriber<std_msgs::Int16> movement_x("channel_x", &getDirectionFromTopicX);
ros::Subscriber<std_msgs::Int16> movement_y("channel_y", &getDirectionFromTopicY);
ros::Subscriber<std_msgs::Bool> status_movement("pattern", &getStatusMoviment);

unsigned int left_counter = 0;
bool odometry_state = false;

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
  node.subscribe(status_movement);
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

vois stopCounter(status) {
  if (status === true) {
    left_counter = 0;
  }
}
