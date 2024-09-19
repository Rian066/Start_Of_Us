inputString = input("Word: ")

charArray = list(inputString)

newArray = []

for char in charArray:
    if newArray and newArray[-1] == char:
        newArray.pop()
    else:
        newArray.append(char)

print("".join(newArray))