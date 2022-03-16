#include "Shooter.h"
#include <frc/smartdashboard/SmartDashboard.h>

Shooter::Shooter()
{
#ifdef ENABLE_SHOOTER_SYSTEM
    shooterMotorTop.ConfigFactoryDefault();
    shooterMotorTop.SetNeutralMode(Coast);
    shooterMotorTop.SetInverted(true);
    shooterMotorTop.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::IntegratedSensor, 0, 0);
    shooterMotorTop.SetSensorPhase(true);
    shooterMotorTop.ConfigClosedloopRamp(1.0); // seconds from 0 to full speed;

    shooterMotorBottom.ConfigFactoryDefault();
    shooterMotorBottom.SetNeutralMode(Coast);
    shooterMotorBottom.SetInverted(false);
    shooterMotorBottom.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::IntegratedSensor, 0, 0);
    shooterMotorBottom.SetSensorPhase(true);
    shooterMotorBottom.ConfigClosedloopRamp(1.0); // seconds from 0 to full speed;

    angleMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::IntegratedSensor);
    angleMotor.SetInverted(false);
#endif

    kTimeoutMs = 0;

    top_kF = 0.1;       // 0.1
    top_kP = 0.25;      // 0.15
    top_kI = 0.;        // 0.00008
    top_kD = 0.;        // 0.01

    bot_kF = 0.1;       // 0.1
    bot_kP = 0.25;      // 0.15
    bot_kI = 0.;        // 0.00008
    bot_kD = 0.;        //0.01;

#ifdef ENABLE_SMARTDASH_PID
    frc::SmartDashboard::PutNumber("Top kF", top_kF);
    frc::SmartDashboard::PutNumber("Top kP", top_kP);
    frc::SmartDashboard::PutNumber("Top kI", top_kI);
    frc::SmartDashboard::PutNumber("Top kD", top_kD);

    frc::SmartDashboard::PutNumber("Bot kF", bot_kF);
    frc::SmartDashboard::PutNumber("Bot kP", bot_kP);
    frc::SmartDashboard::PutNumber("Bot kI", bot_kI);
    frc::SmartDashboard::PutNumber("Bot kD", bot_kD);
#endif

#ifdef ENABLE_SHOOTER_SYSTEM
    // For velocity feedback
    shooterMotorTop.Config_kF(0, top_kF, kTimeoutMs);
    shooterMotorTop.Config_kP(0, top_kP, kTimeoutMs);
    shooterMotorTop.Config_kI(0, top_kI, kTimeoutMs);
    shooterMotorTop.Config_kD(0, top_kD, kTimeoutMs);

    shooterMotorBottom.Config_kF(0, bot_kF, kTimeoutMs);
    shooterMotorBottom.Config_kP(0, bot_kP, kTimeoutMs);
    shooterMotorBottom.Config_kI(0, bot_kI, kTimeoutMs);
    shooterMotorBottom.Config_kD(0, bot_kD, kTimeoutMs);
#endif
}

void Shooter::SetShooterSpeedTopVoltage(double voltage)
{
#ifdef ENABLE_SHOOTER_SYSTEM
    shooterMotorTop.Set(ControlMode::PercentOutput, voltage);
#endif
}
void Shooter::SetShooterSpeedBottomVoltage(double voltage)
{
#ifdef ENABLE_SHOOTER_SYSTEM
    shooterMotorBottom.Set(ControlMode::PercentOutput, voltage);
#endif
}

void Shooter::SetShooterSpeedTopVelocityRPM(double speed)
{
    if (speed == 0.0)
    {
        SetShooterSpeedTopVoltage(0.0);
        return;
    }

#ifdef ENABLE_SMARTDASH_PID
    double newF = frc::SmartDashboard::GetNumber("Top kF", 0);
    double newP = frc::SmartDashboard::GetNumber("Top kP", 0);
    double newI = frc::SmartDashboard::GetNumber("Top kI", 0);
    double newD = frc::SmartDashboard::GetNumber("Top kD", 0);

    int newShooterSpeedVelocity = frc::SmartDashboard::GetNumber("Set Shooter Top Speed", 0);
    frc::SmartDashboard::PutNumber("newF", newF);

    // for velocity feedback
    if (newF != top_kF)
    {
        top_kF = newF;
        shooterMotorTop.Config_kF(0, top_kF, kTimeoutMs);
    }
    if (newP != top_kP)
    {
        top_kP = newP;
        shooterMotorTop.Config_kP(0, top_kP, kTimeoutMs);
    } // Accelerates at .5 try 0.1
    if (newI != top_kI)
    {
        top_kI = newI;
        // shooterMotorTop.Config_kI(0, top_kI, kTimeoutMs);
    }
    if (newD != top_kD)
    {
        top_kD = newD;
        // shooterMotorTop.Config_kD(0, top_kD, kTimeoutMs);
    }
    if (newShooterSpeedVelocity != shooterSpeedTopVelocity)
    {
        shooterSpeedTopVelocity = newShooterSpeedVelocity;
    }
#endif
#ifdef ENABLE_SHOOTER_SYSTEM
    double speedRawUnitsPer100Ms = speed * CONVERT_RPM_TO_VELOCITY_TICKS;
    shooterMotorTop.Set(ControlMode::Velocity, speedRawUnitsPer100Ms);
#endif
}

