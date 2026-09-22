#ifndef INCIDENT_H
#define INCIDENT_H

#include "IncidentState.h"
#include "Subject.h"

#include <memory>
#include <string>

class Incident : public Subject {
public:
    Incident(int id,
             IncidentType type,
             IncidentSeverity severity,
             int areaId);
    ~Incident();

    Incident(const Incident&) = delete;
    Incident& operator=(const Incident&) = delete;

    bool request(IncidentAction action);

    int getId() const { return id; }
    IncidentType getType() const { return type; }
    IncidentSeverity getSeverity() const { return severity; }
    int getAreaId() const { return areaId; }
    const IncidentState& getState() const { return *state; }
    const char* getStateName() const { return state->name(); }

    // State objects call this after validating a transition. It is public to
    // keep the state hierarchy independent of Incident internals; clients
    // should use request() instead.
    void transitionTo(std::unique_ptr<IncidentState> nextState,
                      IncidentUpdateType updateType);
    bool reject(IncidentAction action, const std::string& reason) const;

private:
    int id;
    IncidentType type;
    IncidentSeverity severity;
    int areaId;
    std::unique_ptr<IncidentState> state;
};

#endif
