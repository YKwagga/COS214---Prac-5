#ifndef RESPONSE_COMPONENT_H
#define RESPONSE_COMPONENT_H

#include "Types.h"
#include "ResponseMediator.h"
#include <string>

class ResponseComponent {
public:
    ResponseComponent(int id,
                      const std::string& name,
                      ResponseMediator* mediator)
        : id(id), name(name),
          status(ResponseStatus::Available),
          mediator(mediator) {}

    virtual ~ResponseComponent() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }
    ResponseStatus getStatus() const { return status; }
    ResponseMediator* getMediator() const { return mediator; }

    void setId(int newId) { id = newId; }
    void setName(const std::string& newName) { name = newName; }
    void setStatus(ResponseStatus newStatus) { status = newStatus; }
    void setMediator(ResponseMediator* m) { mediator = m; }

    void notifyMediator(ComponentEventType type,
                        const std::string& message,
                        int incidentId) {
        if (mediator)
            mediator->notify(this,
                ComponentEvent(type, message, incidentId));
    }

    virtual void receiveInstruction(const std::string& instruction) = 0;

protected:
    int id;
    std::string name;
    ResponseStatus status;
    ResponseMediator* mediator;   
};

#endif