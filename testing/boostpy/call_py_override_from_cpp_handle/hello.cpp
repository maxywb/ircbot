#include <boost/python.hpp>

#include "hello.hpp"

namespace hello {
Parent::Parent(std::string name)
    : name(name),
      value()
{
  // empty
}

void Parent::set_value(float new_value)
{
  value = new_value;
}

float Parent::get_value()
{
  return value;
}

std::string Parent::foo()
{
  return "Parent " +  name;
}

ParentWrapper::ParentWrapper(std::string name)
    : Parent(name)
{
  // empty
}

std::string ParentWrapper::foo()
{
  if (boost::python::override overridedFoo = this->get_override("foo")) {
    return overridedFoo();
  }
  return Parent::foo();
}

std::string ParentWrapper::default_foo()
{
  return this->Parent::foo();
}

Child::Child(std::string name)
    : Parent(name)
{
  // empty
}

std::string Child::foo()
{
  return "Child " +  name;
}

}
