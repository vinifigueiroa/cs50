from cs50 import get_string

MAX_GRADE = 16
MIN_GRADE = 1


def main():
    text = get_string("Text: ")
    letters = float(count_letters(text))
    words = float(count_words(text))
    sentences = float(count_sentences(text))

    # Average number of letters per 100 words
    L = (letters / words) * 100.0
    # Average number of sentences per 100 words
    S = (sentences / words) * 100.0

    # Rounded Coleman-Liau index
    index = round((0.0588 * L) - (0.296 * S) - 15.8)

    # Print the result
    if index > MAX_GRADE:
        print("Grade 16+")
    elif index < MIN_GRADE:
        print("Before Grade 1")
    else:
        print("Grade ", index)


def count_letters(text):
    count = 0
    for char in text:
        if char.isalpha():
            count += 1
    return count

# Assuming each space has a word before it, we count the number of space occurrences.
# We also assume no sentence will ever end or begin with a space


def count_words(text):
    # Add one more word after the last space to count the last word.
    return text.count(" ") + 1

# Count the number os sentences that end in a dot, exclamation point or question mark.
# We ignore abreviations like Ms. and Mr for this assignment.


def count_sentences(text):
    count = 0
    for char in text:
        if is_punct(char):
            count += 1
    return count


def is_punct(char):
    if char == "." or char == "?" or char == "!":
        return True
    else:
        return False


main()
