#!/usr/bin/env python
import sqlite3
import sys

if len(sys.argv) != 2:
    print "must supply db name, and only db name"
    sys.exit()

db_name = sys.argv[1]

db_connection = sqlite3.connect(db_name)


db_cursor = db_connection.cursor()

create_privmsg_log = '''
      CREATE TABLE privmsg_log(
       id INTEGER PRIMARY KEY NOT NULL,
       channel TEXT NOT NULL,
       nick TEXT NOT NULL,
       hostname TEXT NOT NULL,
       message TEXT NOT NULL
      );
'''

create_config = '''
      CREATE TABLE config(
       id INTEGER PRIMARY KEY NOT NULL,
       tag TEXT NOT NULL,
       config TEXT NOT NULL
      );
'''

populate_config = [
      """insert into config(id, tag, config)
      values(NULL, 'channel','/g/spam');""",
      """insert into config(id, tag, config)
      values(NULL, 'channel','boatz');""",
      """insert into config(id, tag, config)
      values(NULL, 'channel','lifting');""",
      """insert into config(id, tag, config)
      values(NULL, 'channel','/diy/');""",
]

db_cursor.execute(create_privmsg_log)

db_cursor.execute(create_config)

for config in populate_config:
    db_cursor.execute(config)

db_connection.commit()

db_connection.close()
