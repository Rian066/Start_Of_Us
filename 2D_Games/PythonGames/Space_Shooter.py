import turtle

# Setup the game screen
screen = turtle.Screen()
screen.title("Space Game")
screen.bgcolor("black")
winHeight = 600
winWidth = 600
screen.setup(winWidth, winHeight)
tk_screen = screen._root # Access the underlying Tkinter window
tk_screen.resizable(False, False) # Remove the ability to manipulate screen size
screen.tracer(0) # Max speed in transition which helps the FPS

# Setup your space ship
ship = turtle.Turtle()
ship.penup()
ship.shape("Triangle")
ship.color("white")
ship.setx(0)
ship.sety(-250)

turtle.exitonclick()
