from cs50 import get_int

while True:
    number = get_int("Enter height\n")
    if number > 0 and number < 9:
        break
for i in range(1, number + 1, 1):
    print(" " * (number - i), end = "")
    print("#" * i, end = "  ")
    print("#" * i)



