from cs50 import get_string


def main():

    # Get text from user
    text = get_string("Text: ")

    # Calculate index
    grade = count_grade(text)

    # Print grade
    if grade <= 1:
        print("Before Grade 1")
    elif grade >= 2 and grade <= 15:
        print(f"Grade {grade}")
    else:
        print("Grade 16+")


def count_letters(text):
    # Declare variable letters
    letters = 0

    # Count letters
    for i in range(len(text)):
        if ord(text[i]) >= 65 and ord(text[i]) <= 90:
            letters += 1
        elif ord(text[i]) >= 97 and ord(text[i]) <= 122:
            letters += 1

    return letters


def count_words(text):
    # Declare variable words
    words = 1

    # Count words
    for i in range(len(text)):
        if ord(text[i]) == 32:
            words += 1

    return words


def count_sentences(text):
    # Declare variable sentences
    sentences = 0

    # Count sentences
    for i in range(len(text)):
        if ord(text[i]) == 33 or ord(text[i]) == 46 or ord(text[i]) == 63:
            sentences += 1

    return sentences


def count_grade(text):
    # Get variables for Coleman-Liau
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    L = letters / words * 100
    S = sentences / words * 100

    # Calculate grade
    I = 0.0588 * L - 0.296 * S - 15.8
    I = round(I)
    return I


main()