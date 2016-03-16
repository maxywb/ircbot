import sqlite3

import derived.pyircbot

from .util import (
    IGNORE_USERS,
    split_privmsg,
)

class SqlRecorder(derived.pyircbot.PythonOperation):
    def __init__(self, irc_connector):
        super(SqlRecorder, self).__init__(irc_connector)
        
        # ATTN: do something smarter about creating this in the consumer thread
        self._db_connection = None
        self._db_cursor = None

        self._log_command = '''
        insert into privmsg_log(id, channel, nick, hostname, message)
        values(NULL, ?, ?, ?, ?);
        '''

        self._hostname_exempt_list = [
            "ctcp@ctcp-scanner.rizon.net",
            "break.out.another.thousand",
        ]

    def consume(self, line):
        try:
            try:
                who, what, where, message = split_privmsg(line)
            except IndexError:
                return

            if len(message) <=0:
                return

            if who[0] in IGNORE_USERS:
                return

            if what != "PRIVMSG":
                return

            if who[1] in self._hostname_exempt_list:
                return

            if self._db_connection is None:
                self._db_connection = sqlite3.connect("/home/meatwad/.ircbot.db", check_same_thread=False)
                self._db_cursor = self._db_connection.cursor()

            self._db_cursor.execute(self._log_command, (where, who[0], who[1], ' '.join(message)))
            self._db_connection.commit()

        except Exception as e:
            print "SqlRecorder exception:", e
