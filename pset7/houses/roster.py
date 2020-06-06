# TODO
import cs50
from sys import argv, exit

db = cs50.SQL("sqlite:///students.db")

if len(argv) != 2:
    print("argv number should be 2")
    exit(1)

r = db.execute(f"SELECT first,middle,last,birth FROM students WHERE house = '{argv[1]}' ORDER BY last, first")

for row in r:
    if row['middle'] != None:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['last']}, born {row['birth']}")

