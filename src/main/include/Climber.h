#pragma once

#include "Rage2022.h"
#include <frc/drive/DifferentialDrive.h>

class Climber
{
public:
    Climber();
    // void RotateClimber(double speed, int direction = 0);
    void ExtendClimber(void);
    void RetractClimber(void);
    // void ReleaseBrake(void);

private:
#ifdef ENABLE_CLIMBER_SYSTEM
    ctre::phoenix::motorcontrol::can::WPI_TalonFX climberMotor1{CLIMBER_MOTOR_1_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonFX climberMotor2{CLIMBER_MOTOR_2_CAN};

    frc::Solenoid extendClimberSolenoid{frc::PneumaticsModuleType::REVPH, EXTEND_CLIMBER_SOLENOID};
    frc::Solenoid retractClimberSolenoid1{frc::PneumaticsModuleType::REVPH, RETRACT_CLIMBER_SOLENOID_1};
    frc::Solenoid retractClimberSolenoid2{frc::PneumaticsModuleType::REVPH, RETRACT_CLIMBER_SOLENOID_2};

#endif
};
