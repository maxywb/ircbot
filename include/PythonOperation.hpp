#ifndef IRCBOT_PYTHONOPERATION_HPP
#define IRCBOT_PYTHONOPERATION_HPP

#include <string>

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "assert.hpp"
#include "Operation.hpp"

namespace ircbot
{

class IrcConnector;

// allow python subclass overrides
class PythonOperation : public Operation, public boost::python::wrapper<Operation>                        
{
 public:
  PythonOperation() = default;
  PythonOperation(boost::shared_ptr<IrcConnector> ircConnection);

  void consume(std::string const line) override;

  void setConnector(boost::shared_ptr<IrcConnector> ircConnection);
  boost::shared_ptr<IrcConnector> getConnector();
};

}

#endif
