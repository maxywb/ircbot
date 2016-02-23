#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "hello.hpp"

namespace hello {
Parent::Parent(boost::shared_ptr<Other> name)
    : name(name)
{
  // empty
}

void Parent::set_name(std::string new_name)
{
  name->set_name(new_name);
}

std::string Parent::get_name()
{
  return name->get_name();
}

std::string Parent::foo()
{
  return "Parent " +  get_name();
}

ParentWrapper::ParentWrapper(boost::shared_ptr<Other> name)
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

Child::Child(boost::shared_ptr<Other> name)
    : Parent(name)
{
  // empty
}

std::string Child::foo()
{
  return "Child " + name->get_name();
}

}
