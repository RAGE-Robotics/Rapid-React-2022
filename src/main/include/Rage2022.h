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

#define LEFT_FRONT_DRIVE_MOTOR 1
#define LEFT_REAR_DRIVE_MOTOR 2

#define RIGHT_FRONT_DRIVE_MOTOR 3
#define RIGHT_REAR_DRIVE_MOTOR 4

// #define TEST_JOYSTICK 0

#define RIGHT_DRIVER_JOYSTICK_USB 1
#define LOW_GEAR_BUTTON 1
#define LEFT_DRIVER_JOYSTICK_USB 0
#define HIGH_GEAR_BUTTON 1

#define LEFT_OPERATOR_JOYSTICK_USB 2
#define RIGHT_OPERATOR_JOYSTICK_USB 3

#define SHIFT_GEAR_SOLENOID 0