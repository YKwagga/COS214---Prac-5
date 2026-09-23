#ifndef SECURE_AREA_COMMAND_H
#define SECURE_AREA_COMMAND_H

#include "Command.h"
#include "EmergencyResponseMediator.h"

class SecureAreaCommand : public Command {
public:
    SecureAreaCommand(EmergencyResponseMediator& receiver,
                      int areaId,
                      int incidentId)
        : receiver(receiver),
          areaId(areaId),
          incidentId(incidentId) {}

    void execute() override {
        receiver.secureArea(areaId, incidentId);
    }

    void undo() override {
        receiver.cancelSecureArea(areaId, incidentId);
    }

    std::string description() const override {
        return "Secure area " + std::to_string(areaId) +
               " for incident " + std::to_string(incidentId);
    }

private:
    EmergencyResponseMediator& receiver;
    int areaId;
    int incidentId;
};

#endif