#ifndef CANCELLED_STATE_H
#define CANCELLED_STATE_H

#include "IncidentState.h"

class CancelledState : public IncidentState {
public:
    bool handle(Incident& incident, IncidentAction action) const override;
    const char* name() const override { return "Cancelled"; }
};

#endif
