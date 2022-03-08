#include "Base.h"

void Base::TankDrive(double leftSpeed, double rightSpeed)
{
    leftFrontMotor.Set(ControlMode::PercentOutput, -leftSpeed * LEFT_DRIVE_MOTOR_SCALER);
    leftRearMotor.Set(ControlMode::PercentOutput, -leftSpeed * LEFT_DRIVE_MOTOR_SCALER);

    rightFrontMotor.Set(ControlMode::PercentOutput, rightSpeed * RIGHT_DRIVE_MOTOR_SCALER);
    rightRearMotor.Set(ControlMode::PercentOutput, rightSpeed * RIGHT_DRIVE_MOTOR_SCALER);
}

void Base::IntakeMotor(bool isOn)
{
    if (isOn)
    {
        intakeMotor.Set(ControlMode::PercentOutput, -INTAKE_ROLLER_MOTOR_SPEED);
    }
    else
    {
        intakeMotor.Set(ControlMode::PercentOutput, 0);
    }
}

void Base::ConveyorMotor(bool isOn, int direction)
{
    if (isOn)
    {
        conveyorMotor.Set(ControlMode::PercentOutput, CONVEYOR_MOTOR_SPEED * direction);
    }
    else
    {
         conveyorMotor.Set(ControlMode::PercentOutput, 0);
    }
}
