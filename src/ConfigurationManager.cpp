

#include <string>
#include <unordered_map>
#include <set>

#include <iostream>

#include <boost/shared_ptr.hpp>

#include "assert.h"
#include "ConfigurationManager.hpp"
#include "IrcConnectorInterface.hpp"
#include "SqlConnector.hpp"

namespace ircbot {

ConfigurationManager::ConfigurationManager(boost::shared_ptr<IrcConnectorInterface> ircConnector,
                                           boost::shared_ptr<SqlConnector> sqlConnector)
    : ircConnector_(ircConnector),
      sqlConnector_(sqlConnector),
      operations_(),
      channels_()
    
{
  std::cout << "ConfigurationManager" << std::endl;
}

ConfigurationManager::~ConfigurationManager()
{
  std::cout << "~ConfigurationManager" << std::endl;
}

void ConfigurationManager::enableOperation(std::string const & operation, std::string const & channel)
{
  std::cout << "enableOperation " << operation << " " << channel << std::endl;
}

void ConfigurationManager::disableOperation(std::string const & operation, std::string const & channel)
{

  std::cout << "disableOperation " << operation << " " << channel << std::endl;
}

bool ConfigurationManager::isEnabled(std::string const & operation, std::string const & channel)
{
  if (operations_.count(channel) == 0) {
    return false;
  }

  return operations_[channel].count(operation) > 0;
}

void ConfigurationManager::configureBot()
{

  // load channels
  auto pending_channels = sqlConnector_->getChannels();

  for (auto channel : pending_channels) {
    
    ircConnector_->join(channel);
    channels_.insert(channel);
  }

  operations_ = sqlConnector_->getOperations();

}

}