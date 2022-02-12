// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "LEDs.h"
#include "Base.h"
#include "Camera.h"

class Robot : public frc::TimedRobot
{
public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;
    void TestInit() override;
    void TestPeriodic() override;
    void SimulationInit() override;
    void SimulationPeriodic() override;

private:
    frc::Timer m_gameTimer;
    frc::SendableChooser<std::string> m_chooser;
    const std::string kAutoNameDefault = "Default";
    const std::string kAutoNameCustom = "My Auto";
    std::string m_autoSelected;

    frc::SendableChooser<std::string> m_limelightLEDChooser;
    std::string m_limelightLEDModeSelected;

    // frc::Joystick m_testStick{TEST_JOYSTICK};
    frc::Joystick driverLeftStick{LEFT_DRIVER_JOYSTICK_USB};
    frc::Joystick driverRightStick{RIGHT_DRIVER_JOYSTICK_USB};
    frc::Joystick operatorLeftStick{LEFT_OPERATOR_JOYSTICK_USB};
    frc::Joystick operatorRightStick{RIGHT_OPERATOR_JOYSTICK_USB};
    LEDs leds;
    Base base; // Based
    Camera limelightCamera;

    frc::Solenoid gearSolenoid{frc::PneumaticsModuleType::CTREPCM, SHIFT_GEAR_SOLENOID};
};
