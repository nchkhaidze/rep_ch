import csv
from sys import argv


def main(argv):
    # prompt for correct usage, read database and sequence files
    if len(argv) != 3:
        print("Usage: dna.py database.csv sequence.txt")
    database_file = open(argv[1])
    database = list(csv.reader(database_file))

    sequence_file = open(argv[2])
    sequence = sequence_file.read()

    STR = database[0][1:]
    # compute the longest run of consecutive STRs
    str_counts = compute_STR(sequence, STR)
    str_counts = [str(x) for x in str_counts]
    # find and print a matching STR set
    for lists in database:
        if lists[1:] == str_counts:
            print(lists[0])
            return
    print("No match")
    database_file.close()
    sequence_file.close()


# compute the longest run of consecutive STR repeats
def compute_STR(sequence, STR):
    str_max = [0 for n in STR]

    for pos in range(len(sequence)):
        for pattern in STR:
            # for each position in sequence check if the STR repeats from there
            # if so, count how many times and compare against the current longest run
            str_repeats = 0
            new_pos = pos
            while new_pos + len(pattern) < len(sequence):
                if sequence[new_pos:new_pos + len(pattern)] == pattern:
                    str_repeats += 1
                    new_pos += len(pattern)
                else:
                    break
            if str_repeats > str_max[STR.index(pattern)]:
                str_max[STR.index(pattern)] = str_repeats
    return str_max


main(argv)