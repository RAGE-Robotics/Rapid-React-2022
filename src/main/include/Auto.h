#pragma once

#include "Rage2022.h"
#include <frc/TimedRobot.h>
#include <vector>

enum class ActionType
{
    NOTHING,
    DRIVE_FORWARD,
    DRIVE_BACKWARD,
    TURN_LEFT,
    TURN_RIGHT,
    SHOOT,
    INTAKE,
    RANGE,
    SET_ANGLE
};

struct AutoAction
{
    AutoAction(ActionType p_type, float p_duration, float p_delay)
    {
        type = p_type;
        duration = p_duration;
        delay = p_delay;
    };

    enum ActionType type;
    float duration;
    float delay;
};

// DEFINED ACTION LISTS (Should probably be moved)==================================================
const std::vector<AutoAction> k_testActions{
    AutoAction(
        ActionType::DRIVE_FORWARD,
        3.0f,
        1.0f),
    AutoAction(
        ActionType::DRIVE_BACKWARD,
        3.0f,
        1.0f)};

// ================================================================================================
class AutoController
{
public:
    AutoController() {};
    AutoController(std::vector<AutoAction> p_actionList)
    {
        m_actions = p_actionList;
    };

    void start();
    void setActions(std::vector<AutoAction> p_actionList);
    ActionType getCurrentAction();

private:
    frc::Timer m_currentActionTimer;

    unsigned int currActionIndex = 0;

    std::vector<AutoAction> m_actions;
};
