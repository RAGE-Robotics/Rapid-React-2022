#pragma once

#include "Rage2022.h"
#include <frc/drive/DifferentialDrive.h>

class Climber
{
public:
    Climber();
    void ExtendClimber(void);
    void RetractClimber(void);

private:
    const units::time::second_t kSolenoidDelay{1};

#ifdef ENABLE_CLIMBER_SYSTEM
    frc::Solenoid extendClimberSolenoid{frc::PneumaticsModuleType::REVPH, EXTEND_CLIMBER_SOLENOID};
    frc::Solenoid retractClimberSolenoid1{frc::PneumaticsModuleType::REVPH, RETRACT_CLIMBER_SOLENOID_1};
    frc::Solenoid retractClimberSolenoid2{frc::PneumaticsModuleType::REVPH, RETRACT_CLIMBER_SOLENOID_2};
#endif
};
