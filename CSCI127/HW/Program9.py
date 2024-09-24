#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: September 21, 2024
#This program gives the turtle a color based on the input

import turtle

color = input("Enter a hex string: ")
hex_turtle = turtle.Turtle()

# Characteristics 
hex_turtle.shape("turtle")  # Shape is like a turtle
#hex_turtle.shapesize(5)  # Size is 5 times the default
hex_turtle.color(color)

turtle.exitonclick()
