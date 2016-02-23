#include <string>

namespace hello {
class Parent
{
 public:
  Parent() = default;

  Parent(std::string name);

  virtual ~Parent() = default;

  void set_value(float new_value);

  float get_value();

  std::string const name;

  virtual std::string foo(int n);

 private:  
  float value;
};


// allow python subclass overrides
class ParentWrapper : public Parent, public boost::python::wrapper<Parent>
{
 public:
  ParentWrapper() = default;

  ParentWrapper(std::string name);

  std::string foo(int n) override;

  std::string default_foo(int n);
};

class Child : public Parent
{
 public:
  Child() = default;

  Child(std::string name);

  virtual std::string foo(int n) override;
  
};

}
