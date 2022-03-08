#include "Shooter.h"
//#include <frc/smartdashboard/SmartDashboard.h>

Shooter::Shooter()
{
    shooterMotorTop.ConfigFactoryDefault();
    shooterMotorTop.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::IntegratedSensor, 0, 0);
    shooterMotorTop.SetSensorPhase(true);

    shooterMotorTop.ConfigClosedloopRamp(1.0); // seconds from 0 to full speed;

    shooterMotorBottom.ConfigFactoryDefault();
    shooterMotorBottom.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::IntegratedSensor, 0, 0);
    shooterMotorBottom.SetSensorPhase(true);

    shooterMotorBottom.ConfigClosedloopRamp(1.0); // seconds from 0 to full speed;

    kTimeoutMs = 0;

    top_kF = 0;       // 0.1
    top_kP = 0.25;    // 0.15
    top_kI = 0.00008; // 0.0001
    top_kD = 0.01;

    bot_kF = 0;       // 0.1
    bot_kP = 0.25;    // 0.15
    bot_kI = 0.00008; // 0.0001
    bot_kD = 0.01;

    // frc::SmartDashboard::PutNumber("Top kF", top_kF);
    // frc::SmartDashboard::PutNumber("Top kP", top_kP);
    // frc::SmartDashboard::PutNumber("Top kI", top_kI);
    // frc::SmartDashboard::PutNumber("Top kD", top_kD);

    // frc::SmartDashboard::PutNumber("Bot kF", bot_kF);
    // frc::SmartDashboard::PutNumber("Bot kP", bot_kP);
    // frc::SmartDashboard::PutNumber("Bot kI", bot_kI);
    // frc::SmartDashboard::PutNumber("Bot kD", bot_kD);

    // for velocity feedback
    shooterMotorTop.Config_kF(0, top_kF, kTimeoutMs);
    shooterMotorTop.Config_kP(0, top_kP, kTimeoutMs); // Accelerates at .5 try 0.1
    shooterMotorTop.Config_kI(0, top_kI, kTimeoutMs);
    shooterMotorTop.Config_kD(0, top_kD, kTimeoutMs);

    shooterMotorBottom.Config_kF(0, bot_kF, kTimeoutMs);
    shooterMotorBottom.Config_kP(0, bot_kP, kTimeoutMs); // Accelerates at .5 try 0.1
    shooterMotorBottom.Config_kI(0, bot_kI, kTimeoutMs);
    shooterMotorBottom.Config_kD(0, bot_kD, kTimeoutMs);

    // RaiseShooterHood(true); // Hood ready in raised positoin
    //  shooterLeadScrewMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 30);
}

double Shooter::SetShooterSpeedTopVoltage(double voltage)
{
    //ctre::phoenix::motorcontrol::can::WPI_TalonFX
    shooterMotorTop.Set(ControlMode::PercentOutput, voltage);

    return 0;
}
double Shooter::SetShooterSpeedBottomVoltage(double voltage)
{
    //ctre::phoenix::motorcontrol::can::WPI_TalonFX
    shooterMotorBottom.Set(ControlMode::PercentOutput, voltage);

    return 0;
}

double Shooter::SetShooterSpeedBottomVelocityRPM(double speed)
{
    if (speed == 0.0)
    {
        SetShooterSpeedBottomVoltage(0.0);
        return 0;
    }
#if 0
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
    // if (newShooterSpeedVelocity != shooterSpeedBottomVelocity)
    // {
    //     shooterSpeedBottomVelocity = newShooterSpeedVelocity;
    // }
#endif
    double speedRawUnitsPer100Ms = speed * CONVERT_RPM_TO_VELOCITY_TICKS;
    shooterMotorBottom.Set(ControlMode::Velocity, speedRawUnitsPer100Ms);

    return 0;
}

double Shooter::SetShooterSpeedTopVelocityRPM(double speed)
{
    speed = -speed;

    if (speed == 0.0)
    {
        SetShooterSpeedTopVoltage(0.0);
        return 0;
    }
#if 0
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
    // if (newShooterSpeedVelocity != shooterSpeedTopVelocity)
    // {
    //     shooterSpeedTopVelocity = newShooterSpeedVelocity;
    // }
#endif

    double speedRawUnitsPer100Ms = speed * CONVERT_RPM_TO_VELOCITY_TICKS;
    shooterMotorTop.Set(ControlMode::Velocity, speedRawUnitsPer100Ms);

    return 0;
}

// double Shooter::GetShooterSpeedTopRPM()
// {
//     // int rawSensorVelocityTop = shooterMotorTop.GetSelectedSensorVelocity(0);

//     // frc::SmartDashboard::PutNumber("shooterVelocityTopRAW: ", rawSensorVelocityTop);

//     // double shooterVelocityTopRPM = double(rawSensorVelocityTop) * CONVERT_VELOCITY_TICKS_TO_RPM;

//     // frc::SmartDashboard::PutNumber("shooterVelocityTopRPM: ", shooterVelocityTopRPM);

//     return shooterVelocityTopRPM;
// }

// double Shooter::GetShooterSpeedBottomRPM()
// {
//     // int rawSensorVelocityBottom = shooterMotorBottom.GetSelectedSensorVelocity(0);

//     // frc::SmartDashboard::PutNumber("shooterVelocityBottomRAW: ", rawSensorVelocityBottom);

//     // double shooterVelocityBottomRPM = double(rawSensorVelocityBottom) * CONVERT_VELOCITY_TICKS_TO_RPM;

//     // frc::SmartDashboard::PutNumber("shooterVelocityBottomRPM: ", shooterVelocityBottomRPM);

//     return shooterVelocityBottomRPM;
// }

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

void Shooter::IncreaseTargetAngle(void)
{
    targetShooterAngle += DEG_TO_RAD * 15.0;
}

void Shooter::DecreaseTargetAngle(void)
{
    targetShooterAngle -= DEG_TO_RAD * 15.0;
}

void Shooter::AimShooter(double radians)
{

    double rotations = (currentShooterAngle - targetShooterAngle) * ANGLE_TO_ROTATIONS;
    angleMotor.Set(ControlMode::Position, rotations);
    currentShooterAngle = targetShooterAngle;
}


double Shooter::GetShooterAngle(void)
{
    int angleCount = angleMotor.GetSelectedSensorPosition(0);
    currentShooterAngle = double(angleCount) / ROTATION_CONSTANT;
    //frc::SmartDashboard::PutNumber("shooter angle count raw", angleCount);
    return currentShooterAngle;
}

void Shooter::SetIntakeRollerSpeed(double rollerSpeed)
{
    double upperRollerSpeed = rollerSpeed;
    // intakeRollerAndLowerConveyorMotor.Set(rollerSpeed);
    intakeRollerMotor.Set(upperRollerSpeed);
    // IsBallBlockingLowerSensor();
}

void Shooter::SetShooterFeedMotorSpeed(double feedmotorspeed)
{
    shooterFeedMotor.Set(feedmotorspeed);
}

void Shooter::SetConveyorIntakeMotorSpeed(double motorSpeed)
{
    // SqueezeConveyor(false);
    //  SetIntakeRollerSpeed(motorSpeed);
    conveyorMotor.Set(motorSpeed);
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