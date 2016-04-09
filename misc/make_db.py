#!/usr/bin/env python
import sqlite3
import sys

if len(sys.argv) <= 2:
    print "must supply db name"
    sys.exit()

db_name = sys.argv[1]

try:
    testing = sys.argv[2] == "--test"
    print "TESTING"
except:
    testing = False

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

create_channels = '''
      CREATE TABLE channels(
       id INTEGER PRIMARY KEY NOT NULL,
       channel TEXT NOT NULL
      );
'''

create_operations = '''
      CREATE TABLE operations(
       id INTEGER PRIMARY KEY NOT NULL,
       channel TEXT NOT NULL,
       operation TEXT NOT NULL
      );
'''


if testing:
    populate_channels = [
        """insert into channels(id, channel)
      values(NULL, 'boatz');""",
    ]

    populate_operations = [
        """insert into operations(id, channel, operation)
      values(NULL, 'boatz', 'hello');""",
    ]
else:
    populate_channels = [
        """insert into channels(id, channel)
      values(NULL, 'boatz');""",
        """insert into channels(id, channel)
      values(NULL, 'lifting');""",
        """insert into channels(id, channel)
      values(NULL, '/diy/');""",
    ]

    populate_operations = [
        """insert into operations(id, channel, operation)
      values(NULL, 'boatz', 'hello');""",
        """insert into operations(id, channel, operation)
      values(NULL, 'lifting', 'hello');""",
        """insert into operations(id, channel, operation)
      values(NULL, '/diy/', 'hello');""",
    ]


db_cursor.execute(create_privmsg_log)

db_cursor.execute(create_channels)
db_cursor.execute(create_operations)

for config in populate_channels:
    db_cursor.execute(config)

for config in populate_operations:
    db_cursor.execute(config)

db_connection.commit()

db_connection.close()
