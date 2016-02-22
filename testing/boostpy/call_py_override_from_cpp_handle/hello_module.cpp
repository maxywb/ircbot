#include <boost/python.hpp>

#include "hello.hpp"

namespace hello {
BOOST_PYTHON_MODULE(hello)
{
  boost::python::class_<Parent>("Parent", boost::python::init<std::string>())
      .def("foo", &Parent::foo)
      .def_readonly("name",
                    &Parent::name)
      .add_property("value",
                    &Parent::get_value,
                    &Parent::set_value);

  // allow python subclass overrides
  boost::python::class_<ParentWrapper, boost::noncopyable>("Parent", boost::python::init<std::string>())
      .def("foo",
           &Parent::foo,
           &ParentWrapper::default_foo)
      .def_readonly("name",
                    &ParentWrapper::name)
      .add_property("value",
                    &ParentWrapper::get_value,
                    &ParentWrapper::set_value);

  boost::python::class_<Child,
                        boost::python::bases<Parent> >(
                            "Child", boost::python::init<std::string>())
      .def_readonly("name",
                    &Child::name)
      .add_property("value",
                    &Child::get_value,
                    &Child::set_value);

}

}
