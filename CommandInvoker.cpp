#include "CommandInvoker.h"
#include <iostream>

void CommandInvoker::execute(Command* command) {
    if (!command) {
        return;
    }

    command->execute();
    history.push_back(command);
}

void CommandInvoker::undoLast() {
    if (history.empty()) {
        std::cout << "[Invoker] Nothing to undo.\n";
        return;
    }

    Command* command = history.back();
    history.pop_back();

    if (command) {
        command->undo();
    }
}

bool CommandInvoker::hasHistory() const {
    return !history.empty();
}