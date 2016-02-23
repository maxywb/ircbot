#ifndef IRCBOT_BASEOPERATION_HPP
#define IRCBOT_BASEOPERATION_HPP

#include <string>

#include <boost/shared_ptr.hpp>

#include "Operation.hpp"

namespace ircbot
{

class IrcConnector;

class BaseOperation : public Operation
{
 private:
  BaseOperation();
 public:
  BaseOperation(boost::shared_ptr<IrcConnector> ircConnection);
  ~BaseOperation();

  void consume(std::string const match) override;

};

}

#endif
