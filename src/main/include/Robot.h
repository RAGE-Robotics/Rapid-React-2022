#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "LEDs.h"
#include "Base.h"
#include "Camera.h"
#include "Shooter.h"
#include "Climber.h"
#include "Auto.h"

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

    frc::Joystick driverLeftStick{LEFT_DRIVER_JOYSTICK_USB};
    frc::Joystick driverRightStick{RIGHT_DRIVER_JOYSTICK_USB};
    frc::Joystick operatorLeftStick{LEFT_OPERATOR_JOYSTICK_USB};
    frc::Joystick operatorRightStick{RIGHT_OPERATOR_JOYSTICK_USB};

    AutoController autoController;

    frc::Compressor compressor{frc::PneumaticsModuleType::REVPH};
    const units::pounds_per_square_inch_t kCompressorMinPressure {20};
    const units::pounds_per_square_inch_t kCompressorMaxPressure {120};

    bool shooterHoming {false};
    
    LEDs leds;
    Base base;
    Shooter shooter;
    Climber climber;
    Camera limelightCamera;
};
