#Starting snake game

import turtle
import random

# Setup window
window = turtle.Screen()
window.title("Snake")
window.bgcolor("cyan")
winHeight = 600
winWidth = 600
window.setup(winWidth, winHeight)
tk_window = window._root # Access the underlying Tkinter window
tk_window.resizable(False, False) # Remove the ability to manipulate window size


# Setup Snake
snake = turtle.Turtle()
snake.penup()
snake.setx(random.randint(-250,250))
snake.sety(random.randint(-250,250))
snake.color("red")
snake.shape("triangle")

# Pause option
paused = False
def pause_game():
    global paused
    paused = not paused # Changes paused from False to true so when it's used in move(), it becomes False again because of the "not" and doesn't continue to next steps

# Movement

# Set up a direction variable
direction = "none"
# Make def statements to determine the direction variable value when keys are pressed
def go_up():
    global direction
    if direction != "down": # If the snake is not going in the opposote direction then the key will work when pressed
        direction = "up"

def go_down():
    global direction
    if direction != "up": # If the snake is not going in the opposote direction then the key will work when pressed
        direction = "down"

def go_right():
    global direction
    if direction != "left": # If the snake is not going in the opposote direction then the key will work when pressed
        direction = "right"

def go_left():
    global direction
    if direction != "right": # If the snake is not going in the opposote direction then the key will work when pressed
        direction = "left"

def move(): # Defines by how much the snake will move by when the keys are presssed
 if not paused: # Since initially paused is False, the "not" makes it True and runs the next step
    if direction == "up":
        yCordinate = snake.ycor()
        snake.sety(yCordinate + 5)
    if direction == "down":
        yCordinate = snake.ycor()
        snake.sety(yCordinate - 5)
    if direction == "right":
        xCordinate = snake.xcor()
        snake.setx(xCordinate + 5)
    if direction == "left":
        xCordinate = snake.xcor()
        snake.setx(xCordinate - 5)

# Setup the trigger for when keys are pressed
window.listen()
window.onkey(go_up, "Up") # If the up key is pressed then it will trigger def go_up
window.onkey(go_down, "Down") # If the down key is pressed then it will trigger def go_down
window.onkey(go_right, "Right") # If the right key is pressed then it will trigger def go_right
window.onkey(go_left, "Left") # If the left key is pressed then it will trigger def go_left
window.onkey(pause_game, "space") # If the left key is pressed then it will trigger def go_left

# Make it move
while True: # It will make sure it's always watching out for when a key is pressed and keeps the snake in continious motion
    window.update()  # Needs to update the window in order to see the changes
    move()  # Makes sure to keep the move() def running at all times


window.exitonclick()