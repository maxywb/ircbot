#ifndef IRCBOT_COMMANDHANDLER_HPP
#define IRCBOT_COMMANDHANDLER_HPP

#include <string>

#include <boost/shared_ptr.hpp>

#include "Operation.hpp"

namespace ircbot
{

class IrcConnector;
class OperationManager;
class SqlConnector;

class CommandHandler : public Operation
{
 private:
  CommandHandler();
  boost::shared_ptr<ircbot::OperationManager> operationManager_;

 public:
  CommandHandler(boost::shared_ptr<IrcConnector> ircConnection,
                 boost::shared_ptr<SqlConnector> sqlConnector,
                 boost::shared_ptr<ConfigurationManager> configManager,
                 boost::shared_ptr<OperationManager> operationManager);

  ~CommandHandler();

  void consume(std::string const match) override;

};

}

#endif
