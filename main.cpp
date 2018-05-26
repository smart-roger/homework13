#include <iostream>

#include "TShell.h"
#include "TDBController.h"

#include <boost/asio.hpp>
#include "network.h"
int main(int argc, char** argv)
{
    if (argc < 2){
        std::cout << "Using: join_server <port> "<<std::endl;
        return -1;
    }


    std::shared_ptr<TDBController> controller = std::make_shared<TDBController>();
    TShellPtr  shell = std::make_shared<TShell>(controller);

    std::stringstream init;
    init << "create A" << std::endl;
    init << "create B" << std::endl;
    init << "INSERT A 0 lean" << std::endl;
    init << "INSERT A 1 sweater" << std::endl;
    init << "INSERT A 2 frank" << std::endl;
    init << "INSERT A 3 violation" << std::endl;
    init << "INSERT A 4 quality" << std::endl;
    init << "INSERT A 5 precision" << std::endl;
    init << "INSERT B 3 proposal" << std::endl;
    init << "INSERT B 4 example" << std::endl;
    init << "INSERT B 5 lake" << std::endl;
    init << "INSERT B 6 flour" << std::endl;
    init << "INSERT B 7 wonder" << std::endl;
    init << "INSERT B 8 selection" << std::endl;

    {
        std::string line;
        while (std::getline(init, line)){
            /*std::cout << "line:" <<*/ shell->execute(line) /*<< std::endl*/;
        }
    }


    int port (atoi(argv[1]));
    boost::asio::io_service io_service;

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    network::server serverDB(io_service, endpoint, shell);

    io_service.run();

    return 0;
}
