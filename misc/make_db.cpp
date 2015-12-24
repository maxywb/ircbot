#include <iostream>

#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName){

  for(size_t i = 0; i < argc; ++i){
    std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL" )<< std::endl;
  }

  return 0;
}


int main()
{

  sqlite3 *db;

  int rc = sqlite3_open("/tmp/test.db", &db);

  // open db 
  if (rc){
    std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    exit(0);
  } else{
    std::cout << "Opened database successfully" << std::endl;
  }

  // construct statement
  char const * sql = "CREATE TABLE COMPANY("            \
                     "ID INT PRIMARY KEY     NOT NULL," \
                     "NAME           TEXT    NOT NULL," \
                     "AGE            INT     NOT NULL," \
                     "ADDRESS        CHAR(50)," \
                     "SALARY         REAL );";

  // execute statement
  char * errorMessage = nullptr;
  rc = sqlite3_exec(db, sql, callback, 0, &errorMessage);
  if( rc != SQLITE_OK ){
    std::cout << "SQL error: " << errorMessage << std::endl;
    sqlite3_free(errorMessage);
  }else{
    std::cout << "Table created successfully" << std::endl;
  }

  sqlite3_close(db);
  return 0;
}
