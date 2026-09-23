#ifndef EMERGENCY_RESPONSE_MEDIATOR_H
#define EMERGENCY_RESPONSE_MEDIATOR_H

#include "ResponseMediator.h"
#include "ResponseComponent.h"
#include "IncidentObserver.h"
#include "Incident.h"
#include <iostream>
#include "SecurityTeam.h"
#include "MedicalTeam.h"
#include "AccessControl.h"
#include "AlertService.h"

class EmergencyResponseMediator : public ResponseMediator,
                                 public IncidentObserver {
public:
    EmergencyResponseMediator()
        : security(nullptr), medical(nullptr),
          alert(nullptr), access(nullptr) {}

    void setColleagues(SecurityTeam* security,
                       MedicalTeam* medical,
                       AlertService* alert,
                       AccessControl* access) {
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
                    medical->reportUnitArrived(event.incidentId);
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

    //Command functions
    void dispatchUnit(int incidentId, ResponseUnitType unit) {
        std::cout << "[Mediator/Receiver] dispatchUnit: "
                  << toString(unit) << " -> incident "
                  << incidentId << "\n";

        switch (unit) {
            case ResponseUnitType::Security:
                if (security) security->reportDispatch(incidentId);
                break;
            case ResponseUnitType::Medical:
                if (medical)  medical->reportDispatch(incidentId);
                break;
            case ResponseUnitType::Alert:
                if (alert)    alert->reportDispatch(incidentId);
                break;
            case ResponseUnitType::Access:
                if (access)   access->reportDispatch(incidentId);
                break;
        }
    }

    void cancelDispatch(int incidentId, ResponseUnitType unit) {
        std::cout << "[Mediator/Receiver] cancelDispatch: "
                  << toString(unit) << " for incident "
                  << incidentId << "\n";

        switch (unit) {
            case ResponseUnitType::Security:
                if (security) security->reportTaskComplete(incidentId);
                break;
            case ResponseUnitType::Medical:
                if (medical)  medical->reportTaskComplete(incidentId);
                break;
            case ResponseUnitType::Alert:
                if (alert)    alert->reportTaskComplete(incidentId);
                break;
            case ResponseUnitType::Access:
                if (access)   access->reportTaskComplete(incidentId);
                break;
        }
    }

    void secureArea(int areaId, int incidentId) {
        std::cout << "[Mediator/Receiver] secureArea: area " << areaId
                  << " for incident " << incidentId << "\n";

        if (security) security->reportAreaSecured(incidentId);
        if (access)   access->lockArea(areaId, incidentId);
    }

    void cancelSecureArea(int areaId, int incidentId) {
        std::cout << "[Mediator/Receiver] cancelSecureArea: area " << areaId
                  << " for incident " << incidentId << "\n";

        if (access)   access->unlockArea(areaId, incidentId);
        if (security) security->reportTaskComplete(incidentId);
    }

    void issueEvacuation(const std::string& message, int incidentId) {
        std::cout << "[Mediator/Receiver] issueEvacuation for incident "
                  << incidentId << ": " << message << "\n";

        if (alert)    alert->broadcast(message, incidentId);
        if (security) security->assistEvacuation(incidentId);
        if (access)   access->openEvacuationRoutes(incidentId);
    }

    void cancelEvacuation(int incidentId) {
        std::cout << "[Mediator/Receiver] cancelEvacuation for incident "
                  << incidentId << "\n";

        if (alert)    alert->broadcast("All clear", incidentId);
        if (security) security->standDownEvacuation(incidentId);
        if (access)   access->restoreNormalAccess(incidentId);
    }

    
private:
    void instructAll(const std::string& instruction) {
        if (security) security->receiveInstruction(instruction);
        if (medical) medical->receiveInstruction(instruction);
        if (alert) alert->receiveInstruction(instruction);
        if (access) access->receiveInstruction(instruction);
    }

        ResponseComponent* findUnit(const std::string& unitName) {
        if (security &&
            (unitName == security->getName() ||
             unitName == "Security" ||
             unitName == "SecurityTeam")) {
            return security;
        }

        if (medical &&
            (unitName == medical->getName() ||
             unitName == "Medical" ||
             unitName == "MedicalTeam")) {
            return medical;
        }

        if (alert &&
            (unitName == alert->getName() ||
             unitName == "Alert" ||
             unitName == "AlertService")) {
            return alert;
        }

        if (access &&
            (unitName == access->getName() ||
             unitName == "Access" ||
             unitName == "AccessControl")) {
            return access;
        }

        return nullptr;
    }
    SecurityTeam* security;
    MedicalTeam* medical;
    AlertService* alert;
    AccessControl* access;
};

#endif
