#ifndef IRCBOT_PINGRESPONDER_HPP
#define IRCBOT_PINGRESPONDER_HPP

#include <memory>

#include "Operation.hpp"

namespace ircbot
{

class IrcConnector;

class PingResponder : public Operation
{
 public:

  PingResponder();
  ~PingResponder();

  void consume(std::string const match) override;

};

}

#endif
