#ifndef IRCBOT_OPERATIONMANAGER_HPP
#define IRCBOT_OPERATIONMANAGER_HPP

#include <atomic>
#include <forward_list>
#include <memory>
#include <thread>

namespace ircbot
{

class Operation;
class IrcConnector;

class OperationManager
{
 private:
  std::forward_list<std::shared_ptr<Operation> > operations_;

  std::shared_ptr<IrcConnector> ircConnection_;

  std::atomic<bool> running_;

  std::thread worker_;

  OperationManager(){};
  void run();

 public:

  explicit OperationManager(std::shared_ptr<IrcConnector> ircConnection);

  void start();
  void stop();

  void join();

  void addOperation(std::shared_ptr<Operation> operation);

};

}

#endif
