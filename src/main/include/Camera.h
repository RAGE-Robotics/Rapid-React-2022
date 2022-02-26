#pragma once

#include "Rage2022.h"
// #include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"
//#include "wpi/span.h"

class Camera
{
public:
    Camera()
    {
        m_table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    };

    bool hasValidTarget();
    double getHorizontalAngle();
    double getVerticalAngle();
    float getDistanceToTarget();
    void setLEDsToDefault();
    void turnOffLEDs();
    void turnOnLEDs();
    void blinkLEDs();

private:
    std::shared_ptr<nt::NetworkTable> m_table;
    static constexpr double cameraAngle = 45.0 * DEG_TO_RAD; // 45 degrees
    static constexpr double cameraHeight = 2.0 + 8.0 / 12.0; // 2'8"
    static constexpr double targetHeight = 8.0 + 8.0 / 12.0; // 8'8"
};