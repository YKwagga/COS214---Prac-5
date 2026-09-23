#ifndef SECURITY_TEAM_H
#define SECURITY_TEAM_H

#include "ResponseComponent.h"
#include <iostream>

class SecurityTeam : public ResponseComponent {
public:
    SecurityTeam(int id, ResponseMediator* mediator)
        : ResponseComponent(id, "SecurityTeam", mediator) {}

    void receiveInstruction(const std::string& instruction) override {
        std::cout << "[" << name << " #" << id << "] "
                  << instruction << "\n";
    }

    void reportAreaSecured(int incidentId) {
        setStatus(ResponseStatus::OnScene);
        notifyMediator(ComponentEventType::AreaSecured,
                       "Area secured by " + name, incidentId);
    }

    void requestBackup(int incidentId) {
        notifyMediator(ComponentEventType::NeedBackup,
                       name + " requests backup", incidentId);
    }

    void reportUnitArrived(int incidentId) {
        setStatus(ResponseStatus::OnScene);
        notifyMediator(ComponentEventType::UnitArrived,
                       name + " arrived on scene", incidentId);
    }

    void reportTaskComplete(int incidentId) {
        setStatus(ResponseStatus::Available);
        notifyMediator(ComponentEventType::TaskComplete,
                       name + " task complete", incidentId);
    }

    void reportDispatch(int incidentId) {
        setStatus(ResponseStatus::Dispatched);
        std::cout << "[" << name << " #" << id
                << "] Dispatched to incident " << incidentId << "\n";
        notifyMediator(ComponentEventType::UnitArrived,
                    name + " dispatched", incidentId);
    }

    void assistEvacuation(int incidentId) {
        setStatus(ResponseStatus::Busy);
        std::cout << "[" << name << " #" << id
                  << "] Assisting evacuation for incident "
                  << incidentId << "\n";
        notifyMediator(ComponentEventType::TaskComplete,
                       name + " assisting evacuation", incidentId);
    }

    void standDownEvacuation(int incidentId) {
        setStatus(ResponseStatus::Available);
        std::cout << "[" << name << " #" << id
                  << "] Stand down evacuation support for incident "
                  << incidentId << "\n";
        notifyMediator(ComponentEventType::TaskComplete,
                       name + " stood down from evacuation", incidentId);
    }
};

#endif