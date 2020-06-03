from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n > 0 and n < 9:
        for i in range(n):
            for j in range(n):
                if j < n - i - 1:
                    print(" ", end="")
                else:
                    print("#", end="")
            print("\n", end="")
        break