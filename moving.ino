#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

#define pwmPinY 5
#define pwmPinX 6
#define stopped 135
#define odometryPinRight 2
#define odometryPinLeft 3

unsigned int right_counter = 0;
unsigned int left_counter = 0;
unsigned int pulse = 0;

void clearCounter(const std_msgs::Bool &shouldClear)
{
  if (shouldClear.data)
  {
    right_counter = 0;
    left_counter = 0;
  }
}

void getDirectionFromTopicX(const std_msgs::String &pwm)
{
  char value[] = strtok(pwm.data ' ');
  moveX(atoi(value[0]));
  pulse = atoi(value[1]);
}

void getDirectionFromTopicY(const std_msgs::String &pwm)
{
  char value[] = strtok(pwm.data ' ');
  moveY(atoi(value[0]));
  pulse = atoi(value[1]);
}

ros::NodeHandle node;
ros::Subscriber<std_msgs::String> movement_x("channel_x", &getDirectionFromTopicX);
ros::Subscriber<std_msgs::String> movement_y("channel_y", &getDirectionFromTopicY);
ros::Subscriber<std_msgs::Bool> clear_counter("pattern", &clearCounter);

void setup()
{
  Serial.begin(9600);
  pinMode(odometryPinRight, INPUT);
  pinMode(odometryPinLeft, INPUT);
  pinMode(pwmPinY, OUTPUT);
  pinMode(pwmPinX, OUTPUT);
  analogWrite(pwmPinY, stopped);
  analogWrite(pwmPinX, stopped);
  node.initNode();
  node.subscribe(movement_x);
  node.subscribe(movement_y);
  node.subscribe(clear_counter);
  attachInterrupt(digitalPinToInterrupt(odometryPinRight), counterRight, RISING);
  attachInterrupt(digitalPinToInterrupt(odometryPinLeft), counterLeft, RISING);
}

void loop()
{
  if ((right_counter >= pulse) || (left_counter >= pulse))
  {
    moveX(stopped);
    moveY(stopped);
  }
  node.spinOnce();
}

void counterRight()
{
  right_counter++;
}

void counterLeft()
{
  left_counter++;
}

void moveX(int pwm)
{
  analogWrite(pwmPinX, pwm);
}

void moveY(int pwm)
{
  analogWrite(pwmPinY, pwm);
}
