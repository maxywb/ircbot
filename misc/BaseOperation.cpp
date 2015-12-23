#include <iostream>

#include <boost/algorithm/string.hpp>

#include "assert.hpp"
#include "IrcConnector.hpp"
#include "BaseOperation.hpp"

namespace ircbot
{

BaseOperation::BaseOperation(std::shared_ptr<IrcConnector> ircConnection)
    : Operation(ircConnection)
{
  // empty
}

BaseOperation::~BaseOperation()
{
  // empty
}

void BaseOperation::consume(std::string const line)
{
  if (line.find("example") == 0) {


    std::vector<std::string> strs;
    boost::split(strs, line, boost::is_any_of(" "));

    ircConnection_->pong(strs[1]);

  } 
}

}
