import turtle 

name = input("Your first name: ")
name_length = len(name)
angle = 360/name_length

polygon = turtle.Turtle()
if name_length > 2:
    for i in range(name_length):
        polygon.forward(100)
        polygon.left(angle)
else: 
    message = turtle.Turtle()
    message.penup()
    message.goto(-200,0)
    message.write(f"You dumbass\nPolygons have 3 or more sides...\nSMH", font=("Arial", 18, "normal"))

turtle.exitonclick()
    