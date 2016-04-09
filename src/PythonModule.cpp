
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "IrcConnector.hpp"
#include "PythonOperation.hpp"
#include "SqlConnector.hpp"
#include "ConfigurationManager.hpp"

namespace ircbot
{

BOOST_PYTHON_MODULE(pyircbot)
{
  // sql connector
  boost::python::class_<SqlConnector,
                        boost::noncopyable>("SqlConnector",
                                            boost::python::init<std::string>())
      .def("log_privmsg", &SqlConnector::logPrivmsg);
  boost::python::register_ptr_to_python<boost::shared_ptr<SqlConnector>>();

  // irc connecotr
  boost::python::class_<IrcConnector,
                        boost::noncopyable>("IrcConnector",
                                            boost::python::init<>())
      .def("join",&IrcConnector::join)
      .def("nick", &IrcConnector::nick)
      .def("privmsg", &IrcConnector::privmsg)
      .def("user", &IrcConnector::user);
  boost::python::register_ptr_to_python<boost::shared_ptr<IrcConnector>>();

  // python operation base class
  boost::python::class_<PythonOperation,
                        boost::noncopyable>("PythonOperation",
                                            boost::python::init<boost::shared_ptr<IrcConnector>,
                                            boost::shared_ptr<SqlConnector>,
                                            boost::shared_ptr<ConfigurationManager>>())
      .def("consume", boost::python::pure_virtual(&Operation::consume))
      .def_readwrite("_irc_connection", &Operation::ircConnection_)
      .def_readwrite("_sql_connector", &Operation::sqlConnector_)
        .def_readwrite("_config_manager", &Operation::configManager_);

  // configuration manager
  boost::python::class_<ConfigurationManager,
                        boost::noncopyable>("ConfigurationManager",
                                            boost::python::init<boost::shared_ptr<IrcConnector>,
                                            boost::shared_ptr<SqlConnector> >())
      .def("enable_operation", &ConfigurationManager::enableOperation)
      .def("disable_operation", &ConfigurationManager::disableOperation)
      .def("is_enabled", &ConfigurationManager::isEnabled);
  boost::python::register_ptr_to_python<boost::shared_ptr<ConfigurationManager>>();

  
}
}
