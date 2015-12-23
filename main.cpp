#include <atomic>
#include <string>
#include <memory>
#include <chrono>
#include <signal.h>

#include "IrcConnector.hpp"
#include "HighlightHandler.hpp"
#include "PingResponder.hpp"
#include "OperationManager.hpp"

std::atomic<bool> running_s(true);

void signal_handler(int /*signal*/)
{
  running_s = false;
}

int main(void) {
  
  signal (SIGINT, signal_handler);
  signal (SIGTERM, signal_handler);

  std::string const nick = "boatz";
  std::string const server = "irc.rizon.net";
  size_t const port = 7000;

  std::shared_ptr<ircbot::IrcConnector> connector =
      std::make_shared<ircbot::IrcConnector>();

  std::shared_ptr<ircbot::PingResponder> pingResponder =
      std::make_shared<ircbot::PingResponder>(connector);

  std::shared_ptr<ircbot::HighlightHandler> highlightHandler =
      std::make_shared<ircbot::HighlightHandler>(connector);

  ircbot::OperationManager operationManager(connector);

  operationManager.addOperation(pingResponder);
  operationManager.addOperation(highlightHandler);

  operationManager.start();

  connector->connect(server, port);
  connector->user(nick);
  connector->nick(nick);

  std::this_thread::sleep_for(std::chrono::seconds(2));

  connector->join("#boatz");

  connector->privmsg("#boatz", "asdf fdsa qwer rewq");

  while (running_s) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  operationManager.stop();
  operationManager.join();

}
