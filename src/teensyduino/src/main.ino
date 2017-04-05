#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h>
#include <std_msgs/UInt16.h>

#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
//#define USE_USBCON

#include <Encoder.h>
#define MOTOR_ENCODER_A 12 // front_A
#define MOTOR_ENCODER_B 11 // front_B
#define ENCODER_OPTIMIZE_INTERRUPTS

char g_buffer[50];

ros::NodeHandle  nh;

sensor_msgs::Range range_msg;
Servo servo;
Encoder motor_encoder(MOTOR_ENCODER_A,MOTOR_ENCODER_B);

// std_msgs::String msg;
// std::stringstream ss;

ros::Publisher pub_range( "/boxRange", &range_msg);

int pingPin = 7;
int inPin = 23;//8;
int ledPin = 22;//13;
long range_time;
char frameid[] = "/boxRange";

void servoCallback( const std_msgs::UInt16& cmd_msg){
  servo.write(cmd_msg.data); //set servo angle, should be from 0-180
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led
}

ros::Subscriber<std_msgs::UInt16> sub_servo("servo_control", servoCallback);

void setup() {
  nh.initNode();
  nh.advertise(pub_range);
  nh.subscribe(sub_servo);

  servo.attach(9); //attach it to pin 9
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.1;  // fake
  range_msg.min_range = 0.0;
  range_msg.max_range = 6.47;
}

void loop()
{
  if ( millis() >= range_time ){
      int r =0;
      range_msg.range = getRange() / 100;
      range_msg.header.stamp = nh.now();
      pub_range.publish(&range_msg);
      range_time =  millis() + 50;
      Encoder_print();
    }
    nh.spinOnce();
}

long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29.1 / 2;
}

float getRange()
{

    // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);

  // convert the time into a distance
  return microsecondsToCentimeters(duration);
}

void Encoder_print()
{
  sprintf(g_buffer, "Encoder: %1d",motor_encoder.read());
  nh.loginfo(g_buffer);

}
