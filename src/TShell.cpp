#include "TShell.h"

TShell::TShell(std::shared_ptr<TDBController> controller):_controller(controller), _commands()
{
    std::shared_ptr<TCommand>   ptrCommand;

    ptrCommand = std::make_shared<TCommandCreate>();
    _commands[ptrCommand->command()] = ptrCommand;

    ptrCommand = std::make_shared<TCommandInsert>();
    _commands[ptrCommand->command()] = ptrCommand;

    ptrCommand = std::make_shared<TCommandIntersection>();
    _commands[ptrCommand->command()] = ptrCommand;

    ptrCommand = std::make_shared<TCommandDifference>();
    _commands[ptrCommand->command()] = ptrCommand;

    ptrCommand = std::make_shared<TCommandTruncate>();
    _commands[ptrCommand->command()] = ptrCommand;
}

TShell::~TShell()
{
    _commands.clear();
}

std::string TShell::execute(std::string strCommand){
    std::lock_guard<std::mutex> lock(_mutexTransaction);
    std::stringstream   sstream(strCommand);

    std::string command;
    sstream >> command;

    std::string result;

    if(0==_commands.count(command)){
        result = std::string(err_header) + "Command " + command + " not found.\r\n";
    }else{
        std::shared_ptr<TCommand>   ptrCommand = _commands[command];
        auto Res = ptrCommand->exec(_controller, sstream);
        result = Res.toString();
    }

    return result;
}
