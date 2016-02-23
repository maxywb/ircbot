#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>

#include "assert.hpp"
#include "IrcConnector.hpp"
#include "BaseOperation.hpp"

namespace ircbot
{

BaseOperation::BaseOperation(boost::shared_ptr<IrcConnector> ircConnection)
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
  std::vector<std::string> strs;
  boost::split(strs, line, boost::is_any_of(" \n"));

  std::string const & who = strs[0];
  std::string const & type = strs[1];
  std::string const & dest = strs[2];
  std::string const & target = strs[3];

  if (!(type == "PRIVMSG"
        && dest[0] == '#'
        && (target == ":boatz"
            || target == ":boatz:")
        )) {
    return;
  }

  ircConnection_->privmsg(dest, "no thanks");
}

}
