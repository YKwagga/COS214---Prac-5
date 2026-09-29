#include "EmergencyResponseFacade.h"

#include "EmergencyResponseMediator.h"
#include "ExternalAgencyNotifier.h"
#include "DispatchUnitCommand.h"
#include "IssueEvacuationCommand.h"
#include "SecureAreaCommand.h"
#include "CommandInvoker.h"

#include <iostream>

EmergencyResponseFacade::EmergencyResponseFacade(
    IncidentRegistry& registry,
    EmergencyResponseMediator& mediator,
    OperatorDashboard& dashboard,
    IncidentAuditLog& auditLog,
    ExternalAgencyNotifier& agencyNotifier)
    : registry(registry),
      mediator(mediator),
      dashboard(dashboard),
      auditLog(auditLog),
      agencyNotifier(agencyNotifier) {}

Incident& EmergencyResponseFacade::createObservedIncident(
    IncidentType type,
    IncidentSeverity severity,
    int areaId) {
    Incident& incident = registry.createIncident(type, severity, areaId);
    incident.attach(&mediator);
    incident.attach(&dashboard);
    incident.attach(&auditLog);
    incident.attach(&agencyNotifier);
    return incident;
}

int EmergencyResponseFacade::startEvacuation(
    int areaId,
    const std::string& message) {
    std::cout << "\n===== Evacuation Scenario =====\n";
    Incident& incident = createObservedIncident(
        IncidentType::Fire, IncidentSeverity::Critical, areaId);

    incident.request(IncidentAction::Dispatch);
    incident.request(IncidentAction::BeginResponse);

    CommandInvoker invoker;
    IssueEvacuationCommand evacuation(mediator, message, incident.getId());
    invoker.execute(&evacuation);
    return incident.getId();
}

int EmergencyResponseFacade::respondToSecurityThreat(int areaId) {
    std::cout << "\n===== Security Threat Scenario =====\n";
    Incident& incident = createObservedIncident(
        IncidentType::SecurityThreat, IncidentSeverity::High, areaId);

    incident.request(IncidentAction::Dispatch);
    incident.request(IncidentAction::BeginResponse);

    CommandInvoker invoker;
    DispatchUnitCommand dispatchSecurity(
        mediator, ResponseUnitType::Security, incident.getId());
    SecureAreaCommand secureArea(mediator, areaId, incident.getId());
    invoker.execute(&dispatchSecurity);
    invoker.execute(&secureArea);
    return incident.getId();
}

int EmergencyResponseFacade::respondToMedicalEmergency(int areaId) {
    std::cout << "\n===== Medical Emergency Scenario =====\n";
    Incident& incident = createObservedIncident(
        IncidentType::Medical, IncidentSeverity::High, areaId);

    incident.request(IncidentAction::Dispatch);
    incident.request(IncidentAction::BeginResponse);

    CommandInvoker invoker;
    DispatchUnitCommand dispatchMedical(
        mediator, ResponseUnitType::Medical, incident.getId());
    invoker.execute(&dispatchMedical);
    return incident.getId();
}

int EmergencyResponseFacade::simulateCancelledSecurityResponse(int areaId) {
    std::cout << "\n===== Cancelled Security Response Scenario =====\n";
    Incident& incident = createObservedIncident(
        IncidentType::SecurityThreat, IncidentSeverity::High, areaId);

    incident.request(IncidentAction::Dispatch);
    incident.request(IncidentAction::BeginResponse);

    CommandInvoker invoker;
    DispatchUnitCommand dispatchSecurity(
        mediator, ResponseUnitType::Security, incident.getId());
    SecureAreaCommand secureArea(mediator, areaId, incident.getId());

    invoker.execute(&dispatchSecurity);
    invoker.execute(&secureArea);

    std::cout << "[Scenario] Incident interrupted mid-response; cancelling and "
                 "undoing completed work.\n";
    incident.request(IncidentAction::Cancel);
    while (invoker.hasHistory()) {
        invoker.undoLast();
    }

    return incident.getId();
}
