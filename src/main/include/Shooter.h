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
    double GetShooterSpeedTopRPM();
    double GetShooterSpeedBottomRPM();
    double SetShooterAngle(double angle);
    double GetShooterAngle(void);
    void SetIntakeRollerSpeed(double rollerSpeed);
    void SetConveyorIntakeMotorSpeed(double motorSpeed);
    void SetShooterFeedMotorSpeed(double feedmotorspeed);
    void SpinUpShooterMotors(void);
    void ShutDownShooterMotors(void);
    void Shoot(void);
    bool IsBallBlockingLowerSensor(void);
    void IncreaseShooterAngle(void);
    void DecreaseShooterAngle(void);
    void AimShooterTowardsTargetAngle();

    int kTimeoutMs {0};
    int ballCount {0};

    double top_kF {0.};
    double top_kP {0.};
    double top_kI {0.};
    double top_kD {0.};

    double bot_kF {0.};
    double bot_kP {0.};
    double bot_kI {0.};
    double bot_kD {0.};

    double targetShooterAngle {0.};
    double currentShooterAngle {0.};

    int shooterSpeedTopVelocity = SHOOTER_SPEED_TOP_VELOCITY;
    int shooterSpeedBottomVelocity = SHOOTER_SPEED_BOTTOM_VELOCITY;

    bool shooterIsControllingIntakeConveyor; // Allow shooter to override the intake button

    ctre::phoenix::motorcontrol::can::WPI_TalonFX shooterMotorTop{SHOOTER_MOTOR_TOP_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonFX shooterMotorBottom{SHOOTER_MOTOR_BOTTOM_CAN};

    ctre::phoenix::motorcontrol::can::WPI_TalonSRX intakeRollerMotor{INTAKE_ROLLER_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX shooterFeedMotor{SHOOTER_FEED_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX conveyorMotor{SHOOTER_FEED_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX angleMotor{SHOOTER_ANGLE_MOTOR_CAN};

    frc::DigitalInput ballInSensor{BALL_IN_SENSOR_DIO};
    frc::DigitalInput ballShotSensor{BALL_SHOT_SENSOR_DIO};
    frc::Timer rollerIntakeDelay;
};
