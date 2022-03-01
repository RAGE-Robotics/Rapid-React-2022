#include "Shooter.h"

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
    kF = 0;       // 0.1
    kP = 0.25;    // 0.15
    kI = 0.00008; // 0.0001
    kD = 0.01;

    //frc::SmartDashboard::PutNumber("kF", kF);
    //frc::SmartDashboard::PutNumber("kP", kP);
    //frc::SmartDashboard::PutNumber("kI", kI);
    //frc::SmartDashboard::PutNumber("kD", kD);

    // for velocity feedback
    shooterMotorTop.Config_kF(0, kF, kTimeoutMs);
    shooterMotorTop.Config_kP(0, kP, kTimeoutMs); // Accelerates at .5 try 0.1
    shooterMotorTop.Config_kI(0, kI, kTimeoutMs);
    shooterMotorTop.Config_kD(0, kD, kTimeoutMs);

    shooterMotorBottom.Config_kF(0, kF, kTimeoutMs);
    shooterMotorBottom.Config_kP(0, kP, kTimeoutMs); // Accelerates at .5 try 0.1
    shooterMotorBottom.Config_kI(0, kI, kTimeoutMs);
    shooterMotorBottom.Config_kD(0, kD, kTimeoutMs);

    //RaiseShooterHood(true); // Hood ready in raised positoin
    // shooterLeadScrewMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 30);
}

double Shooter::SetShooterSpeedTopVoltage(double voltage)
{
    // ctre::phoenix::motorcontrol::can::WPI_TalonFX
    shooterMotorTop.Set(ControlMode::PercentOutput, voltage);

    return 0;
}
double Shooter::SetShooterSpeedBottomVoltage(double voltage)
{
    // ctre::phoenix::motorcontrol::can::WPI_TalonFX
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
    // double newF = frc::SmartDashboard::GetNumber("kF", 0);
    // double newP = frc::SmartDashboard::GetNumber("kP", 0);
    // double newI = frc::SmartDashboard::GetNumber("kI", 0);
    // double newD = frc::SmartDashboard::GetNumber("kD", 0);
    //int newShooterSpeedVelocity = frc::SmartDashboard::GetNumber("Set Shooter Speed", 0);
    // frc::SmartDashboard::PutNumber("newF", newF);
    // for velocity feedback
    // if (newF != kF)
    // {
    //     kF = newF;
    //     shooterMotor.Config_kF(0, kF, kTimeoutMs);
    // }
    // if (newP != kP)
    // {
    //     kP = newP;
    //     shooterMotor.Config_kP(0, kP, kTimeoutMs);
    // } // Accelerates at .5 try 0.1
    // if (newI != kI)
    // {
    //     kI = newI;
    //     shooterMotor.Config_kI(0, kI, kTimeoutMs);
    // }
    // if (newD != kD)
    // {
    //     kD = newD;
    //     shooterMotor.Config_kD(0, kD, kTimeoutMs);
    // }
    // if (newShooterSpeedVelocity != shooterSpeedVelocity)
    // {
    //     shooterSpeedVelocity = newShooterSpeedVelocity;
    // }

    double speedRawUnitsPer100Ms = speed * CONVERT_RPM_TO_VELOCITY_TICKS;
    shooterMotorTop.Set(ControlMode::Velocity, speedRawUnitsPer100Ms);
    shooterMotorBottom.Set(ControlMode::Velocity, speedRawUnitsPer100Ms);

    return 0;
}

double Shooter::SetShooterSpeedTopVelocityRPM(double speed)
{
    if (speed == 0.0)
    {
        SetShooterSpeedTopVoltage(0.0);
        return 0;
    }
    // double newF = frc::SmartDashboard::GetNumber("kF", 0);
    // double newP = frc::SmartDashboard::GetNumber("kP", 0);
    // double newI = frc::SmartDashboard::GetNumber("kI", 0);
    // double newD = frc::SmartDashboard::GetNumber("kD", 0);
    //int newShooterSpeedVelocity = frc::SmartDashboard::GetNumber("Set Shooter Speed", 0);
    // frc::SmartDashboard::PutNumber("newF", newF);
    // for velocity feedback
    // if (newF != kF)
    // {
    //     kF = newF;
    //     shooterMotor.Config_kF(0, kF, kTimeoutMs);
    // }
    // if (newP != kP)
    // {
    //     kP = newP;
    //     shooterMotor.Config_kP(0, kP, kTimeoutMs);
    // } // Accelerates at .5 try 0.1
    // if (newI != kI)
    // {
    //     kI = newI;
    //     shooterMotor.Config_kI(0, kI, kTimeoutMs);
    // }
    // if (newD != kD)
    // {
    //     kD = newD;
    //     shooterMotor.Config_kD(0, kD, kTimeoutMs);
    // }
    // if (newShooterSpeedVelocity != shooterSpeedVelocity)
    // {
    //     shooterSpeedVelocity = newShooterSpeedVelocity;
    // }

    double speedRawUnitsPer100Ms = speed * CONVERT_RPM_TO_VELOCITY_TICKS;
    shooterMotorTop.Set(ControlMode::Velocity, speedRawUnitsPer100Ms);
    shooterMotorBottom.Set(ControlMode::Velocity, speedRawUnitsPer100Ms);

    return 0;
}

double Shooter::GetShooterSpeedRPM()
{
    int rawSensorVelocityTop = shooterMotorTop.GetSelectedSensorVelocity(0);
//    int rawSensorVelocityBottom = shooterMotorBottom.GetSelectedSensorVelocity(0);

    //frc::SmartDashboard::PutNumber("shooterVelocityRAW: ", rawSensorVelocity);
    double shooterVelocityRPM = double(rawSensorVelocityTop) * CONVERT_VELOCITY_TICKS_TO_RPM;
    //frc::SmartDashboard::PutNumber("shooterVelocityRPM: ", shooterVelocityRPM);
    return shooterVelocityRPM;
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

#if 0
double Shooter::SetShooterAngle(double angle)
{
    // Angle in raw count units
    return 0;
}

double Shooter::GetShooterAngle(void)
{
    // int angleCount = shooterLeadScrewMotor.GetSelectedSensorPosition(0);
    // double angle = double(angleCount) * 1.0;
    // frc::SmartDashboard::PutNumber("shooter angle count raw", angleCount);
    //  return angle;
    return 0.0;
}

void Shooter::SetIntakeRollerSpeed(double rollerSpeed)
{
    double upperRollerSpeed = rollerSpeed;
    // intakeRollerAndLowerConveyorMotor.Set(rollerSpeed);
    upperIntakeMotor.Set(upperRollerSpeed);
    // IsBallBlockingLowerSensor();
}

void Shooter::SetShooterFeedMotorSpeed(double feedmotorspeed)
{
    shooterFeedMotor.Set(feedmotorspeed);
}

void Shooter::SetLowerConveyorIntakeMotorSpeed(double motorSpeed)
{
    SqueezeConveyor(false);
    // SetIntakeRollerSpeed(motorSpeed);
    lowerConveyorMotor.Set(motorSpeed);
}

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