#pragma once
#include "Rage2022.h"

#include <frc/drive/DifferentialDrive.h>

class Base
{
public:
    Base() {};
    void TankDrive(double leftSpeed, double rightSpeed);
    void SetGear(bool isHighGear);

private:
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX leftFrontMotor{LEFT_FRONT_DRIVE_MOTOR};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX leftRearMotor{LEFT_REAR_DRIVE_MOTOR};
    
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX rightFrontMotor{RIGHT_FRONT_DRIVE_MOTOR};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX rightRearMotor{RIGHT_REAR_DRIVE_MOTOR};

};