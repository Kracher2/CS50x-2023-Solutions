from cs50 import get_string


def main():
    card = get_string("Number: ")
    if isValid(card):
        type = getType(card)
        print(type)
    else:
        print("INVALID")


def isValid(card):
    digits = [int(digit) for digit in card]

    total = 0

    for i in range(len(digits) - 2, -1, -2):
        num = digits[i] * 2
        total += (num % 10) + int((num / 10))

    for i in range(len(digits) - 1, -1, -2):
        total += digits[i]

    return total % 10 == 0


def getType(card):
    first_two = int(card[:2])
    if len(card) == 15 and (first_two == 34 or first_two == 37):
        return "AMEX"
    elif len(card) == 16 and ((51 <= first_two <= 55)):
        return "MASTERCARD"
    elif (len(card) == 13 or len(card) == 16) and int(card[0]) == 4:
        return "VISA"
    else:
        return "INVALID"


if __name__ == "__main__":
    main()
