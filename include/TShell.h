#ifndef TSHELL_H
#define TSHELL_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <mutex>

#include "TDBController.h"
#include "TCommand.h"
#include "common_types.h"

class TShell
{
    public:
        TShell() = delete;
        TShell(std::shared_ptr<TDBController> controller);
        ~TShell();

        std::string execute(std::string strCommand);
    protected:

    private:
        std::mutex _mutexTransaction;
        std::shared_ptr<TDBController>   _controller;
        std::unordered_map<std::string, std::shared_ptr<TCommand>> _commands;
};

using TShellPtr = std::shared_ptr<TShell>;

#endif // TSHELL_H
