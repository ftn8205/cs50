from cs50 import get_float

while True:
    n = get_float("Change owed: ")
    if n > 0:
        num25 = (n * 100) // 25
        remainMoney = (n * 100) % 25
        print(f"num1: {num25}, {remainMoney}")
        num10 = remainMoney // 10
        remainMoney = remainMoney % 10
        print(f"num2: {num10}, {remainMoney}")
        num5 = remainMoney // 5
        remainMoney = remainMoney % 5
        print(f"num3: {num5}, {remainMoney}")
        num1 = remainMoney // 1
        remainMoney = remainMoney % 1
        print(f"num4: {num1}, {remainMoney}")
        print(f"{int(num25 + num10 + num5 + num1)}")
        break