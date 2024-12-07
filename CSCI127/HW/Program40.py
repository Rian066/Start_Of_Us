# Name:  Rian M Alif
# Email: rian.alif58@myhunter.cuny.edu
# Date: December 6, 2024
# This program is a update version of the 100 times walk on lab 10

import turtle
import random

trey = turtle.Turtle()
trey.speed(10)

for i in range(100):
    angle = random.randrange(0, 360, 10)
    trey.left(angle)
    trey.forward(30)
