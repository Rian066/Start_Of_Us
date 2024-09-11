import turtle

# Setup the game screen
screen = turtle.Screen()
screen.title("Space Shooter")
winHeight = 600
winWidth = 600
screen.setup(winWidth, winHeight)

bg_pic = "/Users/macbookair/Start_Of_Us/2D_Games/PythonGames/space-1.gif"
screen.register_shape(bg_pic)  # Makes a new shape based on the gif

tk_screen = screen._root # Access the underlying Tkinter window
tk_screen.resizable(False, False) # Remove the ability to manipulate screen size
screen.tracer(0) # Max speed in transition which helps the FPS

# Setup the background using turtle
# First background turtle
bg_screen = turtle.Turtle()
bg_screen.penup()
bg_screen.shape(bg_pic)
# Second background turtle
bg_screen2 = turtle.Turtle()
bg_screen2.penup()
bg_screen2.shape(bg_pic)
bg_screen2.goto(0, 600) # Only one of the pic need to be in screen at the start

# Setup your space ship
ship = turtle.Turtle()
ship.penup()
ship.shape("triangle")
ship.color("white")
ship.setheading(90)
ship.goto(0,-250)
ship.speed(1)

def move_bg():
    # We need two of these because when one of then reaches the bottom, it reveals the actual background behind it. So it doesn't look like moving space. You can see for yourself by deleting one of them.
   
    # Decrement the y coordinate by 5 so the screen turtle goes down
    y = bg_screen.ycor() 
    bg_screen.sety(y - 5)
    y2 = bg_screen2.ycor()
    bg_screen2.sety(y2 - 5)
    #When it reaches the bottom, it starts from the top again
    if y == -600:  # It's -600 because you need to make sure the image is fully out of the screen before teleporting it above. 
        bg_screen.sety(595)
    if y2 == -600:
        bg_screen2.sety(595)


def move_ship(x, y):
    if x < -270 or x > 270 or y < -270 or y > -50:
        ship.ondrag(None)
    else:
        ship.goto(x,y)

def drag():
    ship.ondrag(move_ship)

screen.onscreenclick(move_ship)

while True:
    screen.update()
    move_bg()
    drag()

