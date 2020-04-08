import cs50
from sys import argv, exit

if len(argv) != 2:
    print("Usage roster.py name_of_house")
    exit(1)

house = argv[1]
houses = ("gryffindor", "ravenclaw", "hufflepuff", "slytherin")
if house.lower() not in houses:
    print("Incorrect name of house")
    exit(2)

db = cs50.SQL("sqlite:///students.db")
students = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last", house.capitalize())

for student in students:
    first = student['first']
    last = student['last']
    birth = student['birth']
    if student['middle'] != None:
        middle = student['middle']
        print(f"{first} {middle} {last}, born {birth}")
    else:
        print(f"{first} {last}, born {birth}")