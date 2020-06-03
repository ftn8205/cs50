from sys import argv, exit
import csv


def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)
    else:
        peopleDict = {}
        STRDict = {}
        maxMatch = []
        with open(argv[2]) as seqFile:
            seq = csv.reader(seqFile)
            for row in seq:
                dnaList = row
                # print(len(dnaList[0]))

        with open(argv[1]) as dnaFile:
            people = csv.DictReader(dnaFile)

            for row in people:
                STRDict = row
                STRDict.pop('name')
                # print(STRDict.keys())

            # find repeat STR
            for STR in STRDict:
                countRepeat(STR, dnaList, maxMatch)

            # print(f"maxMatch:{maxMatch}")
            
        # match people
        with open(argv[1]) as dnaFile:
            rows = csv.DictReader(dnaFile)
            
            found = False
            for row in rows:
                peopleDict = row
                # print(peopleDict)
                
                p = 0
                for STR in STRDict:
                    # print(f"{peopleDict[STR]}", end=" ")
                    if int(peopleDict[STR]) == maxMatch[p]:
                        p = p + 1
                    if p == (len(STRDict)):
                        print(peopleDict['name'])
                        found = True
                        break
                # print(f"P:{p}")
            if (found == False):
                print("No match")        


def countRepeat(STR, dnaList, maxMatch):
    maxCount = 0
    dnaData = dnaList[0]
    dnaLength = len(dnaData)
    # print(f"{STR}, {dnaData}")

    for i in range(dnaLength):
        count = 0
        if dnaData[i:i+len(STR)] == STR:
            # print(f"i:{i}")
            count = count + 1
            while dnaData[i:i+len(STR)] == dnaData[i+len(STR):i+2*len(STR)]:
                # print(f"while:{i}")
                count = count + 1
                i = i + len(STR)
        if count > maxCount:
            # print(f"count:{count}")
            maxCount = count
    maxMatch.append(maxCount)
    if maxCount == 0:
        maxMatch.append(0)

      
main()

