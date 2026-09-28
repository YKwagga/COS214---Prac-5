# CampusGuard - COS 214 Practical 5

CampusGuard is a C++11 emergency-response coordination application for a university
campus. It models incident lifecycles, coordinates security, medical, alert and
access-control services, adapts a legacy city emergency service, and exposes
high-level emergency workflows.

## Team

- Dirk Kunz u24689999
- Yoshua Smit u25433726
- Chavonne Makurira
- https://github.com/YKwagga/COS214---Prac-5

## Build and Run

The required build uses the supplied Makefile and C++11:

```text
make clean
make
./campusguard
```

The assessed demonstration must be run through Docker:

```text
docker compose up --build
```

The current Docker image installs `gdb` and `valgrind` and builds the same
application inside the container.

## System Design

The application supports the following workflow:

1. An incident is registered with a type, severity and campus area.
2. The incident changes from Reported to Dispatched, In Progress, Resolved or Cancelled.
3. The mediator coordinates response components when the incident changes state or when a component reports an event.
4. Commands dispatch units, secure areas and issue or undo evacuation actions.
5. Critical incident updates are sent to an external agency through the legacy service adapter.
6. The facade creates observed incidents and starts complete emergency workflows.

The default demonstration creates multiple incidents with different runtime data,
shows a cancellation and an invalid operation, and prints the collaborations so
they can be followed during the presentation.

## GoF Pattern Mapping

### Command

- `Command`: command interface.
- `DispatchUnitCommand`, `SecureAreaCommand`, `IssueEvacuationCommand`: concrete
	commands.
- `CommandInvoker`: executes commands and stores history for undo.
- `EmergencyResponseMediator`: receiver for operational command requests.

Commands perform real response operations rather than only printing their names.

### Mediator

- `ResponseMediator`: mediator interface.
- `EmergencyResponseMediator`: concrete mediator.
- `SecurityTeam`, `MedicalTeam`, `AlertService` and `AccessControl`: colleagues.

Response components report events to the mediator. The mediator then coordinates
the other components without requiring direct many-to-many team dependencies.

### Adapter

- `ExternalEmergencyService`: CampusGuard-facing target interface.
- `LegacyEmergencyAdapter`: adapter.
- `LegacyCityEmergencySystem`: incompatible legacy adaptee.
- `ExternalAgencyNotifier`: client of the target interface.

The adapter converts CampusGuard incident data into the legacy zone, text payload
and priority parameters.

### Facade

- `EmergencyResponseFacade`: high-level entry point.
- `startEvacuation`, `respondToSecurityThreat` and `respondToMedicalEmergency`:
	multi-step workflows using the registry, observers, incident state, commands
	and response mediator.

### Additional Pattern 1: State

`Incident` is the context and owns the current `IncidentState` through
`std::unique_ptr`. `ReportedState`, `DispatchedState`, `InProgressState`,
`ResolvedState` and `CancelledState` validate lifecycle transitions and reject
invalid operations with a visible message.

### Additional Pattern 2: Observer

`Incident` is the subject. `OperatorDashboard`, `IncidentAuditLog`,
`ExternalAgencyNotifier` and `EmergencyResponseMediator` are observers. Incident
registrations are non-owning; the composition root keeps observers alive longer
than the incidents they observe.

## Ownership and Destruction

- `IncidentRegistry` owns incidents with `std::unique_ptr`.
- `Incident` owns its current state with `std::unique_ptr`.
- `Subject` stores non-owning observer pointers.
- `EmergencyResponseMediator` stores non-owning colleague pointers.
- `LegacyEmergencyAdapter` stores a non-owning reference to the legacy system.
- `ExternalAgencyNotifier` stores a non-owning target pointer.
- `CommandInvoker` stores non-owning pointers to commands; commands remain alive
	until execution and undo are complete.
- All polymorphic base classes have virtual destructors.