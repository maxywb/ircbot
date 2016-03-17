
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "IrcConnector.hpp"
#include "PythonOperation.hpp"
#include "SqlConnector.hpp"

namespace ircbot
{

BOOST_PYTHON_MODULE(pyircbot)
{
  boost::python::class_<SqlConnector,
                        boost::noncopyable>("SqlConnector",
                                            boost::python::init<std::string>())
      .def("log_privmsg", &SqlConnector::log_privmsg);

  boost::python::register_ptr_to_python<boost::shared_ptr<SqlConnector>>();

  boost::python::class_<IrcConnector,
                        boost::noncopyable>("IrcConnector",
                                            boost::python::init<>())
      .def("join",&IrcConnector::join)
      .def("nick", &IrcConnector::nick)
      .def("privmsg", &IrcConnector::privmsg)
      .def("user", &IrcConnector::user);

  boost::python::register_ptr_to_python<boost::shared_ptr<IrcConnector>>();

  boost::python::class_<PythonOperation,
                        boost::noncopyable>("PythonOperation",
                                            boost::python::init<boost::shared_ptr<IrcConnector>,
                                            boost::shared_ptr<SqlConnector> >())
      .def("consume", boost::python::pure_virtual(&Operation::consume))
      .def_readwrite("_irc_connection", &Operation::ircConnection_)
      .def_readwrite("_sql_connector", &Operation::sqlConnector_);


  
}
}
