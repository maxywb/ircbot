import random
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
    "asdf" : "lol"
}

POSITIVE_ADJ = [
    "wonderful",
    "amazing",
    "jaw-dropping",
    "sickening",
    "astounding",
    "great",
    "excellent",
    "top tier",
    "elite"
]

ENDING_ADJ = [
    "so proud of you",
    "very happy for you",
    "envious of you",
    "gonna make it brah",
    "plebs in your presence",
    "peons compared to you",
    "jealous of dem financial gains"
]

class HelloResponder(derived.pyircbot.PythonOperation):
    def __init__(self, irc_connector):
        super(HelloResponder, self).__init__(irc_connector)

    def consume(self, line):
        try:
            try:
                who, what, where, message = split_privmsg(line)
            except IndexError:
                return

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
                start = POSITIVE_ADJ[random.randrange(len(POSITIVE_ADJ))]
                end = ENDING_ADJ[random.randrange(len(ENDING_ADJ))]
                self._irc_connection.privmsg(where, "%s investing %s, we're all %s!" % (start, who[0], end))

        except Exception as e:
            print e
