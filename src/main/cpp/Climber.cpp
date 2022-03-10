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
