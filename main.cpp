#include <atomic>
#include <chrono>
#include <fstream>
#include <list>
#include <signal.h>
#include <sstream>
#include <string>

#include <boost/make_shared.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "CommandHandler.hpp"
#include "ConfigurationManager.hpp"
#include "HighlightHandler.hpp"
#include "IrcConnector.hpp"
#include "OperationManager.hpp"
#include "PingResponder.hpp"
#include "PythonOperation.hpp"
#include "SqlConnector.hpp"

std::atomic<bool> running_s(true);

void signal_handler(int /*signal*/)
{
  running_s = false;
}

int main(void) {
  
  Py_Initialize();

  signal (SIGINT, signal_handler);
  signal (SIGTERM, signal_handler);

  std::string const nick = "boatzzzz";
  std::string const server = "irc.rizon.net";
  size_t const port = 7000;

  boost::shared_ptr<ircbot::IrcConnector> connector =
      boost::make_shared<ircbot::IrcConnector>();

  boost::shared_ptr<ircbot::SqlConnector> sqlConnector =
      boost::make_shared<ircbot::SqlConnector>("/home/meatwad/.ircbot.db");

  boost::shared_ptr<ircbot::ConfigurationManager> configManager =
      boost::make_shared<ircbot::ConfigurationManager>(sqlConnector);

  boost::shared_ptr<ircbot::OperationManager> operationManager =
      boost::make_shared<ircbot::OperationManager>(connector);

  operationManager->addOperation(
      "CommandHandler",
      boost::make_shared<ircbot::CommandHandler>(
          ircbot::CommandHandler(connector, sqlConnector, operationManager)));

  operationManager->addOperation(
      "PingResponder",
      boost::make_shared<ircbot::PingResponder>(
          ircbot::PingResponder(connector, sqlConnector)));

  try {
    boost::python::object mainModule = boost::python::import("__main__");
    boost::python::object mainNamespace = mainModule.attr("__dict__");

    boost::python::object derivedModule = boost::python::import("derived.pyircbot");

    mainNamespace["irc_connector"] = connector;
    mainNamespace["sql_connector"] = sqlConnector;
    mainNamespace["config_manager"] = configManager;

    boost::python::object ignored = boost::python::exec("import python \n"
                                                        "sql_recorder = python.SqlRecorder(irc_connector, sql_connector) \n"
                                                        "h = python.HelloResponder(irc_connector, sql_connector) \n",
                                                        mainNamespace);
    
    boost::shared_ptr<ircbot::PythonOperation> helloHandler =
        boost::python::extract<boost::shared_ptr<ircbot::PythonOperation>>(mainNamespace["h"]);
    operationManager->addOperation(
        "HelloHandler",
        helloHandler);

    boost::shared_ptr<ircbot::PythonOperation> sqlRecorder =
        boost::python::extract<boost::shared_ptr<ircbot::PythonOperation>>(mainNamespace["sql_recorder"]);
    operationManager->addOperation(
        "SqlRecorder",
        sqlRecorder);


  operationManager->start();

  connector->connect(server, port);
  connector->user(nick);
  connector->nick(nick);

  std::this_thread::sleep_for(std::chrono::seconds(5));

  connector->join("#boatz");
  //connector->join("#lifting");
  //connector->join("#/hoc/");

  std::ifstream password_file("/home/meatwad/.ircbot.password");
  std::stringstream password_buffer;
  password_buffer << password_file.rdbuf();

  connector->privmsg("nickserv", "identify " + password_buffer.str());

  while (running_s) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  operationManager->stop();
  operationManager->join();

  } catch (boost::python::error_already_set const &) {
    PyErr_Print();
  }

}
