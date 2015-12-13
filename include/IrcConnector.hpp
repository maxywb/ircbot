#ifndef IRCBOT_IRCCONNECTOR_HPP
#define IRCBOT_IRCCONNECTOR_HPP

#include <forward_list>
#include <string>
#include <mutex>

namespace ircbot
{

class IrcConnector
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
               size_t const port);

  // sending commands
  void join(std::string const & channel);
  void nick(std::string const & nick);
  void privmsg(std::string const & who, std::string const & message);
  void user(std::string const & username);

  // reading commands
  std::string read();

  // misc commands
  void pong(std::string const & value);
  void quit();


};

}

#endif
