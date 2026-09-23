#ifndef ISSUE_EVACUATION_COMMAND_H
#define ISSUE_EVACUATION_COMMAND_H

#include "Command.h"
#include "EmergencyResponseMediator.h"

class IssueEvacuationCommand : public Command {
public:
    IssueEvacuationCommand(EmergencyResponseMediator& receiver,
                           const std::string& message,
                           int incidentId)
        : receiver(receiver),
          message(message),
          incidentId(incidentId) {}

    void execute() override {
        receiver.issueEvacuation(message, incidentId);
    }

    void undo() override {
        receiver.cancelEvacuation(incidentId);
    }

    std::string description() const override {
        return "Issue evacuation '" + message +
               "' for incident " + std::to_string(incidentId);
    }

private:
    EmergencyResponseMediator& receiver;
    std::string message;
    int incidentId;
};

#endif