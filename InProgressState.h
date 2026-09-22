#ifndef IN_PROGRESS_STATE_H
#define IN_PROGRESS_STATE_H

#include "IncidentState.h"

class InProgressState : public IncidentState {
public:
    bool handle(Incident& incident, IncidentAction action) const override;
    const char* name() const override { return "In Progress"; }
};

#endif
