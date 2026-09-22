#ifndef EMERGENCY_RESPONSE_MEDIATOR_H
#define EMERGENCY_RESPONSE_MEDIATOR_H

#include "ResponseMediator.h"
#include "ResponseComponent.h"
#include "IncidentObserver.h"
#include "Incident.h"
#include <iostream>

class EmergencyResponseMediator : public ResponseMediator,
                                 public IncidentObserver {
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

    // The mediator is the single operational Observer. It receives incident
    // lifecycle changes, then directs colleagues rather than making every
    // response component observe Incident independently.
    void update(const Incident& incident,
                IncidentUpdateType updateType) override {
        std::cout << "[Mediator observer] Incident " << incident.getId()
                  << " changed to " << incident.getStateName() << "\n";

        if (updateType == IncidentUpdateType::Cancelled) {
            instructAll("Stand down: incident "
                       + std::to_string(incident.getId()) + " was cancelled");
            return;
        }

        if (updateType == IncidentUpdateType::Resolved) {
            instructAll("Stand down and record resolution for incident "
                       + std::to_string(incident.getId()));
            return;
        }

        const std::string incidentId = std::to_string(incident.getId());
        const std::string areaId = std::to_string(incident.getAreaId());
        const std::string state = incident.getStateName();

        if (state == "Dispatched") {
            if (security)
                security->receiveInstruction("Deploy to area " + areaId
                                             + " for incident " + incidentId);
            if (medical)
                medical->receiveInstruction("Stand by for incident " + incidentId);
            if (access)
                access->receiveInstruction("Prepare responder access at area "
                                           + areaId + " for incident " + incidentId);
            if (alert)
                alert->receiveInstruction("Prepare emergency notice for incident "
                                          + incidentId);
        } else if (state == "In Progress") {
            if (access)
                access->receiveInstruction("Restrict public access to area "
                                           + areaId + " for incident " + incidentId);
            if (alert)
                alert->receiveInstruction("Broadcast active-incident notice for "
                                          + incidentId);
        }
    }

private:
    void instructAll(const std::string& instruction) {
        if (security) security->receiveInstruction(instruction);
        if (medical) medical->receiveInstruction(instruction);
        if (alert) alert->receiveInstruction(instruction);
        if (access) access->receiveInstruction(instruction);
    }

    ResponseComponent* security;
    ResponseComponent* medical;
    ResponseComponent* alert;
    ResponseComponent* access;
};

#endif
