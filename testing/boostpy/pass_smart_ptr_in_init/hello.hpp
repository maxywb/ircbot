#include <string>

#include <boost/shared_ptr.hpp>

namespace hello {

class Other
{
 public:
  Other()
  {
    name = "default";
  }

  Other(std::string new_name)
  {
    name = new_name;
  }

  void set_name(std::string new_name)
  {
    name = new_name;
  }
  
  std::string get_name()
  {
    return name;
  }

 private:
  std::string name;
};

class Parent
{
 public:
  Parent() = default;

  Parent(boost::shared_ptr<Other> name);

  virtual ~Parent() = default;

  void set_name(std::string new_name);

  std::string get_name();

  virtual std::string foo();

 protected:  
  boost::shared_ptr<Other> name;
};


// allow python subclass overrides
class ParentWrapper : public Parent, public boost::python::wrapper<Parent>
{
 public:
  ParentWrapper() = default;

  ParentWrapper(boost::shared_ptr<Other> name);

  std::string foo() override;

  std::string default_foo();
};

class Child : public Parent
{
 public:
  Child() = default;

  Child(boost::shared_ptr<Other> name);

  virtual std::string foo() override;
  
};

}
