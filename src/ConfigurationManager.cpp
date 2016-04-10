

#include <string>
#include <unordered_map>
#include <set>

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/predicate.hpp>

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

  std::cout << channel << " is enabled" << std::endl;

  return operations_[channel].count(operation) > 0;
}

void ConfigurationManager::configureBot()
{
  // load misc
  nick_ = sqlConnector_->getNick();
  password_ = sqlConnector_->getPassword();
  admin_nick_ = ":" + sqlConnector_->getAdminNick();
  admin_host_ = sqlConnector_->getAdminHost();

  ircConnector_->user(nick_);
  ircConnector_->nick(nick_);
  ircConnector_->privmsg("nickserv", "identify " + password_);

  // load channels
  auto pending_channels = sqlConnector_->getChannels();

  for (auto channel : pending_channels) {
    
    ircConnector_->join(channel);
    channels_.insert(channel);
  }

  operations_ = sqlConnector_->getOperations();

}

  bool ConfigurationManager::isAdmin(std::string const & who)
  {
    bool const is_admin = boost::starts_with(who, admin_nick_)
                          && boost::ends_with(who, admin_host_);
    PRINTLN(who << " is admin: " << is_admin);

    return is_admin;
  }

  bool ConfigurationManager::isTalkingToMe(std::string const & target)
  {
    
    bool const talking_to_me = boost::starts_with(target, ":" + nick_);
    return talking_to_me;
  }

  void ConfigurationManager::join(std::string const & channel)
  {
    if (channels_.count(channel) != 0) {
      return;
    }
    channels_.insert(channel);
    ircConnector_->join(channel);

  }

  void ConfigurationManager::part(std::string const & channel)
  {
    if (channels_.count(channel) == 0) {
      return;
    }
    channels_.erase(channel);
    ircConnector_->part(channel);
    
  }

}
