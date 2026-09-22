#ifndef REPORTED_STATE_H
#define REPORTED_STATE_H

#include "IncidentState.h"

class ReportedState : public IncidentState {
public:
    bool handle(Incident& incident, IncidentAction action) const override;
    const char* name() const override { return "Reported"; }
};

#endif
