#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: September 17, 2024
#This program draws based on the given angle

import turtle 

turn0 = input("Enter a numer: ")
turn1 = input("Enter a numer: ")
turn2 = input("Enter a numer: ")
turn3 = input("Enter a numer: ")
turn4 = input("Enter a numer: ")

array = list([turn0,turn1,turn2, turn3, turn4])

rian = turtle.Turtle()

for i in array:
    rian.left(int(i, 10))
    rian.forward(100)

turtle.exitonclick()