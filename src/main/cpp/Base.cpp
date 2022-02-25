#include "Base.h"

void Base::TankDrive(double leftSpeed, double rightSpeed)
{
    leftFrontMotor.Set(ControlMode::PercentOutput, leftSpeed);
    leftRearMotor.Set(ControlMode::PercentOutput, leftSpeed);

    rightFrontMotor.Set(ControlMode::PercentOutput, rightSpeed);
    rightRearMotor.Set(ControlMode::PercentOutput, rightSpeed);
}

// void Base::SetGear(bool isHighGear) {
//     shifter.Set(isHighGear);
// }