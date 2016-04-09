

#include <string>
#include <unordered_map>
#include <set>

#include <iostream>

#include <boost/shared_ptr.hpp>

#include "assert.h"
#include "ConfigurationManager.hpp"
#include "SqlConnector.hpp"

namespace ircbot {

ConfigurationManager::ConfigurationManager(boost::shared_ptr<SqlConnector> sqlConnector)
    : sqlConnector_(sqlConnector),
      operation_config_()
    
{
  std::cout << "ConfigurationManager" << std::endl;
}

ConfigurationManager::~ConfigurationManager()
{
  std::cout << "~ConfigurationManager" << std::endl;
}

void ConfigurationManager::enableOperation(std::string const & operation, std::string const & channel)
{
  std::cout << "enableOperation" << std::endl;
}


void ConfigurationManager::disableOperation(std::string const & operation, std::string const & channel)
{
  std::cout << "disableOperation" << std::endl;
}


bool ConfigurationManager::isEnabled(std::string const & operation, std::string const & channel)
{
  std::cout << "isEnabled" << std::endl;
}


void ConfigurationManager::save()
{
  std::cout << "save" << std::endl;
}

void ConfigurationManager::load()
{
  std::cout << "load" << std::endl;
}



}
