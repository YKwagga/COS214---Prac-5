#ifndef RESPONSE_MEDIATOR_H
#define RESPONSE_MEDIATOR_H

#include "Types.h"

class ResponseComponent;

class ResponseMediator {
public:
    virtual ~ResponseMediator() = default;
    virtual void notify(ResponseComponent* sender,
                        const ComponentEvent& event) = 0;
};

#endif