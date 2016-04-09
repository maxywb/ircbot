#include <iostream>
#include <string>
#include <unordered_set>

#include <sqlite3.h> 

#include "assert.hpp"
#include "SqlConnector.hpp"

namespace ircbot
{
SqlConnector::SqlConnector(std::string db_filename)
{
  int status = sqlite3_open(db_filename.c_str(), &db_);
}

SqlConnector::~SqlConnector()
{
  sqlite3_close(db_);
}

void SqlConnector::logPrivmsg(std::string const & where, std::string const & nick, std::string const & hostmask, std::string const & message)
{
  sqlite3_stmt * log_privmsg_stmt_;
  sqlite3_prepare(db_,
                  log_privmsg_text_.c_str(),
                  log_privmsg_text_.length(),
                  &log_privmsg_stmt_,                           
                  nullptr);

  sqlite3_bind_text(log_privmsg_stmt_,
                    1,
                    where.c_str(),
                    where.length(),
                    nullptr);

  sqlite3_bind_text(log_privmsg_stmt_,
                    2,
                    nick.c_str(),
                    nick.length(),
                    nullptr);

  sqlite3_bind_text(log_privmsg_stmt_,
                    3,
                    hostmask.c_str(),
                    hostmask.length(),
                    nullptr);

  sqlite3_bind_text(log_privmsg_stmt_,
                    4,
                    message.c_str(),
                    message.length(),
                    nullptr);

  sqlite3_step(log_privmsg_stmt_);
  sqlite3_finalize(log_privmsg_stmt_);
}

std::unordered_set<std::string> SqlConnector::getChannels()
{

  std::string const get_channels("select * from channels;");
  std::unordered_set<std::string> channels;

  sqlite3_stmt * get_channels_stmt;
  sqlite3_prepare(db_,
                  get_channels.c_str(),
                  get_channels.length(),
                  &get_channels_stmt,                           
                  nullptr);

  int step = sqlite3_step(get_channels_stmt);
  while(step == SQLITE_ROW){ 
    channels.emplace(reinterpret_cast<char const*>(sqlite3_column_text(get_channels_stmt, 1)));

    step = sqlite3_step(get_channels_stmt);
  } 

  sqlite3_finalize(get_channels_stmt);

  return channels;
}

}
