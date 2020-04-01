text = input("Text: ")

letters = 0
for i in text:
    if i.isalpha() == True:
        letters += 1
word_list = text.split()
words = len(word_list)

sentences = text.count(".") + text.count("!") + text.count("?")
index = int(round((0.0588 * letters / words * 100) - (0.296 * sentences / words * 100) - 15.8))
if index >= 1 and index <= 16:
    print("Grade " + str(index))
elif index > 16:
    print("Grade 16+")
else:
    print("Before Grade 1")
