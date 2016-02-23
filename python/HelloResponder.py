import derived.pyircbot

from .util import split_privmsg

class HelloResponder(derived.pyircbot.PythonOperation):
    def __init__(self, irc_connector):
        super(HelloResponder, self).__init__(irc_connector)

    def consume(self, line):
        try:
            who, what, where, message = split_privmsg(line)

            print len(message), message
            if message[0] == "hi":
                print "got one"
                self._irc_connection.privmsg(where, "hi %s" % who[0])
        except Exception as e:
            print "\n\n\n\n\n", e,  "\n\n\n\n\n"
