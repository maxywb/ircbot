import derived.pyircbot

from .util import split_privmsg

class HelloResponder(derived.pyircbot.PythonOperation):
    def __init__(self, irc_connector):
        super(HelloResponder, self).__init__(irc_connector)

    def consume(self, line):
        try:
            who, what, where, message = split_privmsg(line)

            if len(message) <=0:
                return

            if message[0] == "hi" and len(message) == 1:
                self._irc_connection.privmsg(where, "hi %s" % who[0])

            if message[0] == "hello" and len(message) == 1:
                self._irc_connection.privmsg(where, "hello %s" % who[0])

            if message[0] == "sup" and len(message) == 1:
                self._irc_connection.privmsg(where, "sup")

            if message[0] == "word" and len(message) == 1:
                self._irc_connection.privmsg(where, "no doubt")

        except Exception as e:
            print e
