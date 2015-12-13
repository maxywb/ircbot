#include <string>
#include <memory>

#include <boost/algorithm/string.hpp>

#include "IrcConnector.hpp"
#include "PingResponder.hpp"

int main(void) {
  
  std::string const nick = "boatz";
  std::string const server = "irc.rizon.net";
  size_t const port = 7000;

  std::shared_ptr<ircbot::IrcConnector> connector =
      std::make_shared<ircbot::IrcConnector>();

  ircbot::PingResponder pingResponder;

  pingResponder.subscribe(connector);

  connector->connect(server, port);



  // this will at most 5 seconds due to timeout, by then rizon will be ready
  for (int i = 0; i < 5; ++i) {  
    std::string buf = connector->read();
    std::vector<std::string> lines;
    boost::split(lines, buf, boost::is_any_of("\n"));

    for (auto line : lines) {
      pingResponder.consume(line);
    }

  }

  connector->user(nick);
  connector->nick(nick);

  // this will at most 5 seconds due to timeout, by then rizon will be ready
  for (int i = 0; i < 5; ++i) {  
    std::string buf = connector->read();
    std::vector<std::string> lines;
    boost::split(lines, buf, boost::is_any_of("\n"));

    for (auto line : lines) {
      pingResponder.consume(line);
    }

  }

  connector->join("#boatz");


  while (true) {
    
    std::string buf = connector->read();
    std::vector<std::string> lines;
    boost::split(lines, buf, boost::is_any_of("\n"));

    for (auto line : lines) {
      pingResponder.consume(line);
    }
  }
  connector->quit();
}
