#pragma once

#include "Rage2022.h"
#include <frc/drive/DifferentialDrive.h>

class Climber
{
public:
    Climber();
    void RotateClimber(double speed, int direction = 0);
    void EngageBrake(void);
    void DisengageBrake(void);
    void ReleaseBrake(void);


private:
#ifdef ENABLE_CLIMBER_SYSTEM
    ctre::phoenix::motorcontrol::can::WPI_TalonFX climberMotor1{CLIMBER_MOTOR_1_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonFX climberMotor2{CLIMBER_MOTOR_2_CAN};
    
    frc::Solenoid extendBrakeSolenoid{frc::PneumaticsModuleType::REVPH, EXTEND_CLIMBER_BRAKE_SOLENOID};
    frc::Solenoid retractBrakeSolenoid{frc::PneumaticsModuleType::REVPH, RETRACT_CLIMBER_BRAKE_SOLENOID};

#endif
};
