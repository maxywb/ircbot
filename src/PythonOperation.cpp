#include <boost/python.hpp>

#include <string>

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "Operation.hpp"
#include "PythonOperation.hpp"

namespace ircbot
{
PythonOperation::PythonOperation(boost::shared_ptr<IrcConnectorInterface> ircConnection,
                                 boost::shared_ptr<SqlConnector> sqlConnector,
                                 boost::shared_ptr<ConfigurationManager> configManager)
    : Operation(ircConnection, sqlConnector, configManager)
{
  // empty
}

void PythonOperation::consume(std::string const line)
{
  boost::python::override override = this->get_override("consume");
  override(line);
}

void PythonOperation::setConnector(boost::shared_ptr<IrcConnectorInterface> ircConnection)
{
  ircConnection_ = ircConnection;
}

boost::shared_ptr<IrcConnectorInterface> PythonOperation::getConnector()
{
  return ircConnection_;
}

}


