import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Correct usage: python dna.py CSVFILE DNAFILE")

    # TODO: Read database file into a variable
    subjects = []

    with open(sys.argv[1], newline='') as file:
        reader = csv.DictReader(file)
        for row in reader:
            subjects.append(row)

    # print('subjects: ', subjects)

    subsequences = [sequence for sequence in subjects[0].keys() if sequence != 'name']
    # print('subsequences: ', subsequences)

    # TODO: Read DNA sequence file into a variable

    dna = ''

    with open(sys.argv[2], "r") as file:
        dna = file.read()
    # print('dna: ', dna)

    # TODO: Find longest match of each STR in DNA sequence

    results = {}

    for sub in subsequences:
        results[sub] = longest_match(dna, sub)
    # print('results: ', results)

    # TODO: Check database for matching profiles

    match = 'No match'

    for i in range(len(subjects)):
        match_count = 0
        for sub in subsequences:
            if int(subjects[i][sub]) == results[sub]:
                match_count += 1
        if match_count == len(subsequences):
            match = subjects[i]['name']

    print(match)


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

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
