#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>

#include "assert.hpp"
#include "IrcConnectorInterface.hpp"
#include "PingResponder.hpp"

namespace ircbot
{

PingResponder::PingResponder(boost::shared_ptr<IrcConnectorInterface> ircConnection,
                             boost::shared_ptr<SqlConnector> sqlConnector)
    : Operation(ircConnection, sqlConnector)
{



}

PingResponder::~PingResponder()
{

}

void PingResponder::consume(std::string const line)
{
  if (line.find("PING") == 0) {


    std::vector<std::string> strs;
    boost::split(strs, line, boost::is_any_of(" "));

    ircConnection_->pong(strs[1]);

  } 
}

}
