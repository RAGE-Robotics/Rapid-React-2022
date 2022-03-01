#pragma once

#include "Rage2022.h"
#include "ctre/Phoenix.h"

class Shooter
{
public:
    Shooter();
    double SetShooterSpeedTopVelocityRPM(double speed); // Using velocity speed feedback
    double SetShooterSpeedBottomVelocityRPM(double speed); // Using velocity speed feedback
    double SetShooterSpeedTopVoltage(double voltage);
    double SetShooterSpeedBottomVoltage(double voltage);
    double GetShooterSpeedRPM();
    double SetShooterAngle(double angle);
    double GetShooterAngle(void);
    void SetIntakeRollerSpeed(double rollerSpeed);
    void SetLowerConveyorIntakeMotorSpeed(double motorSpeed);
    void SetShooterFeedMotorSpeed(double feedmotorspeed);
    void SpinUpShooterMotors(void);
    void ShutDownShooterMotors(void);
    void Shoot(void);
    bool IsBallBlockingLowerSensor(void);

    int kTimeoutMs = 0;
    int ballCount = 0;

    double kF;
    double kP;
    double kI;
    double kD;

    int shooterSpeedTopVelocity = SHOOTER_SPEED_TOP_VELOCITY;
    int shooterSpeedBottomVelocity = SHOOTER_SPEED_BOTTOM_VELOCITY;

    bool shooterIsControllingIntakeConveyor; // Allow shooter to override the intake button

    ctre::phoenix::motorcontrol::can::WPI_TalonFX shooterMotorTop{SHOOTER_MOTOR_TOP_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonFX shooterMotorBottom{SHOOTER_MOTOR_BOTTOM_CAN};

    ctre::phoenix::motorcontrol::can::WPI_TalonSRX intakeRollerMotor{INTAKE_ROLLER_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX shooterFeedMotor{SHOOTER_FEED_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX conveyorMotor{INTAKE_ROLLER_MOTOR_CAN};

    frc::DigitalInput ballInSensor{BALL_IN_SENSOR_DIO};
    frc::DigitalInput ballShotSensor{BALL_SHOT_SENSOR_DIO};
    frc::Timer rollerIntakeDelay;
};
