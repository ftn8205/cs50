# TODO
from sys import argv, exit
import csv
import cs50

if len(argv) != 2:
    print("argv is not equal to 2")
    exit(1)

open(f"students.db", "w").close()

db = cs50.SQL("sqlite:///students.db")

db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")

with open(argv[1], "r") as titles:
    reader = csv.DictReader(titles)

    for row in reader:
        rowSplit = row["name"].split(" ")
        print(row["name"].split(" "))
        if len(rowSplit) == 2:
            first = rowSplit[0]
            middle = None
            last = rowSplit[1]
        else:
            first = rowSplit[0]
            middle = rowSplit[1]
            last = rowSplit[2]
            
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   first, middle, last, row["house"], int(row["birth"]))
