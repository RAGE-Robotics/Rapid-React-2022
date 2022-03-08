#include "Robot.h"
#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit()
{
    m_chooser.SetDefaultOption("Do nothing", "donothing");
    m_chooser.AddOption("Forwards then back", "forwardback");
    frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

    compressor.EnableAnalog(kCompressorMinPressure, kCompressorMaxPressure);

    // m_limelightLEDChooser.SetDefaultOption("Default LED Behavior", "default");
    // m_limelightLEDChooser.AddOption("LEDs Off", "ledsoff");
    // m_limelightLEDChooser.AddOption("LEDs On", "ledson");
    // m_limelightLEDChooser.AddOption("LEDs Blinking", "ledsblinking");
    // frc::SmartDashboard::PutData("Limelight LED Modes", &m_limelightLEDChooser);

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
    m_autoSelected = m_chooser.GetSelected();
    m_limelightLEDModeSelected = m_limelightLEDChooser.GetSelected();

    autoController.start();

    if (m_autoSelected == "forwardback")
    {
        autoController.setActions(k_forwardBack); // k_forwardBack is defined in Auto.h
    }
    else if (m_autoSelected == "donothing")
    {
        autoController.setActions(k_doNothing); // k_doNothing is defined in Auto.h
    }
}

void Robot::AutonomousPeriodic()
{
    leds.displayRainbow();

    if (m_autoSelected == kAutoNameCustom)
    {
        // Custom Auto goes here
    }
    else
    {
        // Default Auto goes here
    }

    ActionType currentAction = autoController.getCurrentAction();

    switch (currentAction)
    {
    case ActionType::DRIVE_FORWARD:
        // wpi::outs() << "Driving Forwards!\n";
        base.TankDrive(0.2, 0.2);
        break;
    case ActionType::DRIVE_BACKWARD:
        base.TankDrive(-0.2, -0.2);
        // wpi::outs() << "Driving Backwards!\n";
        break;
    case ActionType::NOTHING:
        base.TankDrive(0.0, 0.0);
        // wpi::outs() << "Doing nothing...\n";
        break;
    default:
        break;
    }
}

void Robot::TeleopInit()
{
    m_limelightLEDModeSelected = m_limelightLEDChooser.GetSelected();

    leds.displayTeamColor();
}

void Robot::TeleopPeriodic()
{
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

    if (operatorLeftStick.GetRawButton(DEPLOY_INTAKE_BUTTON))
    {
        base.DeployIntake();
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
    if (operatorRightStick.GetRawButtonPressed(SHOOTER_ANGLE_INCREASE_BUTTON))
    {
        //shooter.IncreaseShooterAngle();
    }
    if (operatorRightStick.GetRawButtonPressed(SHOOTER_ANGLE_DECREASE_BUTTON))
    {
        //shooter.DecreaseShooterAngle();
    }

    ///////////////////////////////////////////////////////
    // LEDs
    if (m_gameTimer.HasElapsed((units::second_t)120.0))
    {
        leds.displayFallingLights();
    }

    ///////////////////////////////////////////////////////
    // Camera operation
    // if (m_limelightLEDModeSelected == "default")
    // {
    //     limelightCamera.setLEDsToDefault();
    // }
    // else if (m_limelightLEDModeSelected == "ledsoff")
    // {
    //     limelightCamera.turnOffLEDs();
    // }
    // else if (m_limelightLEDModeSelected == "ledson")
    // {
    //     limelightCamera.turnOnLEDs();
    // }
    // else if (m_limelightLEDModeSelected == "ledsblinking")
    // {
    //     limelightCamera.blinkLEDs();
    // }

    // if (limelightCamera.hasValidTarget() && (rand() % 10 == 0))
    // {
    //   std::cout << "Camera Distance to Target: " << limelightCamera.getDistanceToTarget() << std::endl;
    // }
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
