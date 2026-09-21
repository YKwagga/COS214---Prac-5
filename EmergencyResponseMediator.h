#ifndef EMERGENCY_RESPONSE_MEDIATOR_H
#define EMERGENCY_RESPONSE_MEDIATOR_H

#include "ResponseMediator.h"
#include "ResponseComponent.h"
#include <iostream>

class EmergencyResponseMediator : public ResponseMediator {
public:
    EmergencyResponseMediator()
        : security(nullptr), medical(nullptr),
          alert(nullptr), access(nullptr) {}

    void setColleagues(ResponseComponent* security,
                       ResponseComponent* medical,
                       ResponseComponent* alert,
                       ResponseComponent* access) {
        this->security = security;
        this->medical  = medical;
        this->alert    = alert;
        this->access   = access;
    }

    void notify(ResponseComponent* sender,
                const ComponentEvent& event) override {
        std::cout << "\n[Mediator] Received from "
                  << sender->getName() << ": "
                  << event.message << "\n";

        switch (event.type) {
            case ComponentEventType::AreaSecured:
                if (medical && medical != sender)
                    medical->receiveInstruction(
                        "Area secured. Safe to enter incident "
                        + std::to_string(event.incidentId));
                if (alert && alert != sender)
                    alert->receiveInstruction(
                        "Broadcast area-secured notice for incident "
                        + std::to_string(event.incidentId));
                break;

            case ComponentEventType::NeedBackup:
                if (alert && alert != sender)
                    alert->receiveInstruction(
                        "Broadcast backup request for incident "
                        + std::to_string(event.incidentId));
                if (security && security != sender)
                    security->receiveInstruction(
                        "Prepare to support backup for incident "
                        + std::to_string(event.incidentId));
                break;

            case ComponentEventType::UnitArrived:
                if (alert && alert != sender)
                    alert->receiveInstruction(
                        "Unit on scene for incident "
                        + std::to_string(event.incidentId));
                if (access && access != sender)
                    access->receiveInstruction(
                        "Prepare access for responders at incident "
                        + std::to_string(event.incidentId));
                break;

            case ComponentEventType::TaskComplete:
                if (security && security != sender)
                    security->receiveInstruction(
                        "Task complete elsewhere for incident "
                        + std::to_string(event.incidentId));
                if (medical && medical != sender)
                    medical->receiveInstruction(
                        "Task complete elsewhere for incident "
                        + std::to_string(event.incidentId));
                if (alert && alert != sender)
                    alert->receiveInstruction(
                        "Task complete elsewhere for incident "
                        + std::to_string(event.incidentId));
                if (access && access != sender)
                    access->receiveInstruction(
                        "Task complete elsewhere for incident "
                        + std::to_string(event.incidentId));
                break;
        }
    }

private:
    ResponseComponent* security;
    ResponseComponent* medical;
    ResponseComponent* alert;
    ResponseComponent* access;
};

#endif