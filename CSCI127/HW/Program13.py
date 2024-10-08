#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: September 30, 2024
#This program outputs a given message from the last letter to first letter

message = input("Enter a message: ")

for i in range(len(message) - 1, -1, -1):
    print(message[i],message[i])
