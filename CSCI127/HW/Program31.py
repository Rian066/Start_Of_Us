# Name:  Rian M Alif
# Email: rian.alif58@myhunter.cuny.edu
# Date: November 24, 2024
# This program takes multiple names and prints each name in newline

names = input("Names: ")

nameList = names.split("; ")

for i in nameList:
    lastname, firstname = i.split(", ")
    print(firstname[0] + ".", lastname)
