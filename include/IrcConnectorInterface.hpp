
#ifndef IRCBOT_IRCCONNECTORINTERFACE_HPP
#define IRCBOT_IRCCONNECTORINTERFACE_HPP

#include <string>

namespace ircbot
{

class IrcConnectorInterface
{

 public:
  virtual ~IrcConnectorInterface() {}

  IrcConnectorInterface() = default;

  virtual void connect(std::string const addres,
                       size_t const port) = 0;

  // sending commands
  virtual void join(std::string const & channel) = 0;
  virtual void nick(std::string const & nick) = 0;
  virtual void privmsg(std::string const & who, std::string const & message) = 0;
  virtual void user(std::string const & username) = 0;

  // reading commands
  virtual std::string read() = 0;

  // misc commands
  virtual void pong(std::string const & value) = 0;
  virtual void quit() = 0;
};



}

#endif
