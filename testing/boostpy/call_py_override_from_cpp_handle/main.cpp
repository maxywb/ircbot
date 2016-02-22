#include <iostream>
#include <string>

#include <boost/python.hpp>

#include "hello.hpp"

int main(int argc, char ** argv)
{
  Py_Initialize();

  try {
    boost::python::object main_module = boost::python::import("__main__");
    boost::python::object main_namespace = main_module.attr("__dict__");

    boost::python::object ignored = boost::python::exec(
        "from test import * \n"
        "py_child = PyChild('Q') \n"
        "test() \n",
        main_namespace);

    hello::Parent & pyChild = boost::python::extract<hello::Parent&>(main_namespace["py_child"]);

    std::cout << pyChild.foo() << std::endl;

  } catch (boost::python::error_already_set const &) {
    PyErr_Print();
  }

  return 0;
}
