from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n > 0 and n < 9:
        for i in range(n):
            for j in range(2*n+2):
                if j < n - 1 - i:
                    print(" ", end="")
                elif j >= n - 1 - i and j < n:
                    print("#", end="")
                elif j == n or j == n + 1:
                    print(" ", end="")
                elif j > n + 1 and j <= n + 2 + i:
                    print("#", end="")
            print("")
        break