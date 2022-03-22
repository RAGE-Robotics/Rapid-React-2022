#include "Base.h"

Base::Base(void)
{
#ifdef ENABLE_DRIVE_SYSTEM
    leftFrontMotor.SetInverted(true);
    leftRearMotor.SetInverted(true);
    rightFrontMotor.SetInverted(false);
    rightRearMotor.SetInverted(false);

    leftFrontMotor.SetNeutralMode(Brake);
    leftRearMotor.SetNeutralMode(Brake);
    rightFrontMotor.SetNeutralMode(Brake);
    rightRearMotor.SetNeutralMode(Brake);
#endif
#ifdef ENABLE_INTAKE_SYSTEM
    intakeMotor.SetInverted(true);
    conveyorMotor.SetInverted(false);

    intakeMotor.SetNeutralMode(Coast);
    conveyorMotor.SetNeutralMode(Coast);
#endif
}

void Base::TankDrive(double leftSpeed, double rightSpeed)
{
#ifdef ENABLE_DRIVE_SYSTEM
    leftFrontMotor.Set(ControlMode::PercentOutput, leftSpeed * LEFT_DRIVE_MOTOR_SCALER);
    leftRearMotor.Set(ControlMode::PercentOutput, leftSpeed * LEFT_DRIVE_MOTOR_SCALER);

    rightFrontMotor.Set(ControlMode::PercentOutput, rightSpeed * RIGHT_DRIVE_MOTOR_SCALER);
    rightRearMotor.Set(ControlMode::PercentOutput, rightSpeed * RIGHT_DRIVE_MOTOR_SCALER);
#endif
}

void Base::SetGear(bool isHighGear)
{
#ifdef ENABLE_DRIVE_SYSTEM
    if (isHighGear) {
        gearDownSolenoid.Set(false);
        gearUpSolenoid.Set(true);
    } else {
        gearUpSolenoid.Set(false);
        gearDownSolenoid.Set(true);
    }
#endif
}

void Base::DeployIntake(void)
{
#ifdef ENABLE_INTAKE_SYSTEM
    retractIntakeSolenoid.Set(false);
    deployIntakeSolenoid.Set(true);
#endif
}

void Base::ReleaseIntake(void)
{
#ifdef ENABLE_INTAKE_SYSTEM
    retractIntakeSolenoid.Set(false);
    deployIntakeSolenoid.Set(false);
#endif
}

void Base::RetractIntake(void)
{
#ifdef ENABLE_INTAKE_SYSTEM
    deployIntakeSolenoid.Set(false);
    retractIntakeSolenoid.Set(true);
#endif
}

void Base::IntakeMotor(bool isOn)
{
#ifdef ENABLE_INTAKE_SYSTEM
    if (isOn) {
        intakeMotor.Set(ControlMode::PercentOutput, -INTAKE_ROLLER_MOTOR_SPEED);
    } else {
        intakeMotor.Set(ControlMode::PercentOutput, 0);
    }
#endif
}

void Base::IntakeMotorReverse(bool isOn)
{
#ifdef ENABLE_INTAKE_SYSTEM
    if (isOn) {
        intakeMotor.Set(ControlMode::PercentOutput, INTAKE_ROLLER_MOTOR_SPEED);
    } else {
        intakeMotor.Set(ControlMode::PercentOutput, 0);
    }
#endif
}

void Base::ConveyorMotor(bool isOn, int direction)
{
#ifdef ENABLE_INTAKE_SYSTEM
    if (isOn) {
        conveyorMotor.Set(ControlMode::PercentOutput, CONVEYOR_MOTOR_SPEED * direction);
    } else {
        conveyorMotor.Set(ControlMode::PercentOutput, 0);
    }
#endif
}
