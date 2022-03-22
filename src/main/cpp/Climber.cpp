#include "Climber.h"

Climber::Climber(void)
{
#ifdef ENABLE_CLIMBER_SYSTEM

#endif
}

void Climber::ExtendClimber()
{
#ifdef ENABLE_CLIMBER_SYSTEM
    extendClimberSolenoid.Set(ON);
    retractClimberSolenoid2.Set(OFF);
    retractClimberSolenoid1.Set(ON);
    // frc::Wait(kSolenoidDelay);
    // retractClimberSolenoid1.Set(OFF);
#endif
}

void Climber::RetractClimber()
{
#ifdef ENABLE_CLIMBER_SYSTEM
    extendClimberSolenoid.Set(OFF);
    retractClimberSolenoid1.Set(OFF);
    retractClimberSolenoid2.Set(ON);
    // frc::Wait(kSolenoidDelay);
    // retractClimberSolenoid2.Set(OFF);
#endif
}
