#include "CancelledState.h"
#include "DispatchedState.h"
#include "InProgressState.h"
#include "Incident.h"
#include "ReportedState.h"
#include "ResolvedState.h"

bool ReportedState::handle(Incident& incident, IncidentAction action) const {
    if (action == IncidentAction::Dispatch) {
        incident.transitionTo(std::unique_ptr<IncidentState>(new DispatchedState()),
                              IncidentUpdateType::StateChanged);
        return true;
    }
    if (action == IncidentAction::Cancel) {
        incident.transitionTo(std::unique_ptr<IncidentState>(new CancelledState()),
                              IncidentUpdateType::Cancelled);
        return true;
    }
    return incident.reject(action, "the incident has not been dispatched");
}

bool DispatchedState::handle(Incident& incident, IncidentAction action) const {
    if (action == IncidentAction::BeginResponse) {
        incident.transitionTo(std::unique_ptr<IncidentState>(new InProgressState()),
                              IncidentUpdateType::StateChanged);
        return true;
    }
    if (action == IncidentAction::Cancel) {
        incident.transitionTo(std::unique_ptr<IncidentState>(new CancelledState()),
                              IncidentUpdateType::Cancelled);
        return true;
    }
    return incident.reject(action, "a response unit is already dispatched");
}

bool InProgressState::handle(Incident& incident, IncidentAction action) const {
    if (action == IncidentAction::Resolve) {
        incident.transitionTo(std::unique_ptr<IncidentState>(new ResolvedState()),
                              IncidentUpdateType::Resolved);
        return true;
    }
    return incident.reject(action,
                           "an active response can only be resolved");
}

bool ResolvedState::handle(Incident& incident, IncidentAction action) const {
    return incident.reject(action, "the incident is already resolved");
}

bool CancelledState::handle(Incident& incident, IncidentAction action) const {
    return incident.reject(action, "the incident was cancelled");
}
