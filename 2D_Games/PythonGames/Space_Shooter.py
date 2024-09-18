import turtle
import random

# Setup the game screen
screen = turtle.Screen()
screen.title("Space Shooter")
winHeight = 600
winWidth = 450
screen.setup(winWidth, winHeight)

bg_pic = "/Users/macbookair/Start_Of_Us/2D_Games/PythonGames/space-1.gif"
screen.register_shape(bg_pic)

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

ship_hidden = False

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

# Make the ability to move the ship where ever you drag the cursor within a boundary
def move_ship(x, y):
    if x < -200 or x > 200 or y < -270 or y > -50:
        ship.ondrag(None) # Nothing hapens if cursor is dragged
    else:
        ship.goto(x,y) # The ship goes to the cursor's (x,y) coordinate

def drag():
    ship.ondrag(move_ship) # Calls the move_ship def when cursor is dragged

screen.onscreenclick(move_ship)  # Calls move_ship def whenever its clicked in the boundary

# Shooting animation

bullets = []  # Array to store the newly created bullet turtles
def create_bullets():
    if not ship_hidden:
        x = ship.xcor()
        y = ship.ycor()
        bullet = turtle.Turtle()
        bullet.penup()
        bullet.color("cyan")
        bullet.shape("circle")
        bullet.shapesize(0.3, 0.3)
        bullet.goto(x,y+15)
        bullets.append(bullet)

def shoot():
    to_remove = []
    for bullet in bullets: # Goes through each bullet in the array from 0 to length of the array and moves them up by 10
        y = bullet.ycor()
        bullet.sety(y + 10)
        if y > 300:         # If the bullets go over y = 300, then they are deleted
            bullet.hideturtle()
            to_remove.append(bullet)
    for i in to_remove:
        bullets.remove(i)

        
        
# Obstacles
obstacles = []
def create_obstacles():
    if not ship_hidden:
        x = random.randint(-200, 200)
        y = random.randint(300, 350)
        obs = turtle.Turtle()
        obs.penup()
        obs.color("red")
        obs.shape("square")
        obs.shapesize(random.uniform(0.5, 2), random.uniform(0.5, 2))
        obs.goto(x,y)
        obstacles.append(obs)
        screen.ontimer(create_obstacles, 3000)

screen.ontimer(create_obstacles)

def move_obs():
    to_remove = []
    for obs in obstacles: # Goes through each bullet in the array from 0 to length of the array and moves them up by 10
        y = obs.ycor()
        obs.sety(y - 5)
        if y < -300:         # If the obstacles go over y = 300, then they are deleted
            obs.hideturtle()
            to_remove.append(obs)
    for i in to_remove:
        obstacles.remove(i)

def check_collison():
    global ship_hidden
    to_remove_bullets = []
    to_remove_obs = []

    for obs in obstacles:
        for bullet in bullets:
            if obs.distance(bullet) < 15:
                obs.goto(300,600)
                bullet.goto(300,600)
                to_remove_bullets.append(bullet)
                to_remove_obs.append(obs)
    for i in to_remove_obs:
        obstacles.remove(i)
    for i in to_remove_bullets:
        bullets.remove(i)

    if not ship_hidden:
        for obs in obstacles:
            if obs.distance(ship) < 15:
                ship.hideturtle()
                ship_hidden = not ship_hidden

def reset():
    global ship_hidden
    if ship_hidden:
        ship_hidden = not ship_hidden
        ship.showturtle()
        ship.goto(0, -250)
        screen.ontimer(create_obstacles, 3000)
    screen.ontimer(reset, 12000)

screen.ontimer(reset)

screen.listen()
screen.onkey(create_bullets, "space")
# Enemy ships


def game_loop():
    screen.update()
    move_bg()
    drag()
    shoot()
    move_obs()
    check_collison()
    screen.ontimer(game_loop, 20)

screen.ontimer(game_loop, 20)

