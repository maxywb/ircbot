#ifndef IRCBOT_OPERATIONMANAGER_HPP
#define IRCBOT_OPERATIONMANAGER_HPP

#include <atomic>
#include <map>
#include <thread>

#include <boost/shared_ptr.hpp>

namespace ircbot
{

class Operation;
class IrcConnectorInterface;

class OperationManager
{
 private:
  std::map<std::string, boost::shared_ptr<Operation> > operations_;

  boost::shared_ptr<IrcConnectorInterface> ircConnection_;

  std::atomic<bool> running_;

  std::thread worker_;

  OperationManager(){};
  void run();
  void step();
 public:

  explicit OperationManager(boost::shared_ptr<IrcConnectorInterface> ircConnection);

  void start();

  void stop();

  void join();

  void addOperation(std::string const name,
                    boost::shared_ptr<Operation> operation);
  bool hasOperation(std::string const & name);
  void removeOperation(std::string const & name);

};

}

#endif
