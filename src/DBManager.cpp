#include <iostream>

#include <boost/algorithm/string.hpp>
#include <sqlite3.h>

#include "assert.hpp"
#include "IrcConnector.hpp"
#include "DBManager.hpp"

namespace ircbot
{

DBManager::DBManager(std::string const db_file,
                     std::shared_ptr<IrcConnector> ircConnection)
    : Operation(ircConnection)
{
  // open db 
  int status = sqlite3_open(db_file.c_str(), &db_);

  ASSERT(status, "can't connect to db");
}

DBManager::~DBManager()
{
  // empty
}

void DBManager::consume(std::string const line)
{
  if (line.find("example") == 0) {


    std::vector<std::string> strs;
    boost::split(strs, line, boost::is_any_of(" "));

    ircConnection_->pong(strs[1]);

  } 
}

}
