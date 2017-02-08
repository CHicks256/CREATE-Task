#pragma config(Sensor, in5,    PotPillar,      sensorPotentiometer)
#pragma config(Sensor, in6,    PotPin1,        sensorPotentiometer)
#pragma config(Sensor, in7,    PotPin2,        sensorPotentiometer)
#pragma config(Sensor, in8,    gyroauto,       sensorGyro)
#pragma config(Sensor, dgtl1,  AutoButton1,    sensorTouch)
#pragma config(Sensor, dgtl2,  AutoButton2,    sensorTouch)
#pragma config(Sensor, dgtl3,  ArmButton,      sensorTouch)
#pragma config(Sensor, dgtl4,  Jump1,          sensorDigitalIn)
#pragma config(Motor,  port1,           PincerL,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftfront,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightfront,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftrear,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightrear,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           PillarBottomL, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           PillarBottomR, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           PillarTopL,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           PillarTopR,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          PincerR,       tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
//Variables that are going to be used throughout program
int PillT = 100;
int PillD = -100;
//int degree = 0;
//int error = 100;
int PinOpen = 100;
int PinClose = -100;
// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
	SensorType[in8] = sensorNone;
	wait1Msec(1000);
	//Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
	SensorType[in8] = gyroauto;
	wait1Msec(2000);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()   		// TURN LEFT DAMNIT
{
clearTimer(T1);
while(time1[T1] < 1000)
{
	motor[port2] = 100;
	motor[port3] = 100;
	motor[port4] = 100;
	motor[port5] = 100;
}
motor[port2] = 0;
	motor[port3] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	motor[PincerL] = 100;
	motor[PincerR] = 100;
	wait(2);
	motor[port2] = -50;
	motor[port3] = -50;
	motor[port4] = 50;
	motor[port5] = 50;
	wait(.75);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{

		//X-drive code: Controls: Channel 3 is forward and backward,
		//Channel 4: strafes left and right, Channel 1: Turn left/right
		motor[leftfront] = vexRT[Ch3] + vexRT[Ch1] + vexRT[Ch4];
		motor[rightfront] = vexRT[Ch3] - vexRT[Ch1] - vexRT[Ch4];
		motor[leftrear] = vexRT[Ch3] + vexRT[Ch1] - vexRT[Ch4];
		motor[rightrear]= vexRT[Ch3] - vexRT[Ch1] + vexRT[Ch4];

		//Scoop up/down movement code
		if(vexRT[Btn5U] == 1)
		{
			motor[PillarBottomL] = PillT;
			motor[PillarBottomR] = PillT;
			motor[PillarTopL] = PillT;
			motor[PillarTopR]= PillT;
		}
		else if (vexRT[Btn5D] == 1)
		{
			motor[PillarBottomL] = PillD;
			motor[PillarBottomR] = PillD;
			motor[PillarTopL] = PillD;
			motor[PillarTopR]= PillD;
		}
		else
		{
			motor[PillarBottomL] = 0;
			motor[PillarBottomR] = 0;
			motor[PillarTopL] = 0;
			motor[PillarTopR]= 0;
		}
		if(vexRT[Btn6U] == 1)
		{
			motor[PincerL] = PinOpen;
			motor[PincerR] = PinOpen;
		}
		else if (vexRT[Btn6D] == 1)
		{
			motor[PincerL] = PinClose;
			motor[PincerR] = PinClose;
		}
		else
		{
			motor[PincerL] = 0;
			motor[PincerR] = 0;
		}
	}
}
