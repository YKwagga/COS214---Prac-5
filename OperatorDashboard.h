#ifndef OPERATOR_DASHBOARD_H
#define OPERATOR_DASHBOARD_H

#include "IncidentObserver.h"

class OperatorDashboard : public IncidentObserver {
public:
    void update(const Incident& incident,
                IncidentUpdateType updateType) override;
};

#endif
