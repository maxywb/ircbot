#include <atomic>
#include <chrono>
#include <list>
#include <signal.h>
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

int main(int argc, char ** argv) {

  Py_Initialize();

  signal (SIGINT, signal_handler);
  signal (SIGTERM, signal_handler);

  std::string const nick = "boatzzzz";
  std::string const server = "irc.rizon.net";
  size_t const port = 7000;

  boost::shared_ptr<ircbot::SqlConnector> sqlConnector =
      boost::make_shared<ircbot::SqlConnector>("/home/meatwad/.ircbot.db");

  boost::shared_ptr<ircbot::IrcConnector> connector =
      boost::make_shared<ircbot::IrcConnector>();

  boost::shared_ptr<ircbot::ConfigurationManager> configManager =
      boost::make_shared<ircbot::ConfigurationManager>(connector, sqlConnector);

  boost::shared_ptr<ircbot::OperationManager> operationManager =
      boost::make_shared<ircbot::OperationManager>(connector);

  operationManager->addOperation(
      "CommandHandler",
      boost::make_shared<ircbot::CommandHandler>(
          ircbot::CommandHandler(connector, sqlConnector, configManager, operationManager)));

  operationManager->addOperation(
      "PingResponder",
      boost::make_shared<ircbot::PingResponder>(
          ircbot::PingResponder(connector, sqlConnector, configManager)));

  try {
    boost::python::object mainModule = boost::python::import("__main__");
    boost::python::object mainNamespace = mainModule.attr("__dict__");

    boost::python::object derivedModule = boost::python::import("derived.pyircbot");

    mainNamespace["irc_connector"] = connector;
    mainNamespace["sql_connector"] = sqlConnector;
    mainNamespace["config_manager"] = configManager;

    boost::python::object ignored = boost::python::exec("import python \n"
                                                        "sql_recorder = python.SqlRecorder(irc_connector, sql_connector, config_manager) \n"
                                                        "h = python.HelloResponder(irc_connector, sql_connector, config_manager) \n"
                                                        "bots = python.BotResponder(irc_connector, sql_connector, config_manager) \n",
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

    boost::shared_ptr<ircbot::PythonOperation> botResponder =
        boost::python::extract<boost::shared_ptr<ircbot::PythonOperation>>(mainNamespace["bots"]);
    operationManager->addOperation(
        "BotResponder",
        botResponder);

  connector->connect(server, port);

  operationManager->start();  
  configManager->configureBot();


  while (running_s) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  connector->quit();

  operationManager->stop();
  operationManager->join();

  } catch (boost::python::error_already_set const &) {
    PyErr_Print();
  }

}

#if 0

// TODO read in python file or something nice to initialize python variables
#include <fstream>
#include <sstream>

  std::ifstream password_file("/home/meatwad/.ircbot.password");
  std::stringstream password_buffer;
  password_buffer << password_file.rdbuf();

#endif
