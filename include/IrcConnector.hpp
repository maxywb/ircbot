#ifndef IRCBOT_IRCCONNECTOR_HPP
#define IRCBOT_IRCCONNECTOR_HPP

#include <forward_list>
#include <string>
#include <mutex>

#include "IrcConnectorInterface.hpp"

namespace ircbot
{


class IrcConnector : public IrcConnectorInterface
{
 private:

  // socket stuff
  int socket_;
  std::mutex writeMutex_;
# define LOCK_SOCKET_FOR_WRITE std::lock_guard<std::mutex> scope_lock__(writeMutex_);

  void closeSocket();
  bool connected();

  bool write(std::string const & text);

 public:

  IrcConnector();
  ~IrcConnector();

  void connect(std::string const addres,
               size_t const port) override;

  // sending commands
  void join(std::string const & channel) override;
  void part(std::string const & channel) override;
  void nick(std::string const & nick) override;
  void privmsg(std::string const & who, std::string const & message) override;
  void user(std::string const & username) override;

  // reading commands
  std::string read() override;

  // misc commands
  void pong(std::string const & value) override;
  void quit() override;


};

}

#endif
