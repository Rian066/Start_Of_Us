# Name:  Rian M Alif
# Email: rian.alif58@myhunter.cuny.edu
# Date: December 14, 2024
# This program converts binary to decimal

binary = input("Enter binary number: ")

decNum = 0

for i in binary:
    decNum = decNum * 2
    if i == "1":
        decNum += 1

print(decNum)
