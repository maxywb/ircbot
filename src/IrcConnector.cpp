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

void IrcConnector::demo()
{

  // open socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "failed to open socket" << std::endl;
    return;
  } 
  std::cout << "opened socket" << std::endl;


  // set 1 second timeout
  struct timeval tv;
  tv.tv_sec = 1;  //seconds
  tv.tv_usec = 0;  // not setting this can cause weird behavior
  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
  std::cout << "opened set 1 second timer" << std::endl;

  // look up server
  struct hostent *server = gethostbyname(server_.c_str());
  if (server == nullptr) {
    std::cerr << "no such host " << server_ << std::endl;
    return;
  } else {
    std::cerr << "found hose " << server_ << std::endl;
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
  } else {
    std::cout << "connected to " << server_ << std::endl;
  }
  
  while (true) {
    char buffer[256];
    int size = recv(sockfd,buffer,255,0);
    if (size < 0) {
      std::cout << "nothing to read from socket" << std::endl;
      break;
    }
    std::cout << buffer << std::endl;
  }

  char * userMessage = "USER boatz boatz boatz :something\n";
  size_t lenUserMessage = strlen(userMessage);

  int userMessageStatus = write(sockfd, userMessage, lenUserMessage);

  if (userMessageStatus < 0) {
    std::cerr << "failed to send username" << std::endl;
    return;
  } else {
    std::cout << "set username" << std::endl;
  }

  char * nickMessage = "NICK boatz\n";
  size_t lenNickMessage = strlen(nickMessage);
  
  int nickMessageStatus = write(sockfd, nickMessage, lenNickMessage);

  if (nickMessageStatus < 0) {
    std::cerr << "failed to send nick" << std::endl;
    return;
  } else {
    std::cout << "set nick" << std::endl;
  }

  while (true) {
    char buffer[256];
    int size = recv(sockfd,buffer,255,0);
    if (size < 0) {
      std::cout << "nothing to read from socket" << std::endl;
      break;
    }
    std::cout << buffer << std::endl;
  }

  char * joinMessage = "JOIN #boatz\n";
  size_t lenJoinMessage = strlen(joinMessage);
  
  int joinMessageStatus = write(sockfd, joinMessage, lenJoinMessage);

  if (joinMessageStatus < 0) {
    std::cerr << "failed to send join" << std::endl;
    return;
  } else {
    std::cout << "set join" << std::endl;
  }

  char * helloMessage = "PRIVMSG #boatz sup\n";
  size_t lenHelloMessage = strlen(helloMessage);
  
  int helloMessageStatus = write(sockfd, helloMessage, lenHelloMessage);

  if (helloMessageStatus < 0) {
    std::cerr << "failed to send hello" << std::endl;
    return;
  } else {
    std::cout << "set hello" << std::endl;
  }

  while (true) {
    char buffer[256];
    std::memset(buffer, 0, sizeof(buffer));
    int size = recv(sockfd,buffer,255,0);
    if (size < 0) {
      std::cout << "nothing to read from socket" << std::endl;
      continue;
    }
    std::cout << buffer << std::endl;
  }

  close(sockfd);
}

void IrcConnector::pong()
{

}

}
