#ifndef IRCBOT_OPERATION_HPP
#define IRCBOT_OPERATION_HPP

#include <boost/shared_ptr.hpp>

#include "assert.hpp"

namespace ircbot
{

class IrcConnectorInterface;
class SqlConnector;

// not pure virtual becuase Boost::Python needs implemented base class to be wrapped28
class Operation
{
 public:
  boost::shared_ptr<IrcConnectorInterface> ircConnection_; // ATTN: public cuz boost::pyton needs to reference it
  boost::shared_ptr<SqlConnector> sqlConnector_; // ATTN: public cuz boost::pyton needs to reference it
  
  Operation()
  {
    ASSERT(false, "Can't implement base Operation class;");
  }

  Operation(boost::shared_ptr<IrcConnectorInterface> ircConnection,
            boost::shared_ptr<SqlConnector> sqlConnector)
      :     ircConnection_(ircConnection),
            sqlConnector_(sqlConnector)
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
