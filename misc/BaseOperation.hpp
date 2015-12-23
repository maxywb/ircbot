#ifndef IRCBOT_BASEOPERATION_HPP
#define IRCBOT_BASEOPERATION_HPP

#include <memory>
#include <string>

#include "Operation.hpp"

namespace ircbot
{

class IrcConnector;

class BaseOperation : public Operation
{
 private:
  BaseOperation();
 public:
  BaseOperation(std::shared_ptr<IrcConnector> ircConnection);
  ~BaseOperation();

  void consume(std::string const match) override;

};

}

#endif
