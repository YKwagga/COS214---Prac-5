#ifndef RESOLVED_STATE_H
#define RESOLVED_STATE_H

#include "IncidentState.h"

class ResolvedState : public IncidentState {
public:
    bool handle(Incident& incident, IncidentAction action) const override;
    const char* name() const override { return "Resolved"; }
};

#endif
