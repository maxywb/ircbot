#ifndef IRCBOT_CONFIGURATIONMANAGER_HPP
#define IRCBOT_CONFIGURATIONMANAGER_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>

#include <boost/shared_ptr.hpp>

#include "assert.hpp"

namespace ircbot
{

class SqlConnector;
class IrcConnectorInterface;

class ConfigurationManager
{
 private:
  boost::shared_ptr<IrcConnectorInterface> ircConnector_;
  boost::shared_ptr<SqlConnector> sqlConnector_;

  std::unordered_map<std::string, std::unordered_set<std::string>> operations_;
  std::unordered_set<std::string> channels_;

  std::string nick_;
  std::string password_;
  std::string admin_nick_;
  std::string admin_host_;

 public:
  ConfigurationManager(){
    ASSERT(false, "Unimplemented default constructor");
  }

  ConfigurationManager(boost::shared_ptr<IrcConnectorInterface> ircConnector,
                       boost::shared_ptr<SqlConnector> sqlConnector);

  ~ConfigurationManager();

  // enable operation for channel
  void enableOperation(std::string const & operation, std::string const & channel);

  // disable operation for channel
  void disableOperation(std::string const & operation, std::string const & channel);

  bool isEnabled(std::string const & operation, std::string const & channel);

  void configureBot();

  // queries
  bool isAdmin(std::string const & who);
  bool isTalkingToMe(std::string const & target);

  // irc managing
  void join(std::string const & channel);
  void part(std::string const & channel);
};

}

#endif
