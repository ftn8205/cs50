text = input("Text: ")

numOfChar = 0

for i in range(len(text)):
    if text[i].isalpha():
        numOfChar = numOfChar + 1

numOfWord = len(text.split())

numOfSen = text.count(".") + text.count("!") + text.count("?")

readability = round((numOfChar / numOfWord) * 100 * 0.0588 - (numOfSen / numOfWord) * 100 * 0.296 - 15.8)

# print(f"{numOfChar},{numOfWord},{numOfSen},{readability}")
if readability < 1:
    print("Before Grade 1")
elif readability >= 1 and readability < 16:
    print(f"Grade {readability}")
else:
    print("Grade 16+")