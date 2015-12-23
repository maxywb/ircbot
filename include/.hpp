#ifndef IRCBOT_FOOBAR_HPP
#define IRCBOT_FOOBAR_HPP

#include <memory>
#include <string>

#include "Operation.hpp"

namespace ircbot
{

class IrcConnector;

class FooBar : public Operation
{
 private:
  FooBar();
 public:
  FooBar(std::shared_ptr<IrcConnector> ircConnection);
  ~FooBar();

  void consume(std::string const match) override;

};

}

#endif
