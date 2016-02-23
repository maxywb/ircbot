#ifndef IRCBOT_OPERATION_HPP
#define IRCBOT_OPERATION_HPP

#include <boost/shared_ptr.hpp>

#include "assert.hpp"

namespace ircbot
{

class IrcConnector;

// not pure virtual becuase Boost::Python needs implemented base class to be wrapped28
class Operation
{
 protected:
  boost::shared_ptr<IrcConnector> ircConnection_;
  
 public:
  Operation()
  {
    ASSERT(false, "Can't implement base Operation class;");
  }

  Operation(boost::shared_ptr<IrcConnector> ircConnection)
      :     ircConnection_(ircConnection)
  {
  }  

  virtual ~Operation() = default;

  virtual void consume(std::string const match)
  {
    ASSERT(false, "Can't implement base Operation class;");
  }

};

}

#endif
