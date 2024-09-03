#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: September 3, 2024
#This program draws a flower.

import turtle

flower = turtle.Turtle()

flower.color("red")

for i in range (36):
    flower.forward(100)
    flower.left(145)
    flower.forward(10)
    flower.right(90)
    flower.forward(10)
    flower.left(135)
    flower.forward(100)

turtle.exitonclick()
