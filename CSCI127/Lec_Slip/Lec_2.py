myString = input("Type something: ")

for i in myString:
    uniCode = ord(i) + 1
    asciiValue = chr(uniCode)
    print(i, uniCode, asciiValue)