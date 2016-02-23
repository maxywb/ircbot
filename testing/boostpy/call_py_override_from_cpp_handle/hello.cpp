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

std::string Parent::foo(int n)
{
  return "Parent " +  name;
}

ParentWrapper::ParentWrapper(std::string name)
    : Parent(name)
{
  // empty
}

std::string ParentWrapper::foo(int n)
{
  if (boost::python::override overridedFoo = this->get_override("foo")) {
    return overridedFoo(n);
  }
  return Parent::foo(n);
}

std::string ParentWrapper::default_foo(int n)
{
  return this->Parent::foo(n);
}

Child::Child(std::string name)
    : Parent(name)
{
  // empty
}

std::string Child::foo(int n)
{
  return "Child " +  name;
}

}
