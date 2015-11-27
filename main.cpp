#include <string>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <thread>

#include "IrcConnector.hpp"


int main(void) {
  
  std::string const nick = "boatz";
  std::string const server = "irc.rizon.net";
  size_t const port = 7000;

  ircbot::IrcConnector connector;

  connector.connect(server, port);
  connector.read();

  // this will at most 5 seconds due to timeout, by then rizon will be ready
  for (int i = 0; i < 5; ++i) {  
    connector.read();
  }

  connector.user(nick);
  connector.nick(nick);

  connector.read();

  connector.join("#boatz");
  connector.read();

  connector.privmsg("#boatz", "sup");
  
}
