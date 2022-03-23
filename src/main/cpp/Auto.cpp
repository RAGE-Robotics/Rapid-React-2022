#include "Auto.h"

void AutoController::start() {
    m_currentActionTimer.Reset();
    m_currentActionTimer.Start();
    currActionIndex = 0;
}

ActionType AutoController::getCurrentAction() {
    if (currActionIndex > m_actions.size()) return ActionType::NOTHING; // If at the end of the action list, do nothing.

    float actionProgress = (float)m_currentActionTimer.Get();
    AutoAction& currentAction = m_actions[currActionIndex];
    
    if (actionProgress > currentAction.duration + currentAction.delay) {
        currActionIndex++;
        m_currentActionTimer.Reset();
    }
    if (actionProgress < currentAction.duration) {
       return currentAction.type;
    }
    //wpi::outs() << std::to_string(m_actions.size()) << "\n";

    return ActionType::NOTHING; // Will yell at us if we dont put this
}

void AutoController::setActions(std::vector<AutoAction> p_actionList) {
    m_actions = p_actionList;
}
