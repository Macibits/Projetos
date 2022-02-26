from cs50 import get_float

# Input change by user
while True:
    change = get_float("Change owed: ")
    if change >= 0:
        break

# Declare variable coins and cents
coins = 0
cents = int(change * 100)

# Reduce each coin of change and count coin
while cents >= 25:
    cents -= 25
    coins += 1

while cents >= 10:
    cents -= 10
    coins += 1

while cents >= 5:
    cents -= 5
    coins += 1

while cents >= 1:
    cents -= 1
    coins += 1

# Print minimum coins needed
print(coins)