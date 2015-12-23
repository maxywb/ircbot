#ifndef IRCBOT_OPERATION_HPP
#define IRCBOT_OPERATION_HPP

#include <memory>

namespace ircbot
{

class IrcConnector;

class Operation
{
 protected:
  std::shared_ptr<IrcConnector> ircConnection_;
  
 public:

  Operation(std::shared_ptr<IrcConnector> ircConnection)
      :     ircConnection_(ircConnection)
  {}  

  virtual void consume(std::string const match) = 0;

};

}

#endif
