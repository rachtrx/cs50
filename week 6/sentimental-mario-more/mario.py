# TODO
while True:
    try:
        height = int(input("Height: "))
        if height >= 1 and height <= 8:
            break
    except ValueError:
        pass

number_of_spaces = height - 1
number_of_hashes = 1
for row in range(height):
    print(number_of_spaces * ' ' + number_of_hashes * '#' + '  ' + number_of_hashes * '#')
    number_of_spaces -= 1
    number_of_hashes += 1