void Shooter::SetShooterSpeedBottomVelocityRPM(double speed)
{
    if (speed == 0.0)
    {
        SetShooterSpeedBottomVoltage(0.0);
        return;
    }

#ifdef ENABLE_SMARTDASH_PID
    double newF = frc::SmartDashboard::GetNumber("Bot kF", 0);
    double newP = frc::SmartDashboard::GetNumber("Bot kP", 0);
    double newI = frc::SmartDashboard::GetNumber("Bot kI", 0);
    double newD = frc::SmartDashboard::GetNumber("Bot kD", 0);

    int newShooterSpeedVelocity = frc::SmartDashboard::GetNumber("Set Shooter Bottom Speed", 0);
    frc::SmartDashboard::PutNumber("newF", newF);

    // for velocity feedback
    if (newF != bot_kF)
    {
        bot_kF = newF;
        shooterMotorBottom.Config_kF(0, bot_kF, kTimeoutMs);
    }
    if (newP != bot_kP)
    {
        bot_kP = newP;
        shooterMotorBottom.Config_kP(0, bot_kP, kTimeoutMs);
    } // Accelerates at .5 try 0.1
    if (newI != bot_kI)
    {
        bot_kI = newI;
        shooterMotorBottom.Config_kI(0, bot_kI, kTimeoutMs);
    }
    if (newD != bot_kD)
    {
        bot_kD = newD;
        shooterMotorBottom.Config_kD(0, bot_kD, kTimeoutMs);
    }
    if (newShooterSpeedVelocity != shooterSpeedBottomVelocity)
    {
        shooterSpeedBottomVelocity = newShooterSpeedVelocity;
    }
#endif
#ifdef ENABLE_SHOOTER_SYSTEM
    double speedRawUnitsPer100Ms = speed * CONVERT_RPM_TO_VELOCITY_TICKS;
    shooterMotorBottom.Set(ControlMode::Velocity, speedRawUnitsPer100Ms);
#endif
}

double Shooter::GetShooterSpeedTopRPM()
{
#ifdef ENABLE_SHOOTER_SYSTEM
    int rawSensorVelocityTop = shooterMotorTop.GetSelectedSensorVelocity(0);
    double shooterVelocityTopRPM = double(rawSensorVelocityTop) * CONVERT_VELOCITY_TICKS_TO_RPM;

    frc::SmartDashboard::PutNumber("shooterVelocityTopRAW: ", rawSensorVelocityTop);
    frc::SmartDashboard::PutNumber("shooterVelocityTopRPM: ", shooterVelocityTopRPM);

    return shooterVelocityTopRPM;
#else
    return 0.;
#endif
}

double Shooter::GetShooterSpeedBottomRPM()
{
#ifdef ENABLE_SHOOTER_SYSTEM
    int rawSensorVelocityBottom = shooterMotorBottom.GetSelectedSensorVelocity(0);
    double shooterVelocityBottomRPM = double(rawSensorVelocityBottom) * CONVERT_VELOCITY_TICKS_TO_RPM;

    frc::SmartDashboard::PutNumber("shooterVelocityBottomRAW: ", rawSensorVelocityBottom);
    frc::SmartDashboard::PutNumber("shooterVelocityBottomRPM: ", shooterVelocityBottomRPM);

    return shooterVelocityBottomRPM;
#else
    return 0.;
#endif
}

void Shooter::SpinUpShooterMotors(void)
{
    SetShooterSpeedTopVelocityRPM(shooterSpeedTopVelocity);
    SetShooterSpeedBottomVelocityRPM(shooterSpeedBottomVelocity);
}

void Shooter::ShutDownShooterMotors(void)
{
    SetShooterSpeedTopVelocityRPM(0);
    SetShooterSpeedBottomVelocityRPM(0);
}

