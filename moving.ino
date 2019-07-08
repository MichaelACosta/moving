#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>

#define pwmPinY 5
#define pwmPinX 6
#define stopped 135
#define odometryPinRight 2
#define odometryPinLeft 3

unsigned int right_counter = 0;
unsigned int left_counter = 0;
unsigned int sensor_counter_right = 0;
unsigned int sensor_counter_left = 0;

void clearCounter(const std_msgs::Bool &shouldClear)
{
  if (shouldClear.data)
  {
    right_counter = 0;
    left_counter = 0;
  }
}

void getDirectionFromTopicX(const std_msgs::Int16 &pwm)
{
  moveX(pwm.data);
}

void getDirectionFromTopicY(const std_msgs::Int16 &pwm)
{
  moveY(pwm.data);
}

ros::NodeHandle node;
std_msgs::Int16 value_odometry_right;
std_msgs::Int16 value_odometry_left;
ros::Subscriber<std_msgs::Int16> movement_x("channel_x", &getDirectionFromTopicX);
ros::Subscriber<std_msgs::Int16> movement_y("channel_y", &getDirectionFromTopicY);
ros::Publisher odometry_pub_right("right_sensor", &value_odometry_right);
ros::Publisher odometry_pub_left("left_sensor", &value_odometry_left);
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
  node.advertise(odometry_pub_right);
  node.advertise(odometry_pub_left);
  node.subscribe(clear_counter);
  attachInterrupt(digitalPinToInterrupt(odometryPinRight), counterRight, RISING);
  attachInterrupt(digitalPinToInterrupt(odometryPinLeft), counterLeft, RISING);
}

void loop()
{
  if ((right_counter % 10) == 0)
  {
    value_odometry_right.data = right_counter;
    odometry_pub_right.publish(&value_odometry_right);
  }
  if ((left_counter % 10) == 0)
  {
    value_odometry_left.data = left_counter;
    odometry_pub_left.publish(&value_odometry_left);
  }
  node.spinOnce();
}

void counterRight()
{
  sensor_counter_right++;
  if (sensor_counter_right >= 4)
  {
    sensor_counter_right = 0;
    right_counter++;
  }
}

void counterLeft()
{
  sensor_counter_left++;
  if (sensor_counter_left >= 4)
  {
    sensor_counter_left = 0;
    left_counter++;
  }
}

void moveX(int pwm)
{
  analogWrite(pwmPinX, pwm);
}

void moveY(int pwm)
{
  analogWrite(pwmPinY, pwm);
}
