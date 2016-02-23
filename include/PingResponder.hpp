#ifndef IRCBOT_PINGRESPONDER_HPP
#define IRCBOT_PINGRESPONDER_HPP

#include <boost/shared_ptr.hpp>

#include "Operation.hpp"

namespace ircbot
{

class IrcConnectorInterface;

class PingResponder : public Operation
{
 private:
  PingResponder();
 public:
  PingResponder(boost::shared_ptr<IrcConnectorInterface> ircConnection);
  ~PingResponder();

  void consume(std::string const match) override;

};

}

#endif
