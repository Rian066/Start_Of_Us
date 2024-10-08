#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: September 26, 2024
#This program creates a weird looking star

import turtle

star = turtle.Turtle()

for i in range(5, 301, 5):
    star.forward(i)
    star.left(91)

turtle.exitonclick()
               