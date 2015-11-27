#include <string>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions

#include "IrcConnector.hpp"


int main(void) {
  
  std::string server = "irc.rizon.net";
  size_t port = 7000;
  std::string password = "this is a password";
  std::string username = "boatz";
  std::string hostname = "hostname";
  std::string servername = "servername";
  std::string realname = "realname";

  ircbot::IrcConnector connector(server, port, password, username, hostname, servername, realname);
  connector.demo();
}
