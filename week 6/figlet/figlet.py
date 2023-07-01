import sys
import random
from pyfiglet import Figlet

figlet = Figlet()

fontList = figlet.getFonts()

if len(sys.argv) != (1 and 3):
    print("Invalid Usage")
    sys.exit(1)

elif len(sys.argv) == 3 and (sys.argv[1] != ('-f' or '--font') or (sys.argv[2] not in fontList)):
    print("Invalid Usage")
    sys.exit(1)

s = input("Input: ")

if len(sys.argv) == 3:
    f = sys.argv[2]
else:
    f = random.choice(fontList)

font = figlet.setFont(font=f)

print(figlet.renderText(s))