from cs50 import get_string

word = get_string("Greeting: ").lower().strip()
start = word[0]

if "hello" in word:
    print("${}".format(0))
elif start == 'h':
    print("${}".format(20))
else:
    print("${}".format(100))

