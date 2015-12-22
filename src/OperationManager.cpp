#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#include <boost/algorithm/string.hpp>

#include "assert.hpp"
#include "IrcConnector.hpp"
#include "Operation.hpp"
#include "OperationManager.hpp"

namespace ircbot
{


OperationManager::OperationManager(std::shared_ptr<IrcConnector> ircConnection)
    : running_(true),
      ircConnection_(ircConnection)
{
  // empty
}

void OperationManager::start()
{
  running_ = true;

  worker_ = std::thread(&OperationManager::run, this);

}

void OperationManager::stop()
{
  running_ = false;
}

void OperationManager::run()
{
  while (running_) {
    std::string buf = ircConnection_->read();
    std::vector<std::string> lines;
    boost::split(lines, buf, boost::is_any_of("\n"));

    for (auto operation : operations_) {
      for (auto line : lines) {
        operation->consume(line);
      }
    }
  }
}

void OperationManager::join()
{
  worker_.join();
}

void OperationManager::addOperation(std::shared_ptr<Operation> operation)
{
  operations_.push_front(operation);
}

}
