import sys
import random
import derived.pyircbot

from .util import (
    split_privmsg,
)

class BotResponder(derived.pyircbot.PythonOperation):
    def __init__(self, irc_connector, sql_connector, config_manager):
        super(BotResponder, self).__init__(irc_connector, sql_connector, config_manager)

    def consume(self, line):
        try:
            try:
                who, what, where, message = split_privmsg(line)
            except IndexError:
                return

            if len(message) <=0 and len(message) != 1:
                return

            command = message[0].lower()

            if command in [".bots", "!bots"]:
                self._irc_connection.privmsg(where,
                                             "Reporting in! [C++/Python] https://github.com/maxywb/ircbot")

        except Exception as e:
            print "BotResponder exception:", type(e), e

