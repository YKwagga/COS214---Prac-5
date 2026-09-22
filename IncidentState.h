#ifndef INCIDENT_STATE_H
#define INCIDENT_STATE_H

#include "Types.h"

class Incident;

class IncidentState {
public:
    virtual ~IncidentState() {}

    virtual bool handle(Incident& incident, IncidentAction action) const = 0;
    virtual const char* name() const = 0;
};

#endif
