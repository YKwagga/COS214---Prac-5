#include "EmergencyResponseMediator.h"
#include "SecurityTeam.h"
#include "MedicalTeam.h"
#include "AlertService.h"
#include "AccessControl.h"

#include <iostream>

int main() {
    std::cout << "===== CampusGuard Mediator Demo =====\n";

    EmergencyResponseMediator mediator;

    SecurityTeam  security(1, &mediator);
    MedicalTeam   medical(2, &mediator);
    AlertService  alert(3, &mediator);
    AccessControl access(4, &mediator);

    mediator.setColleagues(&security, &medical, &alert, &access);

    std::cout << "\n--- Colleague information ---\n";
    std::cout << security.getName() << " id=" << security.getId()
              << " status=" << static_cast<int>(security.getStatus()) << "\n";
    std::cout << medical.getName()  << " id=" << medical.getId()
              << " status=" << static_cast<int>(medical.getStatus())  << "\n";
    std::cout << alert.getName()    << " id=" << alert.getId()
              << " status=" << static_cast<int>(alert.getStatus())    << "\n";
    std::cout << access.getName()   << " id=" << access.getId()
              << " status=" << static_cast<int>(access.getStatus())   << "\n";

    std::cout << "\n--- Test 1: AreaSecured (Security -> Medical + Alert) ---\n";
    security.reportAreaSecured(101);

    std::cout << "\n--- Test 2: NeedBackup (Security -> Alert + Security) ---\n";
    security.requestBackup(101);

    std::cout << "\n--- Test 3: UnitArrived (Medical -> Alert + Access) ---\n";
    medical.reportUnitArrived(101);

    std::cout << "\n--- Test 4: TaskComplete (AccessControl -> everyone) ---\n";
    access.unlockArea(12, 101);

    std::cout << "\n--- Test 5: UnitArrived (Security -> Alert + Access) ---\n";
    security.reportUnitArrived(101);

    std::cout << "\n--- Test 6: TaskComplete (Alert -> everyone) ---\n";
    alert.broadcast("Evacuation notice", 101);

    std::cout << "\n--- Test 7: TaskComplete (Medical -> everyone) ---\n";
    medical.reportTaskComplete(101);

    std::cout << "\n--- Test 8: TaskComplete (Security -> everyone) ---\n";
    security.reportTaskComplete(101);

    std::cout << "\n--- Setter test ---\n";
    security.setStatus(ResponseStatus::Busy);
    security.setName("SecurityTeam-Alpha");
    std::cout << "After setter: "
              << security.getName() << " status="
              << static_cast<int>(security.getStatus()) << "\n";

    std::cout << "\n===== Demo complete =====\n";
    return 0;
}