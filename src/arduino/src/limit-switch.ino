#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <ros.h>
#include <std_msgs/UInt16.h>
#include <ros/time.h>
#include <math.h>
#include <std_msgs/String.h>

#define  MOTOR_RATE 10 //hz
unsigned long g_prev_command_time = 0;
unsigned long g_prev_control_time = 0;


//Servo 
#include <Servo.h>
Servo myservo;
#define servo_pin 9

//switch
#define s1 14
#define s2 15
#define s3 16
#define s4 17

//msg objects
std_msgs::UInt16 switch_msg;

ros::NodeHandle nh;
ros::Subscriber<std_msgs::UInt16> servoSub("cmdservo", servoCB);
ros::Publisher switchPub("switch", &switch_msg);

//function prototypes
void servoCB(const std_msgs::UInt16& servo_msg);

void setup()
{
	myservo.attach(servo_pin);
	nh.initNode();

	pinMode(s1, INPUT);
	pinMode(s2, INPUT);
	pinMode(s3, INPUT);
	pinMode(s4, INPUT);

	nh.subscribe(servo_msg);
	nh.advertise(switchPub);
}

void loop()
{

	if((millis() - g_prev_command_time) >= (1000/ MOTOR_RATE))
  	{
      		g_prev_control_time = millis();
  	}

	nh.spinOnce();
  	delay(5);

}	

void servoCB(const std_msgs::UInt16& servo_msg)
{
	int cmVal = toCM(servo_msg.data);
	servo.write(cmVal);
}

void switch_check()
{
	int switchArray[4] = {0,0,0,0};
		
}


