#ifndef IRCBOT_SQLCONNECTOR_HPP
#define IRCBOT_SQLCONNECTOR_HPP

#include <string>
#include <unordered_set>
#include <unordered_map>

#include <sqlite3.h> 

#include "assert.h"

namespace ircbot
{

class SqlConnector 
{
 private:

  sqlite3 * db_;

  std::string const log_privmsg_text_ =
      "insert into privmsg_log(id, channel, nick, hostname, message) \n"\
      "values(NULL, ?,?,?,?);";

 public:
  SqlConnector(){
    ASSERT(false, "Unimplemented default constructor");
  }
  SqlConnector(std::string db_filename);
  ~SqlConnector();

  void logPrivmsg(std::string const & where, std::string const & nick, std::string const & hostmask, std::string const & message);
  std::unordered_set<std::string> getChannels();
  std::unordered_map<std::string, std::unordered_set<std::string>> getOperations();

  std::string getNick();
  std::string getPassword();
  std::string getAdminNick();
  std::string getAdminHost();
};

}

#endif
