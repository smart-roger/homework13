#include <iostream>

#include "TShell.h"
#include "TDBController.h"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session>
{
    public:
        session(tcp::socket socket)
            : _socket(std::move(socket)){}

        void start () {std::cout << "session::start" << std::endl;};
        void read_data(){};

    private:
        tcp::socket _socket;
        std::string _message;
};

class server
{
public:
  server(boost::asio::io_service& io_service,
         const tcp::endpoint& endpoint)
        : acceptor_(io_service, endpoint),
            socket_(io_service)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket_))->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
};



int main(int argc, char** argv)
{
    if (argc < 2){
        std::cout << "Using: join_server <port> "<<std::endl;
        return -1;
    }

    size_t port (argv[1]);
    /*
    std::stringstream test;
    test << "create A" << std::endl;
    test << "create B" << std::endl;
    test << "INSERT A 0 lean" << std::endl;
    test << "INSERT A 1 sweater" << std::endl;
    test << "INSERT A 2 frank" << std::endl;
    test << "INSERT A 3 violation" << std::endl;
    test << "INSERT A 4 quality" << std::endl;
    test << "INSERT A 5 precision" << std::endl;

    test << "INSERT B 3 proposal" << std::endl;
    test << "INSERT B 4 example" << std::endl;
    test << "INSERT B 5 lake" << std::endl;
    test << "INSERT B 6 flour" << std::endl;
    test << "INSERT B 7 wonder" << std::endl;
    test << "INSERT B 8 selection" << std::endl;

    test << "INTERSECTION" << std::endl;
    test << "SYMMETRIC_DIFFERENCE" << std::endl;
*/

    std::shared_ptr<TDBController> controller = std::make_shared<TDBController>();
    TShell  shell(controller);
/*
    while(!test.eof()){
        std::string strInput;
        std::getline(test, strInput);
        shell.execute(strInput);
    }
*/

    boost::asio::io_service io_service;

    tcp::endpoint endpoint(tcp::v4(), port);
    server serverDB(io_service, endpoint);

    io_service.run();

    return 0;
}
