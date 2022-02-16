/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "Rage2022.h"
#include "ctre/Phoenix.h"

#define SHOOTER_SPEED_TOP_VELOCITY 20
#define SHOOTER_MOTOR_TOP_CAN 2
#define SHOOTER_SPEED_BOTTOM_VELOCITY 20
#define SHOOTER_MOTOR_BOTTOM_CAN 6
#define SHOOTER_FEED_MOTOR_CAN 0
#define EXTENDABLE_INTAKE_MOTOR_CAN 0
#define INTAKE_ROLLER_AND_LOWER_CONVEYOR_MOTOR_CAN 0
#define UPPER_INTAKE_ROLLER_CAN 0
#define BALL_IN_SENSOR_DIO 0
#define BALL_SHOT_SENSOR_DIO 0
#define CONVEYOR_SQUEEZE_DOUBLE_SOLENOID 0
#define SHOOTER_HOOD_DOUBLE_SOLENOID 0
#define CONVERT_VELOCITY_TICKS_TO_RPM 0
#define CONVERT_RPM_TO_VELOCITY_TICKS 0
class Shooter
{
public:
    Shooter();
    double SetShooterTopSpeedVoltage(double voltage);
    double SetShooterBottomSpeedVoltage(double voltage);
    double SetShooterSpeedBottomVelocityRPM(double speed); // Using velocity speed feedback
    double SetShooterSpeedTopVelocityRPM(double speed); // Using velocity speed feedback
    double GetShooterSpeedRPM();
    double GetShooterTemperature();
    double SetShooterAngle(double angle);
    double GetShooterAngle(void);
    void SetIntakeRollerSpeed(double rollerSpeed);
    void SetExtendableIntakeRollerSpeed(double rollerSpeed);
    void SetLowerConveyorIntakeMotorSpeed(double motorSpeed);
    void SetShooterFeedMotorSpeed(double feedmotorspeed);
    void SqueezeConveyor(bool squeeze);
    void GrabTheBall(bool grab);
    bool Shoot(bool fire);
    bool RaiseShooterHood(bool raise);
    bool IsShooterMotorTooHot(void);
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

    // ctre::phoenix::motorcontrol::can::WPI_TalonSRX shooterLeadScrewMotor{SHOOTER_LEAD_SCREW_MOTOR_CAN};
    // ctre::phoenix::motorcontrol::can::WPI_TalonSRX intakeRollerMotor{INTAKE_ROLLER_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX shooterFeedMotor{SHOOTER_FEED_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX extendableIntakeMotor{EXTENDABLE_INTAKE_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX lowerConveyorMotor{INTAKE_ROLLER_AND_LOWER_CONVEYOR_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX upperIntakeMotor{UPPER_INTAKE_ROLLER_CAN};

    frc::DigitalInput ballInSensor{BALL_IN_SENSOR_DIO};
    frc::DigitalInput ballShotSensor{BALL_SHOT_SENSOR_DIO};
    frc::Timer rollerIntakeDelay;

    //frc::DoubleSolenoid conveyorSqueezePiston{CONVEYOR_SQUEEZE_DOUBLE_SOLENOID};
    //frc::DoubleSolenoid shooterHoodPiston{SHOOTER_HOOD_DOUBLE_SOLENOID};

};
