#ifndef MEDICAL_TEAM_H
#define MEDICAL_TEAM_H

#include "ResponseComponent.h"
#include <iostream>

class MedicalTeam : public ResponseComponent {
public:
    MedicalTeam(int id, ResponseMediator* mediator)
        : ResponseComponent(id, "MedicalTeam", mediator) {}

    void receiveInstruction(const std::string& instruction) override {
        std::cout << "[" << name << " #" << id << "] "
                  << instruction << "\n";
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
};

#endif