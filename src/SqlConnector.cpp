#include <iostream>

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

void SqlConnector::log_privmsg(std::string const & where, std::string const & nick, std::string const & hostmask, std::string const & message)
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

}

