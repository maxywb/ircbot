import derived.pyircbot

from .util import split_privmsg

class SqlRecorder(derived.pyircbot.PythonOperation):
    def __init__(self, irc_connector):
        super(SqlRecorder, self).__init__(irc_connector)

    def consume(self, line):
        try:
            who, what, where, message = split_privmsg(line)

            if len(message) <=0:
                return

        except Exception as e:
            print e
