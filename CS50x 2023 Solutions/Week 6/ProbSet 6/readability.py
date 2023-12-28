from cs50 import get_string
from sys import exit

words = 1
letters = 0
sentences = 0

text = get_string("Text: ")

for c in text:
    if c.isalpha() == True:
        letters += 1
    elif c == " ":
        words += 1
    elif c in ["!", "?", "."]:
        sentences += 1

index = 0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8

if index < 1:
    print("Before Grade 1")
    exit(0)

index = round(index)

if index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
