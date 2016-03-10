import derived.pyircbot

from .util import split_privmsg

RESPONSE = {
    "nice":"nice",
    "hi":"hi",
    "hello":"hi",
    "bonjour":"hi",
    "sup":"sup",
    "word":"no doubt",
    "nice":"nice",
    "bye":"pce",
    "!eth":None,
}

class HelloResponder(derived.pyircbot.PythonOperation):
    def __init__(self, irc_connector):
        super(HelloResponder, self).__init__(irc_connector)

    def consume(self, line):
        try:
            who, what, where, message = split_privmsg(line)

            if len(message) <=0:
                return

            command = message[0].lower()

            if len(message) != 1:
                return

            try:
                response = RESPONSE[command]
            except IndexError:
                return

            if response is not None:
                self._irc_connection.privmsg(where, response)

            if command == "!eth" and "Angelina" in who[1]:
                self._irc_connection.privmsg(where, "excellent investing bp, we're all proud of you!")

        except Exception as e:
            print e
