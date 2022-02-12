#include "Camera.h"
//#if 0
double Camera::getHorizontalAngle()
{
    return m_table->GetNumber("tx", -999.0);
}

double Camera::getVerticalAngle()
{
    return m_table->GetNumber("ty", -999.0);
}

bool Camera::hasValidTarget()
{
    return (bool)m_table->GetNumber("tv", 0.0);
}

float Camera::getDistanceToTarget()
{
    // Trigonometry. Woo.
    return (targetHeight - cameraHeight) / (float)tan(cameraAngle + getVerticalAngle() * DEG_TO_RAD);
}
void Camera::setLEDsToDefault()
{
    m_table->PutNumber("ledMode", 0);
}
void Camera::turnOffLEDs()
{
    m_table->PutNumber("ledMode", 1);
}
void Camera::blinkLEDs()
{
    m_table->PutNumber("ledMode", 2);
}
void Camera::turnOnLEDs()
{
    m_table->PutNumber("ledMode", 3);
}
//#endif
