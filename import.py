import cs50
from sys import argv, exit
import csv

open("students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")
db.execute("CREATE TABLE students (id INTEGER PRIMARY KEY AUTOINCREMENT, first VARCHAR(255), middle VARCHAR(255), last VARCHAR(255), house VARCHAR(10), birth INTEGER)")

if len(argv) != 2:
    print("Usage: import.py file.csv")
    exit(1)

with open(argv[1], 'r') as file:
    reader = csv.DictReader(file)

    for row in reader:

        name_list = row["name"].split()
        first = name_list[0]
        if len(name_list) == 2:
            middle = None
            last = name_list[1]
        elif len(name_list) == 3:
            middle = name_list[1]
            last = name_list[2]

        house = row["house"]
        birth = int(row["birth"])

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", first, middle, last, house, birth)