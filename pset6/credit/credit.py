from cs50 import get_int, get_string

num = get_string("Number: ")

evenNum = 0
oddNum = 0
length = len(num)
number = num[::-1]
# print(number)
for even in range(1, length, 2):
    if int(number[even]) * 2 >= 10:
        # print(number[even])
        evenCount = int(number[even]) * 2 // 10 + int(number[even]) * 2 % 10
        # print(evenCount)
        evenNum = evenNum + evenCount
    else:
        # print(int(number[even]) * 2)
        evenNum = evenNum + int(number[even]) * 2
# print(evenNum)
    
for odd in range(0, length, 2):
    oddNum = oddNum + int(number[odd])
# print(oddNum)

cardValidateHead = 10 * int(num[0]) + int(num[1])

checksum = (evenNum + oddNum) % 10

if checksum == 0:
    if length == 15 and ((cardValidateHead == 34) or (cardValidateHead == 37)): 
        print("AMEX")
    elif length == 16 and ((cardValidateHead >= 51) and (cardValidateHead <= 55)):
        print("MASTERCARD") 
    elif int(num[0]) == 4 and (length == 13 or length == 16):
        print("VISA")  
    else:
        print("INVALID")
else:
    print("INVALID")
