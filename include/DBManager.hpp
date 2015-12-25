#ifndef IRCBOT_DBMANAGER_HPP
#define IRCBOT_DBMANAGER_HPP

#include <memory>
#include <string>

#include "Operation.hpp"

namespace ircbot
{

class IrcConnector;

class DBManager : public Operation
{
 private:
  DBManager();

  sqlite3 * db_;

 public:
  DBManager(std::string const db_file,
            std::shared_ptr<IrcConnector> ircConnection);
  ~DBManager();

  void consume(std::string const match) override;

};

}

#endif
