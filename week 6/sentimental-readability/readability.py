# TODO
text = input("Text: ")

sum_of_letters = 0
sum_of_words = 0
sum_of_sentences = 0

for character in text:
    if character.isalpha():
        sum_of_letters += 1
    elif character == " ":
        sum_of_words += 1
    elif character == "." or character == "!" or character == "?":
        sum_of_sentences += 1

sum_of_words += 1

L = sum_of_letters / sum_of_words * 100
S = sum_of_sentences / sum_of_words * 100

index = round(0.0588 * L - 0.296 * S - 15.8)
if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print("Grade {}".format(index))