void Shooter::Shoot(void)
{
    // Check to be sure wheels are up to speed

    // When they are, fire solenoid

    // start the shooter wheel

    SetShooterSpeedTopVelocityRPM(shooterSpeedTopVelocity);
    SetShooterSpeedBottomVelocityRPM(shooterSpeedBottomVelocity);

    // we may have to wait for an acceptable speed
    // if (GetShooterSpeedRPM() > (shooterSpeedTopVelocity * 0.95)) // adjust the speed limit as needed
    // {
    //    SetLowerConveyorIntakeMotorSpeed(LOWER_CONVEYOR_MOTOR_SPEED);
    //    SetShooterFeedMotorSpeed(SHOOTER_FEED_MOTOR_SPEED);
    //    SqueezeConveyor(true);
    //    shooterIsControllingIntakeConveyor = true; // Allow shooter to override the intake button
    // }
}

void Shooter::MoveAngleMotor(double speed, int direction)
{
#ifdef ENABLE_SHOOTER_SYSTEM
    angleMotor.Set(ControlMode::PercentOutput, speed * direction);
#endif
}

bool Shooter::AngleMotorAtHome(void)
{
    bool isAtHome = !angleAtHome.Get();
    return isAtHome;
}

void Shooter::IncreaseTargetAngle(void)
{
    targetShooterAngle += DEG_TO_RAD * 15.0;
}

void Shooter::DecreaseTargetAngle(void)
{
    targetShooterAngle -= DEG_TO_RAD * 15.0;
}

void Shooter::AimShooter(double turns)
{
#ifdef ENABLE_SHOOTER_SYSTEM
    // double rotations = (currentShooterAngle - targetShooterAngle) * ANGLE_TO_ROTATIONS;
    // angleMotor.Set(ControlMode::Position, rotations);
    // currentShooterAngle = targetShooterAngle;
    angleMotor.Set(ControlMode::Position, turns * COUNTS_PER_REV);
#endif
}

double Shooter::GetShooterAngle(void)
{
#ifdef ENABLE_SHOOTER_SYSTEM
    int angleCount = angleMotor.GetSelectedSensorPosition(0);
    currentShooterAngle = double(angleCount) / COUNTS_PER_REV;
    //frc::SmartDashboard::PutNumber("shooter angle count raw", angleCount);
#endif
    return currentShooterAngle;
}

void Shooter::SetIntakeRollerSpeed(double rollerSpeed)
{
#ifdef ENABLE_SHOOTER_SYSTEM
    double upperRollerSpeed = rollerSpeed;
    intakeRollerMotor.Set(upperRollerSpeed);
#endif
}

void Shooter::SetConveyorIntakeMotorSpeed(double motorSpeed)
{
#ifdef ENABLE_SHOOTER_SYSTEM
    conveyorMotor.Set(motorSpeed);
#endif
}

#if 0
void Shooter::GrabTheBall(bool grab)
{
    if (grab == true)
    {
        SetIntakeRollerSpeed(INTAKE_ROLLER_MOTOR_SPEED);
    }
    else
    {
        SetIntakeRollerSpeed(0.0);
    }
    if (IsBallBlockingLowerSensor() == true) //! used to calibrate sensor
    {
        SetLowerConveyorIntakeMotorSpeed(LOWER_CONVEYOR_MOTOR_SPEED);
        SetShooterFeedMotorSpeed(SHOOTER_FEED_MOTOR_SPEED);
        shooterIsControllingIntakeConveyor = true;
        frc::SmartDashboard::PutString("Ball Sensor Blocked", "yes");
        rollerIntakeDelay.Reset();
        rollerIntakeDelay.Start();
    }
    if (IsBallBlockingLowerSensor() != true)
    {
        if (rollerIntakeDelay.Get() > ROLLER_INTAKE_DELAY)
        {
            shooterIsControllingIntakeConveyor = false;
            frc::SmartDashboard::PutString("Ball Sensor Blocked", "no ");
            SetLowerConveyorIntakeMotorSpeed(0);
            SetShooterFeedMotorSpeed(0); // When it dosen't see a ball it should stop moving
            // SetLowerConveyorIntakeMotorSpeed(0.0);
            // SetShooterFeedMotorSpeed(0.0);
        }
    }
}

bool Shooter::IsBallBlockingLowerSensor(void) // true means ball is there
{
    bool isBlocking = !ballInSensor.Get();
    frc::SmartDashboard::PutBoolean("BallInSensor", isBlocking); // Invert ball sensor
    return isBlocking;
}
#endif
