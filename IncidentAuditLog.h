#ifndef INCIDENT_AUDIT_LOG_H
#define INCIDENT_AUDIT_LOG_H

#include "IncidentObserver.h"

#include <string>
#include <vector>

class IncidentAuditLog : public IncidentObserver {
public:
    void update(const Incident& incident,
                IncidentUpdateType updateType) override;

    const std::vector<std::string>& entries() const { return logEntries; }

private:
    std::vector<std::string> logEntries;
};

#endif
