#ifndef NETWORK_H
#define NETWORK_H

#include <set>

#include <boost/asio.hpp>
#include "TShell.h"

namespace network
{
     using namespace boost::asio;

     class session
      : public std::enable_shared_from_this<session>
    {
    public:
        session(    ip::tcp::socket socket,
                    std::set<std::shared_ptr<session>>& container,
                    TShellPtr shell);

      virtual ~session(){}

      void start()
      {
        read();
      }

    private:
      void read();

      ip::tcp::socket _socket;
      char _symbol;
      std::string _read_line;
      std::set<std::shared_ptr<session>>& _container;

      TShellPtr   _shell;

    };

    using containerConnections = std::set<std::shared_ptr<session>>;
    class server
    {
        public:
        server(boost::asio::io_service& io_service,
          const ip::tcp::endpoint& endpoint,
          TShellPtr shell);

    void do_accept();

    private:
      ip::tcp::acceptor acceptor_;
      ip::tcp::socket socket_;
      std::set<std::shared_ptr<session>> clients;
      TShellPtr _shell;
    };

};

#endif // NETWORK_H
