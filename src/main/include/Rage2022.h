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

// Comment out any system definition line to disable support for it

#define ENABLE_DRIVE_SYSTEM
#define ENABLE_INTAKE_SYSTEM
#define ENABLE_SHOOTER_SYSTEM
#define ENABLE_CLIMBER_SYSTEM
#define ENABLE_SMARTDASH_PID
#define ENABLE_COMPRESSOR
#define ENABLE_STICK_CONTROL

//Joysticks and buttons
////////////////////////////////////
#define LEFT_DRIVER_JOYSTICK_USB 0
#define LOW_GEAR_BUTTON 1
#define CLIMBER_EXTEND_BUTTON 10

////////////////////////////////////
#define RIGHT_DRIVER_JOYSTICK_USB 1
#define HIGH_GEAR_BUTTON 1
#define INTAKE_ROLLER_ON_BUTTON_DRIVER 2
#define CLIMBER_RETRACT_BUTTON 10

////////////////////////////////////
#define LEFT_OPERATOR_JOYSTICK_USB 2
#define INTAKE_ROLLER_ON_BUTTON_OP 1
#define CONVEYOR_FORWARD_BUTTON 4
#define CONVEYOR_BACKWARD_BUTTON 5
#define DEPLOY_INTAKE_BUTTON 6
#define RETRACT_INTAKE_BUTTON 7
#define CLIMBER_ENABLE_BUTTON 9
//#define CLIMBER_FORWARD_BUTTON_2 10 // unused

////////////////////////////////////
#define RIGHT_OPERATOR_JOYSTICK_USB 3
#define SHOOT_BUTTON 1
#define SHOOTER_MOTOR_ON_BUTTON 2
#define SHOOTER_ANGLE_INCREASE_BUTTON 4
#define SHOOTER_ANGLE_DECREASE_BUTTON 5
#define CLIMBER_BACK_BUTTON_1 9 // unused
#define CLIMBER_BACK_BUTTON_2 10 // unused

////////////////////////////////////
//List CAN Devices
#ifdef PARADE_ROBOT
    #define LEFT_FRONT_DRIVE_MOTOR_CAN 1    // SRX
    #define LEFT_REAR_DRIVE_MOTOR_CAN 2     // SRX
    #define RIGHT_FRONT_DRIVE_MOTOR_CAN 3   // SRX
    #define RIGHT_REAR_DRIVE_MOTOR_CAN 4    // SRX
#else
    #define LEFT_FRONT_DRIVE_MOTOR_CAN 7    // SRX CIM
    #define LEFT_REAR_DRIVE_MOTOR_CAN 11    // SRX CIM
    #define RIGHT_FRONT_DRIVE_MOTOR_CAN 9   // SRX CIM
    #define RIGHT_REAR_DRIVE_MOTOR_CAN 6    // SRX CIM
#endif

#define INTAKE_ROLLER_MOTOR_CAN 10          // SRX Bag
#define CONVEYOR_MOTOR_CAN 8                // SRX Bag
#define SHOOTER_MOTOR_TOP_CAN 3             // FX  Falcon 500
#define SHOOTER_MOTOR_BOTTOM_CAN 1          // FX  Falcon 500
#define SHOOTER_ANGLE_MOTOR_CAN 12          // SRX Bag

// PCM bits
#define GEAR_SHIFT_UP_SOLENOID 1
#define GEAR_SHIFT_DOWN_SOLENOID 0
#define DEPLOY_INTAKE_SOLENOID 2
#define RETRACT_INTAKE_SOLENOID 4
#define EXTEND_CLIMBER_SOLENOID 3
#define RETRACT_CLIMBER_SOLENOID_1 5
#define RETRACT_CLIMBER_SOLENOID_2 6

// PWM ports

// DIO ports
#define SHOOTER_ANGLE_ZERO_SWITCH_DIO 0
#define PISTON_ONE_EXTENDED_SENSOR_A_DIO 1
#define PISTON_ONE_EXTENDED_SENSOR_B_DIO 2

// Adjustable constants
#define FORWARD +1
#define BACKWARD -1
#define ON true
#define OFF false
#define HIGH_GEAR true
#define LOW_GEAR false

#define LEFT_DRIVE_MOTOR_SCALER 1.0
#define RIGHT_DRIVE_MOTOR_SCALER 0.98

#define INTAKE_ROLLER_MOTOR_SPEED 0.75
#define CONVEYOR_MOTOR_SPEED 0.5
#define SHOOTER_ANGLE_HOME_SPEED 0.5
#define SHOOTER_ANGLE_MOTOR_SPEED 0.3
#define SHOOTER_FEED_MOTOR_SPEED -1.0
#define SHOOTER_SPEED_TOP_VELOCITY 2000         // RPM
#define SHOOTER_SPEED_BOTTOM_VELOCITY 2000      // RPM
#define SHOOTER_SPEED_VELOCITY_AUTONOMOUS 2000
#define SHOOTER_SPEED_VELOCITY_FIFTEEN_FEET 4500
#define SHOOTER_SPEED_VELOCITY_TWENTY_FEET 4800

#define CONVERT_VELOCITY_TICKS_TO_RPM  ((1.0/0.1)*(60.0)*(1.0/2048.0)) //based on 2048 ticks/rev and 100mS sample time
#define CONVERT_RPM_TO_VELOCITY_TICKS (1.0 / CONVERT_VELOCITY_TICKS_TO_RPM)
#define DISTANCE_CALIBRATION_HIGH_GEAR (6.625/60515.0) //Calibrate Known inches / Known Count (inches.0/count.0)
#define DISTANCE_CALIBRATION_LOW_GEAR (6.625/48031.0) //Calibrate Known inches / Known Count (inches.0/count.0)
#define DRIVE_GAIN 0.03 // used in drive distance routine 
#define DISTANCE_ACCURACY (3.0 * 3.0) // get base within 3 inches of target distance SQUARE THE ACCURACY
#define COUNTS_PER_REV 44.0
#define ANGLE_TO_ROTATIONS 1
