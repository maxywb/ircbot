#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>

#include "assert.hpp"
#include "IrcConnectorInterface.hpp"
#include "Operation.hpp"
#include "OperationManager.hpp"

namespace ircbot
{


OperationManager::OperationManager(boost::shared_ptr<IrcConnectorInterface> ircConnection)
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

void OperationManager::step()
{
  std::string buf = ircConnection_->read();
  std::vector<std::string> lines;
  boost::split(lines, buf, boost::is_any_of("\n"));

  for (auto operation : operations_) {
    for (auto line : lines) {

      if (line.size() == 0) {
        continue;
      }

      operation.second->consume(line);
    }
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void OperationManager::run()
{
  while (running_) {
    step();
  }
}

void OperationManager::join()
{
  worker_.join();
}

void OperationManager::addOperation(std::string const name,
                                    boost::shared_ptr<Operation> operation)
{
  operations_[name] = operation;
}

bool OperationManager::hasOperation(std::string const & name){
  return false;
}

void OperationManager::removeOperation(std::string const & name){
  return;
}

}
