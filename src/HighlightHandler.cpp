#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "assert.hpp"
#include "IrcConnectorInterface.hpp"
#include "HighlightHandler.hpp"

namespace ircbot
{

HighlightHandler::HighlightHandler(boost::shared_ptr<IrcConnectorInterface> ircConnection)
    : Operation(ircConnection)
{
  // empty
}

HighlightHandler::~HighlightHandler()
{
  // empty
}

void HighlightHandler::consume(std::string const line)
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
