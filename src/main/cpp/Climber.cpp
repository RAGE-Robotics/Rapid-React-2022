#include "Climber.h"

void Climber::RotateClimber(double speed, int direction)
{
#ifdef ENABLE_CLIMBER_SYSTEM
    climberMotor1.Set(ControlMode::PercentOutput, speed * direction);
    climberMotor2.Set(ControlMode::PercentOutput, speed * direction);
#endif
}
