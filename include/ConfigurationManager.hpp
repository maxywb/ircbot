#ifndef IRCBOT_CONFIGURATIONMANAGER_HPP
#define IRCBOT_CONFIGURATIONMANAGER_HPP

#include <string>
#include <unordered_map>
#include <set>

#include <boost/shared_ptr.hpp>

#include "assert.hpp"

namespace ircbot
{

class SqlConnector;

class ConfigurationManager
{
 private:
  boost::shared_ptr<SqlConnector> sqlConnector_;

  std::unordered_map<std::string, std::set<std::string>> operation_config_;


 public:
  ConfigurationManager(){
    ASSERT(false, "Unimplemented default constructor");
  }

  explicit ConfigurationManager(boost::shared_ptr<SqlConnector> sqlConnector);

  ~ConfigurationManager();

  // enable operation for channel
  void enableOperation(std::string const & operation, std::string const & channel);

  // disable operation for channel
  void disableOperation(std::string const & operation, std::string const & channel);

  bool isEnabled(std::string const & operation, std::string const & channel);

  // save to db
  void save();
  // load from db
  void load();

  

};

}

#endif
