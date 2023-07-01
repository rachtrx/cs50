# TODO
import math

while True:
    try:
        inputNumber = int(input("Number: "))
        break
    except ValueError:
        pass

number = str(inputNumber)
length = len(number)
first_index = length - 2
first_sum_of_digits = 0
is_card = False
for digit in range(math.floor(length / 2)):
    first_digit = int(number[first_index])
    first_value = first_digit * 2
    list_of_first_value = str(first_value)
    if len(list_of_first_value) == 2:
        first_value = int(list_of_first_value[0]) + int(list_of_first_value[1])
    first_sum_of_digits += first_value
    first_index -= 2
# print(first_sum_of_digits)

second_index = length - 1
second_sum_of_digits = 0
for digit in range(math.ceil(length / 2)):
    second_digit = int(number[second_index])
    second_sum_of_digits += second_digit
    second_index -= 2
# print(second_sum_of_digits)

total_sum = first_sum_of_digits + second_sum_of_digits
if total_sum % 10 == 0:
    is_card = True


first_two_digits = int(number[0]) * 10 + int(number[1])

if is_card:
    if length == 15 and (first_two_digits == 34 or first_two_digits == 37):
        print("AMEX")

    elif length == 16 and first_two_digits >= 51 and first_two_digits <= 55:
        print("MASTERCARD")

    elif (length == 13 or length == 16) and int(number[0]) == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")