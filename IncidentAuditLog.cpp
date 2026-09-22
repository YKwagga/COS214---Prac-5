#include "IncidentAuditLog.h"
#include "Incident.h"

#include <iostream>
#include <sstream>

void IncidentAuditLog::update(const Incident& incident,
                              IncidentUpdateType updateType) {
    std::ostringstream entry;
    entry << "Incident " << incident.getId()
          << " is now " << incident.getStateName();

    switch (updateType) {
        case IncidentUpdateType::Resolved:
            entry << " (resolution recorded)";
            break;
        case IncidentUpdateType::Cancelled:
            entry << " (cancellation recorded)";
            break;
        default:
            break;
    }

    logEntries.push_back(entry.str());
    std::cout << "[Audit] " << entry.str() << "\n";
}
