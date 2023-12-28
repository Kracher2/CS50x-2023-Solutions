import csv
import sys


def main():
    # Check if correct number of command-line arguments is provided
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Open CSV database file and read its contents into list of dictionaries
    with open(sys.argv[1]) as db_file:
        reader = csv.DictReader(db_file)
        db = [row for row in reader]

    # Open DNA sequence file and read its contents
    with open(sys.argv[2]) as dna_file:
        dna = dna_file.read()

    # Count occurrences of each STR in DNA sequence
    counts = {}
    for key in db[0].keys():
        if key == "name":
            continue
        counts[key] = longest_match(dna, key)

    # Check if there is a matching profile in database
    for row in db:
        match = True
        for key in row.keys():
            if key == "name":
                continue
            if int(row[key]) != counts[key]:
                match = False
                break
        if match:
            print(row["name"])
            return

    # If no match is found, print a message
    print("No match")


def longest_match(sequence, subsequence):
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
