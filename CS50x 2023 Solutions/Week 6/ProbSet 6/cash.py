from cs50 import get_float


while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

change = int(change * 100)
total = 0
while change >= 25:
    change -= 25
    total += 1
while change >= 10:
    change -= 10
    total += 1
while change >= 5:
    change -= 5
    total += 1
while change >= 1:
    change -= 1
    total += 1

print(f"{total}")
