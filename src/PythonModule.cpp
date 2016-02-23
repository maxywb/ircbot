
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "IrcConnector.hpp"
#include "PythonOperation.hpp"

namespace ircbot
{

BOOST_PYTHON_MODULE(pyircbot)
{
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
                                            boost::python::init<boost::shared_ptr<IrcConnector>>())
      .def("consume", boost::python::pure_virtual(&Operation::consume));

}
}
