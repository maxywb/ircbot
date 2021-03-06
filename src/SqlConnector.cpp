#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

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

std::unordered_map<std::string, std::unordered_set<std::string>> SqlConnector::getOperations()
{

  std::string const get_channels("select * from operations;");
  std::unordered_map<std::string, std::unordered_set<std::string>> operations;

  sqlite3_stmt * get_channels_stmt;
  sqlite3_prepare(db_,
                  get_channels.c_str(),
                  get_channels.length(),
                  &get_channels_stmt,                           
                  nullptr);

  int step = sqlite3_step(get_channels_stmt);
  while(step == SQLITE_ROW){ 
    std::string channel( reinterpret_cast<char const*>(sqlite3_column_text(get_channels_stmt, 1)));
    std::string operation( reinterpret_cast<char const*>(sqlite3_column_text(get_channels_stmt, 2)));


    if (operations.count(channel) == 0) {
      operations[channel] = std::unordered_set<std::string>();
    }

    operations[channel].insert(operation);

    std::cout << channel << " " << operation << std::endl;

    step = sqlite3_step(get_channels_stmt);
  } 

  sqlite3_finalize(get_channels_stmt);

  return operations;
}

std::string SqlConnector::getNick()
{
  std::string const get_nick("select * from misc where key = \"nick\" limit 1;");
  std::string nick;

  sqlite3_stmt * stmt;
  sqlite3_prepare(db_,
                  get_nick.c_str(),
                  get_nick.length(),
                  &stmt,                           
                  nullptr);

  int step = sqlite3_step(stmt);

  nick = std::string(reinterpret_cast<char const*>(sqlite3_column_text(stmt, 2)));

  sqlite3_finalize(stmt);

  return nick;

}

std::string SqlConnector::getPassword()
{
  std::string const get_password("select * from misc where key = \"password\" limit 1;");
  std::string password;

  sqlite3_stmt * stmt;
  sqlite3_prepare(db_,
                  get_password.c_str(),
                  get_password.length(),
                  &stmt,                           
                  nullptr);

  int step = sqlite3_step(stmt);

  password = std::string(reinterpret_cast<char const*>(sqlite3_column_text(stmt, 2)));

  sqlite3_finalize(stmt);

  return password;

}

std::string SqlConnector::getAdminNick()
{
  std::string const get_admin_nick("select * from misc where key = \"admin_nick\" limit 1;");
  std::string admin_nick;

  sqlite3_stmt * stmt;
  sqlite3_prepare(db_,
                  get_admin_nick.c_str(),
                  get_admin_nick.length(),
                  &stmt,                           
                  nullptr);

  int step = sqlite3_step(stmt);

  admin_nick = std::string(reinterpret_cast<char const*>(sqlite3_column_text(stmt, 2)));

  sqlite3_finalize(stmt);

  return admin_nick;
}

std::string SqlConnector::getAdminHost()
{
  std::string const get_admin_hostmask("select * from misc where key = \"admin_hostmask\" limit 1;");
  std::string admin_hostmask;

  sqlite3_stmt * stmt;
  sqlite3_prepare(db_,
                  get_admin_hostmask.c_str(),
                  get_admin_hostmask.length(),
                  &stmt,                           
                  nullptr);

  int step = sqlite3_step(stmt);

  admin_hostmask = std::string(reinterpret_cast<char const*>(sqlite3_column_text(stmt, 2)));

  sqlite3_finalize(stmt);

  return admin_hostmask;
}
}
