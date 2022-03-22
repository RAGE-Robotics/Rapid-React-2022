#include "Climber.h"

Climber::Climber(void)
{
    // #ifdef ENABLE_CLIMBER_SYSTEM
    //     climberMotor1.SetInverted(false);
    //     climberMotor2.SetInverted(false);
    // #endif
}

// void Climber::RotateClimber(double speed, int direction)
// {
// #ifdef ENABLE_CLIMBER_SYSTEM
//     climberMotor1.Set(ControlMode::PercentOutput, speed * direction);
//     climberMotor2.Set(ControlMode::PercentOutput, speed * direction);
// #endif
// }

void Climber::ExtendClimber()
{
#ifdef ENABLE_CLIMBER_SYSTEM
    static bool toggle = ON;

    extendClimberSolenoid.Set(ON);
    retractClimberSolenoid1.Set(!toggle);
    retractClimberSolenoid2.Set(toggle);
    toggle = OFF;
#endif
}

void Climber::RetractClimber()
{
#ifdef ENABLE_CLIMBER_SYSTEM
    static bool toggle = ON;

    extendClimberSolenoid.Set(OFF);
    retractClimberSolenoid1.Set(toggle);
    retractClimberSolenoid2.Set(!toggle);
    toggle = OFF;
#endif
}

// void Climber::ReleaseBrake() {
// #ifdef ENABLE_CLIMBER_SYSTEM
//     extendBrakeSolenoid.Set(OFF);
//     retractBrakeSolenoid.Set(OFF);
// #endif
// }