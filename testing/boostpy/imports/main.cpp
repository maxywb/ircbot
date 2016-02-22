#include <iostream>
#include <string>

#include <boost/python.hpp>


int main(int argc, char ** argv)
{

  std::cout << "main!" << std::endl;

  Py_Initialize();
  try {
    boost::python::object main_module = boost::python::import("__main__");
    boost::python::object main_namespace = main_module.attr("__dict__");


    boost::python::object ignored = boost::python::exec(
        "import os \n"
        "print os.environ['PYTHONPATH'] \n"
        "import sys \n"
        "print sys.path \n"
        "import derived.hello \n"
        " \n"
        "class PyChild(derived.hello.Parent): \n"
        "    def foo(self): \n"
        "        return 'PyChild %s' % self.name \n"
        " \n"
        "class PyChildBase(derived.hello.Parent): \n"
        "    pass \n"
        " \n"
        "parent = derived.hello.Parent('A') \n"
        "child = derived.hello.Child('B') \n"
        "py_child = PyChild('C') \n"
        "py_child_base = PyChildBase('D') \n"
        " \n"
        "parent.value = 12 \n"
        "child.value = 27 \n"
        "py_child.value = 42 \n"
        "py_child_base.value = 99 \n"
        " \n"
        "print parent.foo() \n"
        "print child.foo() \n"
        "print py_child.foo() \n"
        "print py_child_base.foo() \n"
        "",
        main_namespace);
  } catch (boost::python::error_already_set const &) {
    PyErr_Print();
  }
  

  return 0;
}
