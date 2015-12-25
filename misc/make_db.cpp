#include <iostream>
#include <string>

#include <sqlite3.h>

static int callback(void */*unused*/,
                    int argc,
                    char ** argv,
                    char ** colName)
{

  for (size_t i = 0; i < argc; ++i){
    std::cout << colName[i] << " = "
              << (argv[i] ? argv[i] : "NULL" )
              << std::endl;
  }

  return 0;
}

bool execute_sql_statement(sqlite3 * db,
                           char const * const statement)
{
  std::cout << "executing statement: "
            << statement << std::endl;

  char * errorMessage = nullptr;
  int const status = sqlite3_exec(db,
                                  statement,
                                  callback,
                                  0,
                                  &errorMessage);

  if(status != SQLITE_OK ){
    std::cout << "SQL error: " << errorMessage
              << std::endl;

    sqlite3_free(errorMessage);

    return false;
  }else{
    std::cout << "Table created successfully"
              << std::endl;

    return true;
  }
}

void make_tables(std::string const db_file)
{

  sqlite3 * db;

  // open db 
  if (sqlite3_open(db_file.c_str(), &db)){
    std::cout << "Can't open database: "
              << sqlite3_errmsg(db) << std::endl;
    exit(0);
  } else{
    std::cout << "Opened database successfully"
              << std::endl;
  }

  // privmsg-log
  // id, channel, user, message
  // 
  char const * make_privmsg_log =
      "CREATE TABLE privmsg_log(" \
      " id INTEGER PRIMARY KEY NOT NULL AUTOINCREMENT," \
      " channel TEXT NOT NULL," \
      " user TEXT NOT NULL," \
      " message TEXT NOT NULL" \
      ");";

  execute_sql_statement(db, make_privmsg_log);

  // config
  // id, tag, config
  // 
  char const * make_config =
      "CREATE TABLE config(" \
      " id INTEGER PRIMARY KEY NOT NULL," \
      " tag TEXT NOT NULL," \
      " config TEXT NOT NULL" \
      ");";

  execute_sql_statement(db, make_config);

  sqlite3_close(db);
}

void populate_initial(std::string const db_file)
{

  sqlite3 * db;

  // open db 
  if (sqlite3_open(db_file.c_str(), &db)){
    std::cout << "Can't open database: "
              << sqlite3_errmsg(db) << std::endl;
    exit(0);
  } else{
    std::cout << "Opened database successfully"
              << std::endl;
  }

  // config
  // id, tag, config
  // 
  char const * populate_config =
      "insert into config(id, tag, config)" \
      "insert into config(id, tag, config)" \
      "values(NULL, 'channel','/g/spam');" \
      "insert into config(id, tag, config)" \
      "values(NULL, 'channel','boatz');" \
      "insert into config(id, tag, config)" \
      "values(NULL, 'channel','lifting');" \
      "insert into config(id, tag, config)" \
      "values(NULL, 'channel','/diy/');" \
      ;
  execute_sql_statement(db, populate_config);

  sqlite3_close(db);
}

int main(int argc, char ** argv)
{

  if (argc != 3) {
    std::cout << "wrong number of arguments" << std::endl;
    return -1;
  }

  std::string const command(argv[2]);
  std::string const db_file(argv[1]);

  if (command == "--make-tables") {
    make_tables(db_file);
  } else if (command == "--populate-initial") {
    populate_initial(db_file);
  } else{
    std::cout << "unknown option: " << argv[1] << std::endl;
    return -1;
  }

  return 0;
}
