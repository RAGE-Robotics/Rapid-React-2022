#pragma once

#include "Rage2022.h"
#include <frc/TimedRobot.h>
#include <vector>

enum class ActionType
{
    NOTHING, // For now, the nothing mode stops the base motors
    SHIFT_HIGH,
    SHIFT_LOW,
    DRIVE_FORWARD,
    DRIVE_BACKWARD,
    DEPLOY_INTAKE,
    RELEASE_INTAKE,
    AIM_SHOOTER,
    TURN_LEFT,
    TURN_RIGHT,
    SHOOT_ON,
    SHOOT_OFF,
    INTAKE_ON,
    INTAKE_OFF,
    CONVEYOR_ON,
    CONVEYOR_OFF,
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
const std::vector<AutoAction> k_leaveTarmac{
    AutoAction(
        ActionType::SHIFT_HIGH,
        0.5f,  // Duration
        0.1f), // Delay
    AutoAction(
        ActionType::AIM_SHOOTER,
        1.0f,  // Duration
        1.0f), // Delay
    AutoAction(
        ActionType::DRIVE_FORWARD,
        2.0f, // Duration
        1.0f) // Delay
};

const std::vector<AutoAction> k_leaveTarmacPickUpBall{
    AutoAction(
        ActionType::SHIFT_HIGH,
        0.5f,  // Duration
        2.0f), // Delay
    AutoAction(
        ActionType::DEPLOY_INTAKE,
        1.0f,
        0.0f),
    AutoAction(
        ActionType::RELEASE_INTAKE,
        0.5f,
        0.0f),
    AutoAction(
        ActionType::AIM_SHOOTER,
        1.0f,  // Duration
        0.0f), // Delay
    AutoAction(
        ActionType::INTAKE_ON,
        0.5f,
        0.5f),
    AutoAction(
        ActionType::DRIVE_FORWARD,
        2.0f, // Duration
        1.0f), // Delay
    AutoAction(
        ActionType::INTAKE_OFF,
        0.1f, // Duration
        0.0f), // Delay
};

const std::vector<AutoAction> k_leaveTarmacAndShoot{
    AutoAction(
        ActionType::DRIVE_FORWARD,
        3.0f,  // Duration
        0.0f), // Delay
    AutoAction(
        ActionType::NOTHING, // Should stop the robot from continuing to drive, functions as DRIVE_OFF
        0.1f,  // Duration
        0.0f), // Delay
    AutoAction(
        ActionType::CONVEYOR_ON,
        0.1f,  // Duration
        0.0f), // Delay
    AutoAction(
        ActionType::SHOOT_ON,
        3.0f,
        0.0f),
    AutoAction(
        ActionType::CONVEYOR_OFF,
        0.1f,
        0.0f),
    AutoAction(
        ActionType::SHOOT_OFF,
        0.1f,
        0.0f)
};

const std::vector<AutoAction> k_forwardBack{
    AutoAction(
        ActionType::DRIVE_FORWARD,
        3.0f,  // Duration
        1.0f), // Delay
    AutoAction(
        ActionType::DRIVE_BACKWARD,
        3.0f, // Duration
        1.0f) // Delay
};

const std::vector<AutoAction> k_doNothing{
    AutoAction(
        ActionType::NOTHING,
        300.0f, // Duration
        1.0f)   // Delay
};

// ================================================================================================
class AutoController
{
public:
    AutoController(){};
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
