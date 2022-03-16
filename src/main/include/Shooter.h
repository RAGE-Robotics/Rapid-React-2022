#pragma once

#include "Rage2022.h"
#include "ctre/Phoenix.h"

class Shooter
{
public:
    Shooter();
    void SetShooterSpeedTopVoltage(double voltage);
    void SetShooterSpeedBottomVoltage(double voltage);
    void SetShooterSpeedTopVelocityRPM(double speed); // Using velocity speed feedback
    void SetShooterSpeedBottomVelocityRPM(double speed); // Using velocity speed feedback
    double GetShooterSpeedTopRPM();
    double GetShooterSpeedBottomRPM();

    void SpinUpShooterMotors(void);
    void ShutDownShooterMotors(void);
    void Shoot(void);

    void MoveAngleMotor(double speed, int direction = 0);
    bool AngleMotorAtHome(void);
    void IncreaseTargetAngle(void);
    void DecreaseTargetAngle(void);
    void AimShooter(double turns);
    void SetShooterAngle(double angle);
    double GetShooterAngle(void);

    void SetIntakeRollerSpeed(double rollerSpeed);
    void SetConveyorIntakeMotorSpeed(double motorSpeed);

    bool IsBallBlockingLowerSensor(void);

private:
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

#ifdef ENABLE_SHOOTER_SYSTEM
    ctre::phoenix::motorcontrol::can::WPI_TalonFX shooterMotorTop{SHOOTER_MOTOR_TOP_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonFX shooterMotorBottom{SHOOTER_MOTOR_BOTTOM_CAN};

    ctre::phoenix::motorcontrol::can::WPI_TalonSRX intakeRollerMotor{INTAKE_ROLLER_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX conveyorMotor{CONVEYOR_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX angleMotor{SHOOTER_ANGLE_MOTOR_CAN};
#endif

    frc::DigitalInput angleAtHome{SHOOTER_ANGLE_ZERO_SWITCH_DIO};
    frc::Timer rollerIntakeDelay;
};
