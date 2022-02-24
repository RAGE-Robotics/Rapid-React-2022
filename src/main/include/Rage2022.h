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
#define TEST_MODE 1

//Joysticks and buttons
#define LEFT_DRIVER_JOYSTICK_USB 0
#define LOW_GEAR_BUTTON 1

#define RIGHT_DRIVER_JOYSTICK_USB 1
#define HIGH_GEAR_BUTTON 1

#define LEFT_OPERATOR_JOYSTICK_USB 2
//#define EXTEND_CLIMBER_A_BUTTON 7
//#define EXTEND_CLIMBER_B_BUTTON 10
#define WINCH_UP_THE_ROBOT_BUTTON 1
//#define EXTEND_PISTON_ONE_BUTTON 7
//#define RELEASE_LATCHES_BUTTON 8
#define EXTEND_PISTON_ONE_BUTTON 8
#define EXTEND_PISTON_TWO_BUTTON 9
#define RETRACT_BOTH_PISTONS_BUTTON 10
//#define UNWHINCH_THE_ROBOT_BUTTON 2

#define RIGHT_OPERATOR_JOYSTICK_USB 3
#define INTAKE_ROLLER_ON_BUTTON 1
#define SHOOT_BUTTON 2
#define SHOOTER_MOTOR_ON_BUTTON 9
#define SHOOTER_MOTOR_OFF_BUTTON 8
#define UNWIND_THE_WINCH_BUTTON 10
#define SHOOTER_HOOD_DOWN_BUTTON 4
#define SHOOTER_HOOD_UP_BUTTON 5
#define REVERSE_INTAKE_BUTTON 3
#define SHOOTER_VELOCITY_FIFTEEN_FEET_BUTTON 6
#define SHOOTER_VELOCITY_TWENTY_FEET_BUTTON 7

#define TEST_JOYSTICK_USB 0

//List CAN Devices
#ifdef PARADE_ROBOT
    #define LEFT_FRONT_DRIVE_MOTOR_CAN 1  //FX
    #define LEFT_REAR_DRIVE_MOTOR_CAN 2   //FX
    #define RIGHT_FRONT_DRIVE_MOTOR_CAN 3 //FX
    #define RIGHT_REAR_DRIVE_MOTOR_CAN 4  //FX
#else
    #define LEFT_FRONT_DRIVE_MOTOR_CAN 7  //FX
    #define LEFT_REAR_DRIVE_MOTOR_CAN 11  //FX
    #define RIGHT_FRONT_DRIVE_MOTOR_CAN 9 //FX
    #define RIGHT_REAR_DRIVE_MOTOR_CAN 6  //FX
#endif

// #define INTAKE_ROLLER_MOTOR_CAN 6 //SRX
#define SHOOTER_MOTOR_TOP_CAN 2
#define SHOOTER_MOTOR_BOTTOM_CAN 5
#define SHOOTER_FEED_MOTOR_CAN 7                     //SRX
#define EXTENDABLE_INTAKE_MOTOR_CAN 10               //SRX
#define INTAKE_ROLLER_AND_LOWER_CONVEYOR_MOTOR_CAN 6 //SRX
#define UPPER_INTAKE_ROLLER_CAN 8 //SRX

#define SHOOTER_MOTOR_CAN 5            //5 FX
//#define SHOOTER_LEAD_SCREW_MOTOR_CAN 8 //SRX

#define SPINNER_MOTOR_CAN 9 //SRX

#define CLIMBER_WINCH_MOTOR_CAN 11 //SRX

//define all PCM's here
#define GEAR_SHIFT_DOUBLE_SOLENOID 0
//#define GEAR_SHIFT_DOUBLE_SOLENOID 0, 0, 1
#define SPINNER_PISTON_SOLENOID 0, 2
#define ALL_MOTOR_COOLING_SOLENOID 0, 3
#define LATCH_RELEASE_SOLENOID 0, 4

#define CONVEYOR_SQUEEZE_DOUBLE_SOLENOID 1, 0, 1
#define PISTON_ONE_DOUBLE_SOLENOID 1, 2, 3
#define PISTON_TWO_DOUBLE_SOLENOID 1, 4, 5
#define SHOOTER_HOOD_DOUBLE_SOLENOID 1, 6, 7

//PWM ports
#define WINCH_PAWL_SERVO_PWM 0
//DIO ports
#define ARM_SWING_SENSOR_DIO 0
#define PISTON_ONE_EXTENDED_SENSOR_A_DIO 1
#define PISTON_ONE_EXTENDED_SENSOR_B_DIO 2
#define BALL_SHOT_SENSOR_DIO 3
#define BALL_IN_SENSOR_DIO 4

// Adjustable constants

#define SPINNER_MOTOR_SPEED 0.5
#define WINCH_UP_SPEED -1.0
#define WINCH_CLEAR_PAWL_SPEED -0.6  //wind a bit to free up the awl in casse it is engaged
#define WINCH_UNWIND_SPEED 1.0
#define PAWL_SERVO_LOCKED 0.0
#define PAWL_SERVO_FREE 1.0
#define INTAKE_ROLLER_MOTOR_SPEED 0.5 //1.0
#define EXTENDABLE_INTAKE_MOTOR_SPEED 1.0
#define SHOOTER_FEED_MOTOR_SPEED -1.0
#define SHOOTER_SPEED_TOP_VELOCITY 4000 //RPM
#define SHOOTER_SPEED_BOTTOM_VELOCITY 4000 //RPM
#define SHOOTER_SPEED_VELOCITY_AUTONOMOUS 4000
#define SHOOTER_SPEED_VELOCITY_FIFTEEN_FEET 4500
#define SHOOTER_SPEED_VELOCITY_TWENTY_FEET 4800
#define LOWER_CONVEYOR_MOTOR_SPEED 1.0
#define CONVERT_VELOCITY_TICKS_TO_RPM  ((1.0/0.1)*(60.0)*(1.0/2048.0)) //based on 2048 ticks/rev and 100mS sample time
#define CONVERT_RPM_TO_VELOCITY_TICKS (1.0 / CONVERT_VELOCITY_TICKS_TO_RPM)
#define DISTANCE_CALIBRATION_HIGH_GEAR (6.625/60515.0) //Calibrate Known inches / Known Count (inches.0/count.0)
#define DISTANCE_CALIBRATION_LOW_GEAR (6.625/48031.0) //Calibrate Known inches / Known Count (inches.0/count.0)
#define DRIVE_GAIN 0.03 // used in drive distance routine 
#define DISTANCE_ACCURACY (3.0 * 3.0) // get base within 3 inches of target distance SQUARE THE ACCURACY
#define SERVO_PAWL_ENGAGED 0.0
#define SERVO_PAWL_DISENGAGED 0.35
#define MAX_MOTOR_TEMP 40.0
#define AUTO_SHOOTER_SHORT_DELAY 2.0
#define AUTO_SHOOTER_LONG_DELAY 7.0
#define AUTO_DRIVE_DELAY_AFTER_SHOOT 5.0
#define ROLLER_INTAKE_DELAY 0.25
#define AUTO_DRIVE_DISTANCE 30
