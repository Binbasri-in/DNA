from sys import argv, exit
import csv

# check all files are exsit
if len(argv) != 3:
    print("please include dna data and the sequance")
    exit(1)

# read each person as a dictionary
dna_list = []
with open(argv[1], 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        dna_list.append(row)

# read sequances and start analyze
STR_count = {}
with open(argv[2], 'r') as f:
    seq = f.read()

# get the required STRs as needed
STRs = list(dna_list[0])

# start count all STR consicuativly
for STR in STRs:
    if STR == "name":
        continue
    max_count = 0
    for i in range(len(seq)):
        count = 0
        while seq[i: i + len(STR)] == STR:
            i += len(STR)
            count += 1

        cur_count = count
        if cur_count > max_count:
            max_count = cur_count
    STR_count[STR] = max_count

for person in dna_list:
    n = len(STRs) - 1
    match = 0
    for STR in STR_count.keys():
        if person[STR] == str(STR_count[STR]):
            match += 1

    if match == n:
        print(person['name'])
        exit(0)


print('No match')
exit(1)