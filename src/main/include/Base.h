#pragma once

#include "Rage2022.h"

#include <frc/drive/DifferentialDrive.h>

class Base
{
public:
    Base(){};
    void TankDrive(double leftSpeed, double rightSpeed);
    void SetGear(bool isHighGear);
    void IntakeMotor(bool isOn);
    void ConveyorMotor(bool isOn, bool Direction);

private:
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX leftFrontMotor{LEFT_FRONT_DRIVE_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX leftRearMotor{LEFT_REAR_DRIVE_MOTOR_CAN};

    ctre::phoenix::motorcontrol::can::WPI_TalonSRX rightFrontMotor{RIGHT_FRONT_DRIVE_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX rightRearMotor{RIGHT_REAR_DRIVE_MOTOR_CAN};
    
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX intakeMotor{INTAKE_ROLLER_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX conveyorMotor{INTAKE_ROLLER_AND_LOWER_CONVEYOR_MOTOR_CAN};

    //frc::Solenoid shifter{frc::PneumaticsModuleType::CTREPCM, 0};
    //frc::DoubleSolenoid shifter{GEAR_SHIFT_DOUBLE_SOLENOID, frc::PneumaticsModuleType::CTREPCM, };
};



















//shh