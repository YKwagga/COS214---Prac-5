#ifndef COMMAND_INVOKER_H
#define COMMAND_INVOKER_H

#include "Command.h"
#include <vector>

class CommandInvoker {
public:
    void execute(Command* command);
    void undoLast();
    bool hasHistory() const;

private:
    std::vector<Command*> history;
};

#endif