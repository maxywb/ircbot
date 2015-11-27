#ifndef IRCBOT_IRCCONNECTOR_HPP
#define IRCBOT_IRCCONNECTOR_HPP

#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions

#include <string>

namespace ircbot
{

class IrcConnector
{
 private:

  std::string server_;
  size_t port_;
  std::string password_;
  std::string username_;
  std::string hostname_;
  std::string servername_;
  std::string realname_;

 public:

  IrcConnector(std::string server,
               size_t port,
               std::string password,
               std::string username,
               std::string hostname,
               std::string servername,
               std::string realname);

  void demo();
  void pong();

};

}

#endif
