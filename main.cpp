#include <atomic>
#include <string>
#include <chrono>
#include <signal.h>

#include <boost/make_shared.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

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
  
  Py_Initialize();
  try {
  boost::python::object mainModule = boost::python::import("__main__");
  boost::python::object mainNamespace = mainModule.attr("__dict__");

  boost::python::object derivedModule = boost::python::import("derived.pyircbot");

#if 0
  boost::python::object ignored = boost::python::exec("import python \n"
                                                      "h = python.HelloResponder \n",
                                                      mainNamespace);
#endif
  } catch (boost::python::error_already_set const &) {
    PyErr_Print();
  }

  return 0;
  signal (SIGINT, signal_handler);
  signal (SIGTERM, signal_handler);

  std::string const nick = "boatz";
  std::string const server = "irc.rizon.net";
  size_t const port = 7000;

  boost::shared_ptr<ircbot::IrcConnector> connector =
      boost::make_shared<ircbot::IrcConnector>();

  boost::shared_ptr<ircbot::PingResponder> pingResponder =
      boost::make_shared<ircbot::PingResponder>(connector);

  boost::shared_ptr<ircbot::HighlightHandler> highlightHandler =
      boost::make_shared<ircbot::HighlightHandler>(connector);

  ircbot::OperationManager operationManager(connector);

  operationManager.addOperation(pingResponder);
  operationManager.addOperation(highlightHandler);

  operationManager.start();

  connector->connect(server, port);
  connector->user(nick);
  connector->nick(nick);

  std::this_thread::sleep_for(std::chrono::seconds(5));

  connector->join("#boatz");

  while (running_s) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  operationManager.stop();
  operationManager.join();

}
