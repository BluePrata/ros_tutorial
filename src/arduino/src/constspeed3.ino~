#if (ARDUINO >=100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <ros.h>
#include <ros/time.h>

#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>

#include <math.h>

#define  MOTOR_RATE 10 //hz
unsigned long g_prev_command_time = 0;
unsigned long g_prev_control_time = 0;

//header file for stepper motor
#include <AccelStepper.h>
#define stp 22
#define dir 23
#define MS1 19
#define MS2 20
#define MS3 21
#define EN 18

//stepper object
AccelStepper stepper(4,22,23,19,20);

//store direction and required steps
geometry_msgs::Pose moveArray;

//messages
std_msgs::UInt16 stageMsg;
std_msgs::UInt16 stepMsg;

//stage steps definition
int stage1 = 0;
int stage2 = 200;
int stage3 = 400;

//other variables
int desired_stage; //MotorCb
int current_step = 0;
int current_stage = 0;
int direction = 0;

//function prototypes
void checkStage(int Stage);
void currentStageis(long StepVal);
void MotorCb( const std_msgs::UInt16& motor_msg);



ros::NodeHandle nh;
ros::Publisher motorPub("/motor", &stageMsg);
ros::Subscriber<std_msgs::UInt16> motorSub("cmdmotor", MotorCb);

void setup()
{
  nh.initNode();

  pinMode(13, OUTPUT);

  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(EN, OUTPUT);


  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
  digitalWrite(EN, HIGH);
  
  nh.subscribe(motorSub);
  nh.advertise(motorPub);

  digitalWrite(EN, LOW);
}


void loop()
{

  if((millis() - g_prev_command_time) >= (1000/ MOTOR_RATE))
  {
      //stepper.run();
      digitalWrite(13, HIGH);
      stepMsg.data = stepper.currentPosition();
      currentStageis(stepMsg.data);

      //stageMsg.data = current_stage;
      //motorPub.publish(&stageMsg);

      g_prev_control_time = millis();
  }

  nh.spinOnce();
  delay(5);
}


//callback function prototypes
void MotorCb( const std_msgs::UInt16& motor_msg)
{
    digitalWrite(13, LOW);

    desired_stage = motor_msg.data;
   	checkStage(desired_stage);


   	if(moveArray.position.x == 0)
   	{
     		digitalWrite(dir, 0);
   	}
   	if(moveArray.position.x == 1)
   	{
   	  	digitalWrite(dir,1);
   	}
   	for(int x = 0; x < moveArray.position.y; x ++)
   	{
      		digitalWrite(stp, 1);
      		delay(1);
      		digitalWrite(stp, 0);
      		delay(1);
    	}
}


void checkStage(int Stage)
{
	if (Stage < current_stage)
	{
		direction = 0;
	}
	else
	{
		direction = 1;
	}
	int diff = abs(Stage - current_stage);
	moveArray.position.x=direction;
	moveArray.position.y=diff*0;
}


void currentStageis(long StepVal)
{
	current_step = StepVal;

	if (current_step <0)
	{
        	current_step = 0;
	}
   	if (current_step == 0)
   	{
      		current_stage = 1;
   	}
   	if (current_step == 200)
   	{
      		current_stage = 2;
   	}
   	if (current_step == 400)
   	{
      		current_stage = 3;
   	}
	else 
	{
		current_stage = 999;
        }
	stageMsg.data = current_step;
	motorPub.publish(&stageMsg);

}
