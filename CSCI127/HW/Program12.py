#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: September 17, 2024
#This program draws a pentagon and stamps the turtle on each angle

import turtle

trtle = turtle.Turtle()
trtle.shape("turtle")
trtle.color("#6495ED")

for i in range(5):
    trtle.stamp()
    trtle.forward(100)
    trtle.left(72)

turtle.exitonclick()