#include "EmergencyResponseMediator.h"
#include "SecurityTeam.h"
#include "MedicalTeam.h"
#include "AlertService.h"
#include "AccessControl.h"
#include "IncidentRegistry.h"
#include "OperatorDashboard.h"
#include "IncidentAuditLog.h"
#include "ExternalAgencyNotifier.h"
#include "LegacyEmergencyAdapter.h"
#include "LegacyCityEmergencySystem.h"

#include <iostream>

int main() {
    std::cout << "===== CampusGuard Mediator Demo =====\n";

    EmergencyResponseMediator mediator;

    SecurityTeam  security(1, &mediator);
    MedicalTeam   medical(2, &mediator);
    AlertService  alert(3, &mediator);
    AccessControl access(4, &mediator);

    mediator.setColleagues(&security, &medical, &alert, &access);

    std::cout << "\n===== Incident State + Observer Demo =====\n";
    IncidentRegistry registry;
    OperatorDashboard dashboard;
    IncidentAuditLog auditLog;
    LegacyCityEmergencySystem legacyCitySystem;
    LegacyEmergencyAdapter cityAdapter(legacyCitySystem);
    ExternalAgencyNotifier agencyNotifier(&cityAdapter);

    Incident& libraryFire = registry.createIncident(
        IncidentType::Fire, IncidentSeverity::Critical, 12);
    libraryFire.attach(&mediator);
    libraryFire.attach(&dashboard);
    libraryFire.attach(&auditLog);
    libraryFire.attach(&agencyNotifier);

    std::cout << "\n--- Incident 100: lifecycle changes notify observers ---\n";
    libraryFire.request(IncidentAction::Dispatch);
    libraryFire.request(IncidentAction::BeginResponse);
    libraryFire.request(IncidentAction::Resolve);
    libraryFire.request(IncidentAction::Dispatch); // intentional invalid case

    Incident& clinicMedical = registry.createIncident(
        IncidentType::Medical, IncidentSeverity::High, 7);
    clinicMedical.attach(&mediator);
    clinicMedical.attach(&dashboard);
    clinicMedical.attach(&auditLog);
    clinicMedical.attach(&agencyNotifier);

    std::cout << "\n--- Incident 101: cancellation before response begins ---\n";
    clinicMedical.request(IncidentAction::Dispatch);
    clinicMedical.request(IncidentAction::Cancel);

    std::cout << "\n--- Colleague information ---\n";
    std::cout << security.getName() << " id=" << security.getId()
              << " status=" << static_cast<int>(security.getStatus()) << "\n";
    std::cout << medical.getName()  << " id=" << medical.getId()
              << " status=" << static_cast<int>(medical.getStatus())  << "\n";
    std::cout << alert.getName()    << " id=" << alert.getId()
              << " status=" << static_cast<int>(alert.getStatus())    << "\n";
    std::cout << access.getName()   << " id=" << access.getId()
              << " status=" << static_cast<int>(access.getStatus())   << "\n";

    // These retain the original low-level Mediator examples. They use an
    // isolated event ID rather than pretending to operate on a cancelled
    // lifecycle incident from the scenarios above.
    const int mediatorDemoIncidentId = 999;

    std::cout << "\n--- Test 1: AreaSecured (Security -> Medical + Alert) ---\n";
    security.reportAreaSecured(mediatorDemoIncidentId);

    std::cout << "\n--- Test 2: NeedBackup (Security -> Alert + Security) ---\n";
    security.requestBackup(mediatorDemoIncidentId);

    std::cout << "\n--- Test 3: UnitArrived (Medical -> Alert + Access) ---\n";
    medical.reportUnitArrived(mediatorDemoIncidentId);

    std::cout << "\n--- Test 4: TaskComplete (AccessControl -> everyone) ---\n";
    access.unlockArea(12, mediatorDemoIncidentId);

    std::cout << "\n--- Test 5: UnitArrived (Security -> Alert + Access) ---\n";
    security.reportUnitArrived(mediatorDemoIncidentId);

    std::cout << "\n--- Test 6: TaskComplete (Alert -> everyone) ---\n";
    alert.broadcast("Evacuation notice", mediatorDemoIncidentId);

    std::cout << "\n--- Test 7: TaskComplete (Medical -> everyone) ---\n";
    medical.reportTaskComplete(mediatorDemoIncidentId);

    std::cout << "\n--- Test 8: TaskComplete (Security -> everyone) ---\n";
    security.reportTaskComplete(mediatorDemoIncidentId);

    std::cout << "\n--- Setter test ---\n";
    security.setStatus(ResponseStatus::Busy);
    security.setName("SecurityTeam-Alpha");
    std::cout << "After setter: "
              << security.getName() << " status="
              << static_cast<int>(security.getStatus()) << "\n";

    std::cout << "\n===== Demo complete =====\n";
    return 0;
}
