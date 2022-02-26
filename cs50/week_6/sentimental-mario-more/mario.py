from cs50 import get_int

# Accept only int between 1 to 8
while True:
    height = get_int("Height ")
    if height > 0 and height < 9:
        break

# Declare variables to count space and blocks
space = height - 1
block = 1

# Print pyramid
while block <= height:
    print((" " * space)+("#" * block)+"  "+("#" * block))
    block += 1
    space -= 1