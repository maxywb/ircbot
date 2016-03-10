#include <iostream>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/python.hpp>

#include "assert.hpp"
#include "IrcConnector.hpp"
#include "CommandHandler.hpp"

namespace ircbot
{

CommandHandler::CommandHandler(boost::shared_ptr<IrcConnector> ircConnection,
                               boost::shared_ptr<OperationManager> operationManager)
    : Operation(ircConnection),
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
        && (target == ":boatz"
            || target == ":boatz:")
        )) {
    return;
  }

  if (command == "reload" ) {
    if (strs.size() < 6) {
      return;
    }

    for (auto i : strs) {
      std::cout << "^ " << i << std::endl;
    }

    std::string const & module = strs[5];

    std::stringstream reload_command;
    reload_command << module << " = reload("  << module << ") \n";

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "# " << reload_command.str().c_str() << " #" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    try {
      boost::python::object mainModule = boost::python::import("__main__");
      boost::python::object mainNamespace = mainModule.attr("__dict__");

      boost::python::object ignored = boost::python::exec(reload_command.str().c_str(),
                                                          mainNamespace);
    
    } catch (boost::python::error_already_set const &) {
      ircConnection_->privmsg(dest, "check your logs, bro. something bad happened.");    
        
      PyErr_Print();
      return;
    }

  }

  ircConnection_->privmsg(dest, "done.");
}

}
