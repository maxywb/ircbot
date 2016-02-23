#ifndef IRCBOT_OPERATIONMANAGER_HPP
#define IRCBOT_OPERATIONMANAGER_HPP

#include <atomic>
#include <forward_list>
#include <thread>

#include <boost/shared_ptr.hpp>

namespace ircbot
{

class Operation;
class IrcConnector;

class OperationManager
{
 private:
  std::forward_list<boost::shared_ptr<Operation> > operations_;

  boost::shared_ptr<IrcConnector> ircConnection_;

  std::atomic<bool> running_;

  std::thread worker_;

  OperationManager(){};
  void run();

 public:

  explicit OperationManager(boost::shared_ptr<IrcConnector> ircConnection);

  void start();
  void stop();

  void join();

  void addOperation(boost::shared_ptr<Operation> operation);

};

}

#endif
