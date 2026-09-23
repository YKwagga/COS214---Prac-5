#ifndef ALERT_SERVICE_H
#define ALERT_SERVICE_H

#include "ResponseComponent.h"
#include <iostream>

class AlertService : public ResponseComponent {
public:
    AlertService(int id, ResponseMediator* mediator)
        : ResponseComponent(id, "AlertService", mediator) {}

    void receiveInstruction(const std::string& instruction) override {
        std::cout << "[" << name << " #" << id << "] "
                  << instruction << "\n";
    }

    void broadcast(const std::string& message, int incidentId) {
        std::cout << "[" << name << " #" << id
                  << "] Broadcasting: " << message << "\n";
        notifyMediator(ComponentEventType::TaskComplete,
                       name + " broadcast complete", incidentId);
    }

    void reportTaskComplete(int incidentId) {
        setStatus(ResponseStatus::Available);
        notifyMediator(ComponentEventType::TaskComplete,
                       name + " task complete", incidentId);
    }

    void reportDispatch(int incidentId) {
        setStatus(ResponseStatus::Dispatched);
        std::cout << "[" << name << " #" << id
                << "] Alert service dispatched for incident "
                << incidentId << "\n";
        notifyMediator(ComponentEventType::UnitArrived,
                    name + " dispatched", incidentId);
    }
};

#endif