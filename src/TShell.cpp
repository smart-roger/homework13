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
}

TShell::~TShell()
{
    _commands.clear();
}

void TShell::execute(std::string strCommand){
    std::lock_guard<std::mutex> lock(_mutexTransaction);
    std::stringstream   sstream(strCommand);

    std::string command;
    sstream >> command;

    if(0==_commands.count(command)){
        std::cout << "Err " << "Command " << command << " not found." << std::endl;
    }else{
        std::shared_ptr<TCommand>   ptrCommand = _commands[command];
        auto Res = ptrCommand->exec(_controller, sstream);
        std::cout << Res.toString() << std::endl;

    }
}
