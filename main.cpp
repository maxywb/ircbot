#include <atomic>
#include <string>
#include <chrono>
#include <signal.h>

#include <boost/make_shared.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "HighlightHandler.hpp"
#include "IrcConnector.hpp"
#include "OperationManager.hpp"
#include "PingResponder.hpp"
#include "PythonOperation.hpp"

std::atomic<bool> running_s(true);

void signal_handler(int /*signal*/)
{
  running_s = false;
}

int main(void) {
  
  Py_Initialize();

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


  try {
    boost::python::object mainModule = boost::python::import("__main__");
    boost::python::object mainNamespace = mainModule.attr("__dict__");

    boost::python::object derivedModule = boost::python::import("derived.pyircbot");

    mainNamespace["irc_connector"] = connector;


    boost::python::object ignored = boost::python::exec("import python \n"
                                                        "h = python.HelloResponder(irc_connector) \n",
                                                        mainNamespace);
    
    boost::shared_ptr<ircbot::PythonOperation> helloHandler =
        boost::python::extract<boost::shared_ptr<ircbot::PythonOperation>>(mainNamespace["h"]);

    operationManager.addOperation(helloHandler);
    operationManager.addOperation(pingResponder);
    operationManager.addOperation(highlightHandler);


    operationManager.start();

    connector->connect(server, port);
    connector->user(nick);
    connector->nick(nick);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    connector->join("#boatz");
    connector->join("#lifting");
    connector->join("#diy");

    while (running_s) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    operationManager.stop();
    operationManager.join();
  } catch (boost::python::error_already_set const &) {
    PyErr_Print();
  }

}
