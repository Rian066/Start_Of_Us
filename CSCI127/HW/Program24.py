#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: November 3, 2024
# This program uses string to control turtle movements

import turtle
trtle = turtle.Turtle()
 
text = input("Type a string: ")

for i in text:
    if i == 'F':
        trtle.forward(50)
    elif i == 'B':
        trtle.backward(50)
    elif i == 'L':
        trtle.left(90)
    elif i == 'R':
        trtle.right(90)
    elif i == 'l':
        trtle.left(45)
    elif i == 'r':
        trtle.right(45)
    elif i == '^':
        trtle.penup()
    elif i == 'v':
        trtle.pendown()
    elif i == 'S':
        trtle.stamp()
    elif i == 'p':
        trtle.pencolor("purple")

turtle.exitonclick()

