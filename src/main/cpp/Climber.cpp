#include "Climber.h"

Climber::Climber(void)
{
#ifdef ENABLE_CLIMBER_SYSTEM
    climberMotor1.SetInverted(false);
    climberMotor2.SetInverted(false);
#endif
}

void Climber::RotateClimber(double speed, int direction)
{
#ifdef ENABLE_CLIMBER_SYSTEM
    climberMotor1.Set(ControlMode::PercentOutput, speed * direction);
    climberMotor2.Set(ControlMode::PercentOutput, speed * direction);
#endif
}

void Climber::EngageBrake() {
#ifdef ENABLE_CLIMBER_SYSTEM
    extendBrakeSolenoid.Set(ON);
    retractBrakeSolenoid.Set(OFF);
#endif
}

void Climber::DisengageBrake() {
#ifdef ENABLE_CLIMBER_SYSTEM
    extendBrakeSolenoid.Set(OFF);
    retractBrakeSolenoid.Set(ON);
#endif
}

void Climber::ReleaseBrake() {
#ifdef ENABLE_CLIMBER_SYSTEM
    extendBrakeSolenoid.Set(OFF);
    retractBrakeSolenoid.Set(OFF);
#endif
}