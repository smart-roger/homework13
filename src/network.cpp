#include "network.h"

namespace network{
     using namespace boost::asio;

     session::session(
                    ip::tcp::socket socket,
                    std::set<std::shared_ptr<session>>& container,
                    TShellPtr shell)
        : _socket(std::move(socket)),
            _symbol(0),
            _read_line(""),
            _container(container),
            _shell(shell)
      {
      }

      void session::read()
      {
        auto self(shared_from_this());
        boost::asio::async_read(_socket,
            boost::asio::buffer(&_symbol, 1),
            [this, self](boost::system::error_code ec, std::size_t length)
            {
              if (!ec)
              {
                  if('\n' != _symbol){
                    _read_line+=_symbol;
                  }
                  else {
                    if('\r' == _read_line.back())
                        _read_line.pop_back();

                        std::string res(_shell->execute(_read_line));
                        boost::asio::async_write(_socket,
                                                 boost::asio::buffer(res.data(), res.length()),
                                                 [](const boost::system::error_code& error, std::size_t bytes_transferred)
                                                 {
                                                    if (error)
                                                        std::cout << "Error while writing data: "
                                                            << error.message() << std::endl;
                                                 });
                        //std::cout << _read_line << ":" << res << std::endl;
                        _read_line.clear();
                        //std::cout <<"=================="<<std::endl;
                  }

                  read();
              } else {

                _container.erase(self);
                _socket.close();
                //if ( _container.empty())
                    //_console->flush();
              }
            });
      }

    server::server(boost::asio::io_service& io_service,
          const ip::tcp::endpoint& endpoint,
          TShellPtr shell)
        : acceptor_(io_service, endpoint),
          socket_(io_service),
          clients(),
          _shell(shell)
          {
            do_accept();
          }

    void server::do_accept()
      {
        acceptor_.async_accept(socket_,
            [this](boost::system::error_code ec)
            {
              if (!ec){
                auto session_new = std::make_shared<session>(std::move(socket_), clients, _shell);
                clients.insert(session_new);
                session_new->start();
              }
              do_accept();
            });
      }
}
