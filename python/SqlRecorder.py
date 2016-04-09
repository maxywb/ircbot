import sqlite3

import derived.pyircbot

from .util import (
    IGNORE_USERS,
    split_privmsg,
)

class SqlRecorder(derived.pyircbot.PythonOperation):
    def __init__(self, irc_connector, sql_connector, config_manager):
        super(SqlRecorder, self).__init__(irc_connector, sql_connector, config_manager)
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

            self._sql_connector.log_privmsg(where, who[0], who[1], ' '.join(message));

        except Exception as e:
            print "SqlRecorder exception:", e
