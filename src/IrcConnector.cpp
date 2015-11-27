#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <sstream>

#include "assert.hpp"
#include "IrcConnector.hpp"

namespace ircbot
{

IrcConnector::IrcConnector()
{
  // open socket
  socket_ = socket(AF_INET, SOCK_STREAM, 0);

  ASSERT(socket_ > 0, "failed to open socket"); 
  PRINT("opened socket");

  // set 1 second timeout
  struct timeval tv;
  tv.tv_sec = 1;  //seconds
  tv.tv_usec = 0;  // not setting this can cause weird behavior
  setsockopt(socket_,
             SOL_SOCKET,
             SO_RCVTIMEO,
             (char *)&tv,
             sizeof(struct timeval));

  PRINT("set 1 second timeout on socket");
}

IrcConnector::~IrcConnector()
{
  quit();
  closeSocket();
}

/* ##### 
 * private methods 
 */

void IrcConnector::closeSocket()
{
  int status = close(socket_);
  ASSERT(status == 0, "failed to close socket");

  socket_ = -1;
}

bool IrcConnector::connected()
{
  return socket_ != -1;
}

bool IrcConnector::write(std::string const & text)
{
  LOCK_SOCKET_FOR_WRITE;

  PRINT("writing: " << text);

  std::string const message = text + "\n";

  int messageStatus = ::write(socket_, message.c_str(), message.size());

  if (messageStatus < 0) {
    ERROR("failed to write : " << message);
    return false;
  }
  
  return true;
}

/* ##### 
 * public methods 
 */

void IrcConnector::connect(std::string const address, size_t const port)
{
  // look up server
  struct hostent *server = gethostbyname(address.c_str());
  ASSERT(server, "no such host " << address);
  PRINT("found host " << address);

  // connect to server
  struct sockaddr_in serv_addr;
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(port);

  int connectStatus = ::connect(socket_,
                                (struct sockaddr *) &serv_addr,
                                sizeof(serv_addr));

  ASSERT(connectStatus >= 0,
         "failed to connect to "
         << address << ":" << port
         << ", status: " << connectStatus);
  PRINT("connected to " << address << ":" << port);
}

void IrcConnector::join(std::string const & channel)
{
  std::string const message = "JOIN " + channel;
  write(message);
}
void IrcConnector::nick(std::string const & nick)
{
  std::string const message = "NICK " + nick;
  write(message);
}

void IrcConnector::privmsg(std::string const & who, std::string const & text)
{
  std::string const message = "PRIVMSG " + who + " " + text;
  write(message);
}

void IrcConnector::user(std::string const & username)
{
  std::string const message = "USER " 
                              + username + " "
                              + username + " "
                              + username + " "
                              + ":" + username;
  write(message);
}

std::string IrcConnector::read()
{
  std::stringstream text;

  while (true) {
    char buffer[256];
    std::memset(buffer,
                0,
                sizeof(buffer));
  
    int size = recv(socket_,
                    buffer,
                    255,
                    0);

    if (size < 0) {
      break;
    } else {
      PRINT(buffer);
      text << buffer;

    }
  }
  return text.str();
}

void IrcConnector::quit()
{
  if (connected()) {
    std::string const message = "QUIT cya";
    write(message);
    PRINT("closed connection");
  } else {
    ERROR("can't quit, socket is closed");
  }
}

}

