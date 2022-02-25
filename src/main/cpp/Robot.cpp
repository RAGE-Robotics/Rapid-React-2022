#include "Robot.h"
#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit()
{
    m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
    m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
    // frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

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
 * <p> This runs after the mode specific periodic functions, but before
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
    // m_limelightLEDModeSelected = m_limelightLEDChooser.GetSelected();

    // m_autoSelected = SmartDashboard::GetString("Auto Selector",
    //     kAutoNameDefault);
    // std::cout << "Auto selected: " << m_autoSelected << std::endl;
    // std::cout << "Limelight LED Mode Selected: " << m_limelightLEDModeSelected << std::endl;

    if (m_autoSelected == kAutoNameCustom)
    {
        // Custom Auto goes here
    }
    else
    {
        // Default Auto goes here
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
}

void Robot::TeleopInit()
{
    // m_limelightLEDModeSelected = m_limelightLEDChooser.GetSelected();
    //  std::cout << "Limelight LED Mode Selected: " << m_limelightLEDModeSelected << std::endl;

    leds.displayTeamColor();
    wpi::outs() << "asjhdssx\n";
}

void Robot::TeleopPeriodic()
{
#if 0
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
      limelightCamera.turnOffLEDs();
    }
#endif
    // if (limelightCamera.hasValidTarget() && (rand() % 10 == 0))
    // {
    //   std::cout << "Camera Distance to Target: " << limelightCamera.getDistanceToTarget() << std::endl;
    // }

    // working code, need to comment to debug

    base.TankDrive(driverLeftStick.GetY(), driverRightStick.GetY());
    if (m_gameTimer.HasElapsed((units::second_t)120.0))
    {
        leds.displayFallingLights();
    }
    if (driverLeftStick.GetRawButton(HIGH_GEAR_BUTTON))
    {
        gearSolenoid.Set(true);
    }
    if (driverRightStick.GetRawButton(LOW_GEAR_BUTTON))
    {
        gearSolenoid.Set(false);
    }

    if (operatorRightStick.GetRawButtonPressed(SHOOT_BUTTON))
    {
        shooter.Shoot(true);
    }
    if (operatorRightStick.GetRawButtonReleased(SHOOT_BUTTON))
    {
        shooter.Shoot(false);
    }
    if (operatorLeftStick.GetRawButton(INTAKE_ROLLER_ON_BUTTON))
    {
        base.IntakeMotor(true);
    }
    else
    {
        base.IntakeMotor(false);
    }
    if (operatorLeftStick.GetRawButton(CONVEYOR_ON_BUTTON))
    {
        if (operatorLeftStick.GetRawButton(CONVEYOR_DIRECTION_BUTTON))
        {
            base.ConveyorMotor(true, false);
        }
        else
        {
            base.ConveyorMotor(true, true);
        }
    }
    else
    {
        base.ConveyorMotor(false, 0);
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
