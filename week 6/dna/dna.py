import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python /database /sequence")
        return 1
    database_file = sys.argv[1]
    sequence_file = sys.argv[2]

    # TODO: Read database file into a variable
    people = []
    with open(database_file, "r") as database:
        database_reader = csv.DictReader(database)
        for row in database_reader:
            people.append(row)
        # print(people)


        # create a list of subsequences, read first line, remove the \n, then split them into an array
    with open(database_file, "r") as database_header_file:
        database_first_line = database_header_file.readline().rstrip()
        database_header = database_first_line.split(",")
        # print(database_header)

    # TODO: Read DNA sequence file into a variable
    with open(sequence_file, "r") as sequence:
        sequence_reader = sequence.read()

    # TODO: Find longest match of each STR in DNA sequence
    str_count = {}
    for str in database_header:
        if str == 'name':
            # print("name")
            pass
        else:
            counter = longest_match(sequence_reader, str)
            str_count[str] = counter
            # print(str_count)

    # TODO: Check database for matching profiles

    for person in people:
        match = True
        for str in person:
            if str == 'name':
                # print(person[str])
                pass
            elif int(person[str]) != str_count[str]:
                # print(person[str])
                # print(str_count[str])
                match = False
                break
        if match == True:
            matching_person = person['name']
            print("{}".format(matching_person))
            break
    if match == False:
        print('No match')

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
