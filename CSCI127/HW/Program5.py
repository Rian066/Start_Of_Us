#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: September 3, 2024
#This program draws a star

import turtle 

star = turtle.Turtle()

for i in range(5):
    star.forward(100)
    star.left(144) # It's 144 because if theres 5 turns then dividing 720 by 5 is 144. 

turtle.exitonclick()
