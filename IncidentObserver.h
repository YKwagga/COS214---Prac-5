#ifndef INCIDENT_OBSERVER_H
#define INCIDENT_OBSERVER_H

#include "Types.h"

class Incident;

// Observer participants receive lifecycle updates but do not control
// response components directly.
class IncidentObserver {
public:
    virtual ~IncidentObserver() {}

    virtual void update(const Incident& incident,
                        IncidentUpdateType updateType) = 0;
};

#endif
