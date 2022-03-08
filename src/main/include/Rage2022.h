#pragma once

#include <ctre/Phoenix.h>
#include <frc/Compressor.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/AddressableLED.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Joystick.h>
#include <frc/Servo.h>
#include <frc/DigitalInput.h>
#include <frc/Timer.h>
#include <frc/DriverStation.h>

#define DEG_TO_RAD (M_PI / 180.0)

// Uncomment to build code for the parade robot.
// Comment out the line to build for the competition robot
//#define PARADE_ROBOT

//Test mode enter true = 1
#define TEST_MODE 0

//Joysticks and buttons
////////////////////////////////////
#define LEFT_DRIVER_JOYSTICK_USB 0
#define LOW_GEAR_BUTTON 1

////////////////////////////////////
#define RIGHT_DRIVER_JOYSTICK_USB 1
#define HIGH_GEAR_BUTTON 1
#define INTAKE_ROLLER_ON_BUTTON_B 2

////////////////////////////////////
#define LEFT_OPERATOR_JOYSTICK_USB 2
#define INTAKE_ROLLER_ON_BUTTON_OP 1
#define CONVEYOR_FORWARD_BUTTON 4
#define CONVEYOR_BACKWARD_BUTTON 5
#define DEPLOY_INTAKE_BUTTON 6
#define RETRACT_INTAKE_BUTTON 7

////////////////////////////////////
#define RIGHT_OPERATOR_JOYSTICK_USB 3
#define SHOOT_BUTTON 1
#define SHOOTER_MOTOR_ON_BUTTON 2
#define SHOOTER_ANGLE_INCREASE_BUTTON 4
#define SHOOTER_ANGLE_DECREASE_BUTTON 5

#define TEST_JOYSTICK_USB 0

////////////////////////////////////
//List CAN Devices
#ifdef PARADE_ROBOT
    #define LEFT_FRONT_DRIVE_MOTOR_CAN 1    //SRX
    #define LEFT_REAR_DRIVE_MOTOR_CAN 2     //SRX
    #define RIGHT_FRONT_DRIVE_MOTOR_CAN 3   //SRX
    #define RIGHT_REAR_DRIVE_MOTOR_CAN 4    //SRX
#else
    #define LEFT_FRONT_DRIVE_MOTOR_CAN 7    //SRX
    #define LEFT_REAR_DRIVE_MOTOR_CAN 11    //SRX
    #define RIGHT_FRONT_DRIVE_MOTOR_CAN 9   //SRX
    #define RIGHT_REAR_DRIVE_MOTOR_CAN 6    //SRX
#endif

#define INTAKE_ROLLER_MOTOR_CAN 10          //SRX
#define SHOOTER_MOTOR_TOP_CAN 3
#define SHOOTER_MOTOR_BOTTOM_CAN 1
#define SHOOTER_FEED_MOTOR_CAN 8            //SRX
#define SHOOTER_ANGLE_MOTOR_CAN 12

// PCM bits
#define GEAR_SHIFT_UP_SOLENOID 0
#define GEAR_SHIFT_DOWN_SOLENOID 1
#define BALL_GATE_SOLENOID 3
#define DEPLOY_INTAKE_SOLENOID 2
#define RETRACT_INTAKE_SOLENOID 4

// PWM ports

// DIO ports
#define PISTON_ONE_EXTENDED_SENSOR_A_DIO 1
#define PISTON_ONE_EXTENDED_SENSOR_B_DIO 2
#define BALL_SHOT_SENSOR_DIO 3
#define BALL_IN_SENSOR_DIO 4

// Adjustable constants

#define FORWARD +1
#define BACKWARD -1
#define INTAKE_ROLLER_MOTOR_SPEED 0.75 //1.0
#define SHOOTER_FEED_MOTOR_SPEED -1.0
#define SHOOTER_SPEED_TOP_VELOCITY 5000.0 //RPM
#define SHOOTER_SPEED_BOTTOM_VELOCITY 5000.0 //RPM
#define SHOOTER_SPEED_VELOCITY_AUTONOMOUS 4000.0
#define SHOOTER_SPEED_VELOCITY_FIFTEEN_FEET 4500.0
#define SHOOTER_SPEED_VELOCITY_TWENTY_FEET 4800.0
#define LOWER_CONVEYOR_MOTOR_SPEED 0.5
#define CONVERT_VELOCITY_TICKS_TO_RPM  ((1.0/0.1)*(60.0)*(1.0/2048.0)) //based on 2048 ticks/rev and 100mS sample time
#define CONVERT_RPM_TO_VELOCITY_TICKS (1.0 / CONVERT_VELOCITY_TICKS_TO_RPM)
#define DISTANCE_CALIBRATION_HIGH_GEAR (6.625/60515.0) //Calibrate Known inches / Known Count (inches.0/count.0)
#define DISTANCE_CALIBRATION_LOW_GEAR (6.625/48031.0) //Calibrate Known inches / Known Count (inches.0/count.0)
#define DRIVE_GAIN 0.03 // used in drive distance routine 
#define DISTANCE_ACCURACY (3.0 * 3.0) // get base within 3 inches of target distance SQUARE THE ACCURACY
#define ROTATION_CONSTANT 4096.0
#define ANGLE_TO_ROTATIONS 1
