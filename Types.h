#ifndef TYPES_H
#define TYPES_H

#include <string>

enum class ComponentEventType {
    AreaSecured,
    NeedBackup,
    UnitArrived,
    TaskComplete
};

enum class ResponseStatus {
    Available,
    Dispatched,
    OnScene,
    Busy,
    Offline
};

struct ComponentEvent {
    ComponentEventType type;
    std::string message;
    int incidentId;

    ComponentEvent(ComponentEventType t,
                   const std::string& msg,
                   int iid)
        : type(t), message(msg), incidentId(iid) {}
};

#endif