#pragma once

#include "Rage2022.h"
#include <frc/drive/DifferentialDrive.h>

class Base
{
public:
    Base(); // Based
    void TankDrive(double leftSpeed, double rightSpeed);
    void SetGear(bool isHighGear);
    void DeployIntake(void);
    void ReleaseIntake(void);
    void RetractIntake(void);
    void IntakeMotor(bool isOn);
    void ConveyorMotor(bool isOn, int direction = 0);

private:
#ifdef ENABLE_DRIVE_SYSTEM
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX leftFrontMotor{LEFT_FRONT_DRIVE_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX leftRearMotor{LEFT_REAR_DRIVE_MOTOR_CAN};

    ctre::phoenix::motorcontrol::can::WPI_TalonSRX rightFrontMotor{RIGHT_FRONT_DRIVE_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX rightRearMotor{RIGHT_REAR_DRIVE_MOTOR_CAN};

    frc::Solenoid gearUpSolenoid{frc::PneumaticsModuleType::REVPH, GEAR_SHIFT_UP_SOLENOID};
    frc::Solenoid gearDownSolenoid{frc::PneumaticsModuleType::REVPH, GEAR_SHIFT_DOWN_SOLENOID};
#endif
#ifdef ENABLE_INTAKE_SYSTEM
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX intakeMotor{INTAKE_ROLLER_MOTOR_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX conveyorMotor{CONVEYOR_MOTOR_CAN};

    frc::Solenoid deployIntakeSolenoid{frc::PneumaticsModuleType::REVPH, DEPLOY_INTAKE_SOLENOID};
    frc::Solenoid retractIntakeSolenoid{frc::PneumaticsModuleType::REVPH, RETRACT_INTAKE_SOLENOID};
#endif
    
    // frc::Solenoid ballGateSolenoid{frc::PneumaticsModuleType::REVPH, BALL_GATE_SOLENOID};
};
