#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include "IrcConnector.hpp"

namespace ircbot
{

IrcConnector::IrcConnector(std::string server,
                           size_t port,
                           std::string password,
                           std::string username,
                           std::string hostname,
                           std::string servername,
                           std::string realname)

    : server_(server),
      port_(port),
      password_(password),
      username_(username),
      hostname_(hostname),
      servername_(servername),
      realname_(realname)
{

  std::cout << server_ << std::endl;
  std::cout << port_ << std::endl;
  std::cout << password_ << std::endl;
  std::cout << username_ << std::endl;
  std::cout << hostname_ << std::endl;
  std::cout << servername_ << std::endl;
  std::cout << realname_ << std::endl;

}

void IrcConnector::connect()
{

  // open socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "failed to open socket" << std::endl;
    return;
  }

  // look up server
  struct hostent *server = gethostbyname(server_.c_str());
  if (server == nullptr) {
    std::cerr << "no such host " << server_ << std::endl;
    return;
  }

  // connect to server
  struct sockaddr_in serv_addr;
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(port_);
  if (::connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
    std::cerr << "failed to connect to " << server_ << std::endl;
    return;
  }
  
  while (true) {
    char buffer[256];
    int size = read(sockfd,buffer,255);
    if (size < 0) {
      std::cerr << "failed to read from socket" << std::endl;
      break;
    }
    std::cout << buffer << std::endl;
  }


  close(sockfd);
}

void IrcConnector::pong()
{

}

}
