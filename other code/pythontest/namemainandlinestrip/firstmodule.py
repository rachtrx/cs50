import cs50

words = set()

def main():
    print("__name__ is {}".format(__name__))
    with open("file.txt", "r") as file:
        for line in file:

# 1st experiment
            print(line, end='')
        print('')

# 2nd experiment
        #     word = line.rstrip("ere \n")
        #     words.add(word)
        # for word in words:
        #     print(word)

if __name__ == "__main__":
    main()