
def getYear():
    num = int(input("Type year: "))

    while num > 2021 or num < 2000:
        num = int(input("Type a new year between 2000 and 2021: "))

    return num

getYear()
