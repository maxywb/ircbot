#ifndef IRCBOT_HIGHLIGHTHANDLER_HPP
#define IRCBOT_HIGHLIGHTHANDLER_HPP

#include <memory>
#include <string>

#include "Operation.hpp"

namespace ircbot
{

class IrcConnector;

class HighlightHandler : public Operation
{
 private:
  HighlightHandler();
 public:
  HighlightHandler(std::shared_ptr<IrcConnector> ircConnection);
  ~HighlightHandler();

  void consume(std::string const match) override;

};

}

#endif
