#include <iostream>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/make_shared.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "assert.hpp"
#include "IrcConnector.hpp"
#include "CommandHandler.hpp"
#include "Operation.hpp"
#include "OperationManager.hpp"
#include "PythonOperation.hpp"
#include "SqlConnector.hpp"

namespace ircbot
{

CommandHandler::CommandHandler(boost::shared_ptr<IrcConnector> ircConnection,
                               boost::shared_ptr<SqlConnector> sqlConnector,
                               boost::shared_ptr<ConfigurationManager> configManager,
                               boost::shared_ptr<OperationManager> operationManager)
    : Operation(ircConnection, sqlConnector, configManager),
      operationManager_(operationManager)
{
  // empty
}

CommandHandler::~CommandHandler()
{
  // empty
}

void CommandHandler::consume(std::string const line)
{

  return; //ATTN doesn't do anything

  
  std::vector<std::string> strs;
  boost::split(strs, line, boost::is_any_of(" \n\r\t"));

  if (strs.size() < 5) {
    return;
  }

  // strip trailling newline
  std::string & last = strs[strs.size() - 1];
  last.substr(0, last.length() - 2);
  strs[strs.size() - 1] = last;

  std::string const & who = strs[0];
  std::string const & type = strs[1];
  std::string const & dest = strs[2];
  std::string const & target = strs[3];
  std::string const & command = strs[4];

  if (!(type == "PRIVMSG"
        && dest[0] == '#'
        && (target == ":boatzzz"
            || target == ":boatzzz:")
        )) {
    return;
  }



  ircConnection_->privmsg(dest, "done.");
}

}
