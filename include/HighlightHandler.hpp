#ifndef IRCBOT_HIGHLIGHTHANDLER_HPP
#define IRCBOT_HIGHLIGHTHANDLER_HPP

#include <string>

#include <boost/shared_ptr.hpp>


#include "Operation.hpp"

namespace ircbot
{

class IrcConnectorInterface;
class SqlConnector;

class HighlightHandler : public Operation
{
 private:
  HighlightHandler();
 public:
  HighlightHandler(boost::shared_ptr<IrcConnectorInterface> ircConnection,
                   boost::shared_ptr<SqlConnector> sqlConnector);
  ~HighlightHandler();

  void consume(std::string const match) override;

};

}

#endif
