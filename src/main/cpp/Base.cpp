#include "Base.h"

void Base::TankDrive(double leftSpeed, double rightSpeed)
{
    leftFrontMotor.Set(ControlMode::PercentOutput, leftSpeed);
    leftRearMotor.Set(ControlMode::PercentOutput, leftSpeed);

    rightFrontMotor.Set(ControlMode::PercentOutput, rightSpeed);
    rightRearMotor.Set(ControlMode::PercentOutput, rightSpeed);
}

void Base::IntakeMotor(bool isOn)
{
    if (isOn)
        intakeMotor.Set(ControlMode::PercentOutput, INTAKE_ROLLER_MOTOR_SPEED);

    else
        intakeMotor.Set(ControlMode::PercentOutput, 0);
}

void Base::ConveyorMotor(bool isOn, bool Direction)
{
    int dir1;
    if (Direction)
    dir1 = 1;
    else
    dir1 = -1;
    if (isOn)
        conveyorMotor.Set(ControlMode::PercentOutput, LOWER_CONVEYOR_MOTOR_SPEED * dir1);
    else
         conveyorMotor.Set(ControlMode::PercentOutput, 0);


}


// void Base::SetGear(bool isHighGear) {
//     shifter.Set(isHighGear);
// }