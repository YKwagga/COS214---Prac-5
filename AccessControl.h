#ifndef ACCESS_CONTROL_H
#define ACCESS_CONTROL_H

#include "ResponseComponent.h"
#include <iostream>

class AccessControl : public ResponseComponent {
public:
    AccessControl(int id, ResponseMediator* mediator)
        : ResponseComponent(id, "AccessControl", mediator) {}

    void receiveInstruction(const std::string& instruction) override {
        std::cout << "[" << name << " #" << id << "] "
                  << instruction << "\n";
    }

    void unlockArea(int areaId, int incidentId) {
        std::cout << "[" << name << " #" << id
                  << "] Unlocking area " << areaId << "\n";
        notifyMediator(ComponentEventType::TaskComplete,
                       name + " unlocked area "
                       + std::to_string(areaId), incidentId);
    }

    void lockArea(int areaId, int incidentId) {
        std::cout << "[" << name << " #" << id
                  << "] Locking area " << areaId << "\n";
        notifyMediator(ComponentEventType::TaskComplete,
                       name + " locked area "
                       + std::to_string(areaId), incidentId);
    }

    void reportTaskComplete(int incidentId) {
        setStatus(ResponseStatus::Available);
        notifyMediator(ComponentEventType::TaskComplete,
                       name + " task complete", incidentId);
    }
};

#endif