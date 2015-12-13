#include <iostream>

#include <boost/algorithm/string.hpp>

#include "assert.hpp"
#include "IrcConnector.hpp"
#include "PingResponder.hpp"

namespace ircbot
{

PingResponder::PingResponder()
{

  std::cout << "ping responder" << std::endl;

}

PingResponder::~PingResponder()
{

}

void PingResponder::consume(std::string const line)
{
  if (line.find("PING") == 0) {


    std::vector<std::string> strs;
    boost::split(strs, line, boost::is_any_of(" "));

    ircConnection_->pong(strs[1]);

  } 
}

}
