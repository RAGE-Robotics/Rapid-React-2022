#include "Robot.h"
#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit()
{

    m_chooser.SetDefaultOption("Leave tarmac", "leavetarmac");
    m_chooser.AddOption("Leave tarmac and pick up ball", "leavetarmacpickupball");
    m_chooser.AddOption("Leave tarmac and shoot", "leavetarmacandshoot");
    m_chooser.AddOption("Forward then back", "forwardback");
    m_chooser.AddOption("Do nothing", "donothing");
    frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

#ifdef ENABLE_COMPRESSOR
    compressor.EnableAnalog(kCompressorMinPressure, kCompressorMaxPressure);
#endif

    m_limelightLEDChooser.SetDefaultOption("Default LED Behavior", "default");
    m_limelightLEDChooser.AddOption("LEDs Off", "ledsoff");
    m_limelightLEDChooser.AddOption("LEDs On", "ledson");
    m_limelightLEDChooser.AddOption("LEDs Blinking", "ledsblinking");
    frc::SmartDashboard::PutData("Limelight LED Modes", &m_limelightLEDChooser);

    leds.displayTeamColor();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * This runs after the mode-specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit()
{
    m_gameTimer.Reset();
    m_gameTimer.Start();
    m_limelightLEDModeSelected = m_limelightLEDChooser.GetSelected();

    autoController.start();

    shooterHoming = true;

    if (m_autoSelected == "leavetarmac")
    {
        autoController.setActions(k_leaveTarmac);
    }
    else if (m_autoSelected == "leavetarmacpickupball")
    {
        autoController.setActions(k_leaveTarmacPickUpBall);
    }
    else if (m_autoSelected == "leavetarmacandshoot")
    {
        autoController.setActions(k_leaveTarmacAndShoot);
    }
    else if (m_autoSelected == "forwardback")
    {
        autoController.setActions(k_forwardBack);
    }
    else if (m_autoSelected == "donothing")
    {
        autoController.setActions(k_doNothing);
    }
}

void Robot::AutonomousPeriodic()
{
    leds.displayRainbow();

    // Home the shooter angle mechanism
    // if (shooterHoming)
    // {
    //     if (!shooter.AngleMotorAtHome())
    //     {
    //         shooter.MoveAngleMotor(SHOOTER_ANGLE_HOME_SPEED, BACKWARD);
    //     }
    //     else
    //     {
    //         shooterHoming = false;
    //         shooter.MoveAngleMotor(0);
    //     }
    // }
    // else
    {
        ActionType currentAction = autoController.getCurrentAction();

        switch (currentAction)
        {
        case ActionType::SHIFT_HIGH:
            base.SetGear(HIGH_GEAR);
            break;
        case ActionType::SHIFT_LOW:
            base.SetGear(LOW_GEAR);
            break;
        case ActionType::DRIVE_FORWARD:
            base.TankDrive(-0.7, -0.7);
            break;
        case ActionType::DRIVE_BACKWARD:
            base.TankDrive(0.7, 0.7);
            break;
        case ActionType::DEPLOY_INTAKE:
            base.DeployIntake();
            break;
        case ActionType::RELEASE_INTAKE:
            base.ReleaseIntake();
            break;
        case ActionType::AIM_SHOOTER:
            shooter.AimShooter(1);
            break;
        case ActionType::SHOOT_ON:
            shooter.SpinUpShooterMotors();
            break;
        case ActionType::SHOOT_OFF:
            shooter.ShutDownShooterMotors();
            break;
        case ActionType::INTAKE_ON:
            base.IntakeMotor(ON);
            break;
        case ActionType::INTAKE_OFF:
            base.IntakeMotor(OFF);
            break;
        case ActionType::CONVEYOR_ON:
            base.ConveyorMotor(ON);
            break;
        case ActionType::CONVEYOR_OFF:
            base.ConveyorMotor(OFF);
            break;
        case ActionType::NOTHING:
            base.TankDrive(0.0, 0.0);
            break;
        default:
            break;
        }
    }
}

void Robot::TeleopInit()
{
    m_limelightLEDModeSelected = m_limelightLEDChooser.GetSelected();

    leds.displayTeamColor();
}

void Robot::TeleopPeriodic()
{
    if ((rand() % 30) == 0)
    {
        wpi::outs() << std::to_string(shooter.GetShooterAngle()) << "\n";
    }

#ifdef ENABLE_STICK_CONTROL
    ///////////////////////////////////////////////////////
    // Base driving
    base.TankDrive(driverLeftStick.GetY(), driverRightStick.GetY());

    ///////////////////////////////////////////////////////
    // Driver shifters
    if (driverLeftStick.GetRawButton(HIGH_GEAR_BUTTON))
    {
        base.SetGear(HIGH_GEAR);
    }
    if (driverRightStick.GetRawButton(LOW_GEAR_BUTTON))
    {
        base.SetGear(LOW_GEAR);
    }

    ///////////////////////////////////////////////////////
    // Operator/Driver ball intake
    if (operatorLeftStick.GetRawButton(INTAKE_ROLLER_ON_BUTTON_OP) ||
        driverRightStick.GetRawButton(INTAKE_ROLLER_ON_BUTTON_DRIVER))
    {
        base.IntakeMotor(ON);
    }
    else
    {
        base.IntakeMotor(OFF);
    }

    if (operatorLeftStick.GetRawButtonPressed(DEPLOY_INTAKE_BUTTON))
    {
        base.DeployIntake();
    }

    if (operatorLeftStick.GetRawButtonReleased(DEPLOY_INTAKE_BUTTON))
    {
        base.ReleaseIntake();
    }

    if (operatorLeftStick.GetRawButton(RETRACT_INTAKE_BUTTON))
    {
        base.RetractIntake();
    }

    ///////////////////////////////////////////////////////
    // Operator conveyor control
    if (operatorLeftStick.GetRawButton(CONVEYOR_FORWARD_BUTTON))
    {
        base.ConveyorMotor(ON, FORWARD);
    }
    else if (operatorLeftStick.GetRawButton(CONVEYOR_BACKWARD_BUTTON))
    {
        base.ConveyorMotor(ON, BACKWARD);
    }
    else
    {
        base.ConveyorMotor(OFF);
    }

    ///////////////////////////////////////////////////////
    // Operator shooting motors
    if (operatorRightStick.GetRawButton(SHOOTER_MOTOR_ON_BUTTON))
    {
        shooter.SpinUpShooterMotors();
    }
    else
    {
        shooter.ShutDownShooterMotors();
    }

    // Update Smart Dashboard when used
    shooter.GetShooterSpeedTopRPM();
    shooter.GetShooterSpeedBottomRPM();

    ///////////////////////////////////////////////////////
    // Operator shoot the ball
    if (operatorRightStick.GetRawButtonPressed(SHOOT_BUTTON))
    {
        shooter.Shoot();
    }

    ///////////////////////////////////////////////////////
    // Operator change shooter angle
    if (operatorRightStick.GetRawButton(SHOOTER_ANGLE_INCREASE_BUTTON))
    {
        shooter.MoveAngleMotor(SHOOTER_ANGLE_MOTOR_SPEED, FORWARD);
        // shooter.IncreaseShooterAngle();
    }
    else if (operatorRightStick.GetRawButton(SHOOTER_ANGLE_DECREASE_BUTTON))
    {
        shooter.MoveAngleMotor(SHOOTER_ANGLE_MOTOR_SPEED, BACKWARD);
        // shooter.DecreaseShooterAngle();
    }
    else
    {
        shooter.MoveAngleMotor(0);
    }

    //////////////////////////////////////////////////////
    // Rotate climber
    if (operatorLeftStick.GetRawButton(CLIMBER_FORWARD_BUTTON_1)) // this could be one line of code:
    {                                                             // climberActive = operatorLeftStick.GetRawButton(CLIMBER_FORWARD_BUTTON_1);
        climberActive = true;
    }
    else
    {
        climberActive = false;
    }

    if (climberActive)
    {
        climber.RotateClimber(operatorRightStick.GetY(), FORWARD);
    }
    else
    {
        climber.RotateClimber(0, FORWARD);
    }
    /////////////////////////////////////////////////////////
    // Climber break piston
    if (driverLeftStick.GetRawButtonPressed(CLIMBER_ENGAGE_BRAKE_BUTTON))
    {
        climber.EngageBrake();
    }
    if (driverRightStick.GetRawButtonPressed(CLIMBER_DISENGAGE_BRAKE_BUTTON))
    {
        climber.DisengageBrake();
    }

#endif
    ///////////////////////////////////////////////////////
    // LEDs
    if (m_gameTimer.HasElapsed((units::second_t)120.0))
    {
        leds.displayFallingLights();
    }

    ///////////////////////////////////////////////////////
    // Camera operation
    if (m_limelightLEDModeSelected == "default")
    {
        limelightCamera.setLEDsToDefault();
    }
    else if (m_limelightLEDModeSelected == "ledsoff")
    {
        limelightCamera.turnOffLEDs();
    }
    else if (m_limelightLEDModeSelected == "ledson")
    {
        limelightCamera.turnOnLEDs();
    }
    else if (m_limelightLEDModeSelected == "ledsblinking")
    {
        limelightCamera.blinkLEDs();
    }

    if (limelightCamera.hasValidTarget() && (rand() % 10 == 0))
    {
        wpi::outs() << "Camera Distance to Target: " << std::to_string(limelightCamera.getDistanceToTarget()) << "\n";
    }
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif
