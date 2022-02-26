import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # Read database file into a variable
    dbase = []
    # Open csv file
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)

        # Read if small
        if sys.argv[1] == "databases/small.csv":
            for name in reader:
                name["AGATC"] = int(name["AGATC"])
                name["AATG"] = int(name["AATG"])
                name["TATC"] = int(name["TATC"])
                dbase.append(name)

        # Read if large
        else:
            for name in reader:
                name["AGATC"] = int(name["AGATC"])
                name["TTTTTTCT"] = int(name["TTTTTTCT"])
                name["AATG"] = int(name["AATG"])
                name["TCTAG"] = int(name["TCTAG"])
                name["GATA"] = int(name["GATA"])
                name["TATC"] = int(name["TATC"])
                name["GAAA"] = int(name["GAAA"])
                name["TCTG"] = int(name["TCTG"])
                dbase.append(name)

    # Read DNA sequence file into a variable
    f = open(sys.argv[2])
    arch = f.read()

    # Find longest match of each STR in DNA sequence
    str = {
        "AGATC": longest_match(arch, "AGATC"),
        "TTTTTTCT": longest_match(arch, "TTTTTTCT"),
        "AATG": longest_match(arch, "AATG"),
        "TCTAG": longest_match(arch, "TCTAG"),
        "GATA": longest_match(arch, "GATA"),
        "TATC": longest_match(arch, "TATC"),
        "GAAA": longest_match(arch, "GAAA"),
        "TCTG": longest_match(arch, "TCTG")
    }

    # Check database for matching profiles and print name or no match
    # In small database
    i = 0
    if sys.argv[1] == "databases/small.csv":
        while i < len(dbase):
            if dbase[i]["AGATC"] == str["AGATC"] and dbase[i]["AATG"] == str["AATG"] and dbase[i]["TATC"] == str["TATC"]:
                print(dbase[i]["name"])
                return 0
            else:
                i += 1
        print("No match")
    # In large database
    else:
        while i < len(dbase):
            if dbase[i]["AGATC"] == str["AGATC"] and dbase[i]["TTTTTTCT"] == str["TTTTTTCT"] and dbase[i]["AATG"] == str["AATG"] and dbase[i]["AGATC"] == str["AGATC"] and dbase[i]["TCTAG"] == str["TCTAG"] and dbase[i]["GATA"] == str["GATA"] and dbase[i]["TATC"] == str["TATC"] and dbase[i]["GAAA"] == str["GAAA"] and dbase[i]["TCTG"] == str["TCTG"]:
                print(dbase[i]["name"])
                return 0
            else:
                i += 1
        print("No match")
    return


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
