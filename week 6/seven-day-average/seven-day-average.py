import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")

    # converts to list
    file = decoded_content.splitlines()

    # converts each list to a dictionary
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    previousDay = {}
    newCases = {}

    for row in reader:
        state = row['state']
        cases = int(row['cases'])
        # date = row['date']

        if state not in previousDay:
            previousDay[state] = cases
            newCases[state] = []
        else:
            # subtract previous day's cases from cases
            newCase = cases - previousDay[state]

            # check if the list is full, otherwise push this value into the list.
            if state not in newCases:
                newCases[state] = []

            if len(newCases[state]) >= 14:
                newCases[state].pop(0)
            newCases[state].append(newCase)

            # update previous day value for this state
            previousDay[state] = cases

    return newCases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):

    for state in states:
        # get the corresponding value (list) of new cases in the past 14 days
        newCases = new_cases[state]

        # get the sum of the first 7 days
        firstHalf = newCases[:7]
        firstSum = 0
        for day in firstHalf:
            firstSum += day
        try:
            firstAverage = firstSum / len(firstHalf)
        except ZeroDivisionError:
            print("zero division error")

        # get the sum of the last 7 days
        secondHalf = newCases[7:14]
        secondSum = 0
        for day in secondHalf:
            secondSum += day
        try:
            secondAverage = round(secondSum / len(secondHalf))
        except ZeroDivisionError:
            print("zero division error")

        # calculate percentage change using try exception
        try:
            percentChange = round((secondAverage - firstAverage) / firstAverage * 100)
        except ZeroDivisionError:
            print("zero division error")

        if percentChange > 0:
            print("{} had a 7-day average of {} and an increase of {}%.".format(state, secondAverage, percentChange))
        else:
            print("{} had a 7-day average of {} and a decrease of {}%.".format(state, secondAverage, percentChange))

main()
