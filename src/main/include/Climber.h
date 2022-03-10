#pragma once

#include "Rage2022.h"
#include <frc/drive/DifferentialDrive.h>

class Climber
{
public:
    Climber();
    void RotateClimber(double speed, int direction = 0);

private:
#ifdef ENABLE_CLIMBER_SYSTEM
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX climberMotor1{CLIMBER_MOTOR_1_CAN};
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX climberMotor2{CLIMBER_MOTOR_2_CAN};
#endif
};
