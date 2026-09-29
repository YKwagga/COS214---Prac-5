#ifndef EMERGENCY_RESPONSE_FACADE_H
#define EMERGENCY_RESPONSE_FACADE_H

#include "IncidentAuditLog.h"
#include "IncidentRegistry.h"
#include "OperatorDashboard.h"

class EmergencyResponseMediator;
class ExternalAgencyNotifier;

class EmergencyResponseFacade {
public:
    EmergencyResponseFacade(IncidentRegistry& registry,
                            EmergencyResponseMediator& mediator,
                            OperatorDashboard& dashboard,
                            IncidentAuditLog& auditLog,
                            ExternalAgencyNotifier& agencyNotifier);

    int startEvacuation(int areaId, const std::string& message);
    int respondToSecurityThreat(int areaId);
    int respondToMedicalEmergency(int areaId);
    int simulateCancelledSecurityResponse(int areaId);

private:
    Incident& createObservedIncident(IncidentType type,
                                     IncidentSeverity severity,
                                     int areaId);

    IncidentRegistry& registry;
    EmergencyResponseMediator& mediator;
    OperatorDashboard& dashboard;
    IncidentAuditLog& auditLog;
    ExternalAgencyNotifier& agencyNotifier;
};

#endif
