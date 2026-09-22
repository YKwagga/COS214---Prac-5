#ifndef DISPATCHED_STATE_H
#define DISPATCHED_STATE_H

#include "IncidentState.h"

class DispatchedState : public IncidentState {
public:
    bool handle(Incident& incident, IncidentAction action) const override;
    const char* name() const override { return "Dispatched"; }
};

#endif
