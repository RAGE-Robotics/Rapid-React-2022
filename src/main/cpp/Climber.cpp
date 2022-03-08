#include "Climber.h"

void Climber::RotateClimber(double speed)
{
#ifdef ENABLE_CLIMBER_SYSTEM
    climberMotor1.Set(ControlMode::PercentOutput, speed);
    climberMotor2.Set(ControlMode::PercentOutput, speed);
#endif
}
