#include "Incident.h"
#include "ReportedState.h"

#include <iostream>

Incident::Incident(int id,
                   IncidentType type,
                   IncidentSeverity severity,
                   int areaId)
    : id(id),
      type(type),
      severity(severity),
      areaId(areaId),
      state(new ReportedState()) {}

Incident::~Incident() {}

bool Incident::request(IncidentAction action) {
    return state->handle(*this, action);
}

void Incident::transitionTo(std::unique_ptr<IncidentState> nextState,
                            IncidentUpdateType updateType) {
    if (!nextState) {
        return;
    }

    const std::string oldState(state->name());
    state = std::move(nextState);

    std::cout << "[Incident " << id << "] " << oldState
              << " -> " << state->name() << "\n";
    notify(*this, updateType);
}

bool Incident::reject(IncidentAction action, const std::string& reason) const {
    std::cout << "[Incident " << id << "] Cannot " << toString(action)
              << " while " << state->name() << ": " << reason << "\n";
    return false;
}
