# Stack Operations

inputString = input("Word: ")

charArray = list(inputString)

newArray = []

for char in charArray:
    if newArray and newArray[-1] == char:
        newArray.pop()
    else:
        newArray.append(char)

print("".join(newArray))


# String Manipulation

'''
inputString = input("Word: ")

newString = ""

for i in range(len(inputString)):
        if len(newString) > 0 and newString[-1] == inputString[i]:
            newString = newString[:-1]
        else:
            newString += inputString[i]

print(newString) 
'''