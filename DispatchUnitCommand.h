#ifndef DISPATCH_UNIT_COMMAND_H
#define DISPATCH_UNIT_COMMAND_H

#include "Command.h"
#include "EmergencyResponseMediator.h"

#include <string>

class DispatchUnitCommand : public Command {
public:
    DispatchUnitCommand(EmergencyResponseMediator& receiver,
                        ResponseUnitType unit,
                        int incidentId)
        : receiver(receiver), unit(unit), incidentId(incidentId) {}

    void execute() override {
        receiver.dispatchUnit(incidentId, unit);
    }

    void undo() override {
        receiver.cancelDispatch(incidentId, unit);
    }

    std::string description() const override {
        return "Dispatch " + std::string(toString(unit)) +
               " to incident " + std::to_string(incidentId);
    }

private:
    EmergencyResponseMediator& receiver;
    ResponseUnitType unit;
    int incidentId;
};

#endif