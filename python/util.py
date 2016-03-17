IGNORE_USERS = [
    '_VIPPER_',
]


def split_privmsg(line):
    words = line.split()

    who = words[0]
    what = words[1]
    where = words[2]
    message = words[3:]

    if len(message) <= 0:
        return who, what, where, message

    if message[0].startswith(":"):
        message[0] = message[0][1:]

    if who.startswith(":"):
        who = who[1:]
        
    who = who.split("!")

    return who, what, where, message
