#include <boost/python.hpp>
using namespace boost::python;

namespace {
class Parent
{
 public:
  Parent() = default;

  Parent(std::string name)
      : name(name),
        value()
  {
    // empty
  }

  virtual ~Parent() = default;

  void set_value(float new_value)
  {
    value = new_value;
  }

  float get_value()
  {
    return value;
  }

  std::string const name;

  virtual std::string foo()
  {
    return "Parent " +  name;
  }

 private:  
  float value;
};


// allow python subclass overrides
class ParentWrapper : public Parent, public wrapper<Parent>
{
 public:
  ParentWrapper() {}

  ParentWrapper(std::string name)
      : Parent(name)
  {
    // empty
  }

  std::string foo()
  {
    if (override f = this->get_override("foo")) {
      return foo();
    }
    return Parent::foo();
  }

  std::string default_foo()
  {
    return this->Parent::foo();
  }
};

class Child : public Parent
{
 public:
  Child() = default;

  Child(std::string name)
      : Parent(name)
  {
    // empty
  }

  virtual std::string foo() override
  {
    return "Child " +  name;
  }
  
};

}

BOOST_PYTHON_MODULE(hello)
{
  class_<Parent>("Parent", init<std::string>())
      .def("foo", &Parent::foo)
      .def_readonly("name",
                    &Parent::name)
      .add_property("value",
                    &Parent::get_value,
                    &Parent::set_value);

  // allow python subclass overrides
  class_<ParentWrapper, boost::noncopyable>("Parent", init<std::string>())
      .def("foo",
           &Parent::foo,
           &ParentWrapper::default_foo)
      .def_readonly("name",
                    &Child::name)
      .add_property("value",
                    &Child::get_value,
                    &Child::set_value);

  class_<Child, bases<Parent> >("Child", init<std::string>())
      .def_readonly("name",
                    &Child::name)
      .add_property("value",
                    &Child::get_value,
                    &Child::set_value);

}

