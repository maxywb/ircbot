#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "hello.hpp"

namespace hello {

BOOST_PYTHON_MODULE(hello)
{

  boost::python::class_<Other>("Other")
      .add_property("name",
                    &Parent::get_name,
                    &Parent::set_name);

  boost::python::register_ptr_to_python<boost::shared_ptr<Other>>();

  boost::python::class_<Parent>("Parent",
                                boost::python::init<boost::shared_ptr<Other>>())
      .def("foo", &Parent::foo)
      .add_property("name",
                    &Parent::get_name,
                    &Parent::set_name);

  // allow python subclass overrides
  boost::python::class_<ParentWrapper,
                        boost::noncopyable>("Parent",
                                            boost::python::init<boost::shared_ptr<Other>>())
      .def("foo",
           &Parent::foo,
           &ParentWrapper::default_foo)
      .add_property("name",
                    &ParentWrapper::get_name,
                    &ParentWrapper::set_name);

  boost::python::class_<Child,
                        boost::python::bases<Parent>>("Child",
                                                      boost::python::init<boost::shared_ptr<Other>>())
      .add_property("name",
                    &Child::get_name,
                    &Child::set_name);





}

}
