from cs50 import get_int

def main():
    number = get_int("Enter credit card number: ")
    digits = [int(n) for n in str(number)]

    valid_len = [13, 15, 16]
    if len(digits) not in valid_len:
        print("INVALID")
        return

    if luhn(digits) == False:
        print("INVALID")
        return

    amex = [34, 37]
    mcard = [51, 52, 53, 54, 55]
    first_two = digits[0] * 10 + digits[1]

    if digits[0] == 4:
        print("VISA")
        return
    elif first_two in amex:
        print("AMEX")
    else:
        print("MASTERCARD")

#returns true if the card is syntactically valid
def luhn(digits):
    every_second = digits[-2::-2]
    every_second = [n * 2 for n in every_second]
    every_second = sum([n % 10 + 1 if n >= 10 else n for n in every_second])
    every_other_sum = sum(digits[-1::-2])

    if (every_other_sum + every_second) % 10 == 0:
        return True
    else:
        return False

main()