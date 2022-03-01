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
    SHOOT_ON,
    SHOOT_OFF,
    INTAKE_ON,
    INTAKE_OFF,
    RANGE, // For camera code, potentially?
    INCREASE_SHOOTER_ANGLE,
    DECREASE_SHOOTER_ANGLE
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
const std::vector<AutoAction> k_forwardBack{
    AutoAction(
        ActionType::DRIVE_FORWARD,
        3.0f, // Duration
        1.0f), // Delay
    AutoAction(
        ActionType::DRIVE_BACKWARD,
        3.0f, // Duration
        1.0f)}; // Delay

const std::vector<AutoAction> k_doNothing{
    AutoAction(
        ActionType::NOTHING,
        94823490239.0f, // 3006 years. If a competition lasts longer than that, we have an issue
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

    void start(); // Reverts to the first action within the list and resets the timer
    void setActions(std::vector<AutoAction> p_actionList);
    ActionType getCurrentAction(); // Returns an enum ActionType, for use in a switch statement

private:
    // A timer representing progress through the current timer
    // Resets and increments index after the action is complete
    frc::Timer m_currentActionTimer; 

    unsigned int currActionIndex = 0;

    // List of actions currently assigned to the controller, can change
    std::vector<AutoAction> m_actions; 
};
