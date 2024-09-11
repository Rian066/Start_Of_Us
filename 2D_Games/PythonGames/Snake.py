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
window.tracer(0) # Max speed in transition which helps the FPS

# Setup Snake
snake = turtle.Turtle()
snake.penup()
snake.setx(random.randint(-250,250))
snake.sety(random.randint(-250,250))
snake.color("red")
snake.shape("triangle")

# Setup Food
food = turtle.Turtle()
food.penup()
food.shape("circle")
food.color("yellow")
food.shapesize(0.8, 0.8) #Food size is a big smaller to make it look nice
food.goto(random.randint(-250,250), random.randint(-250,250))  # Spawns food at a random location

# Pause option
paused = True
def pause_game():
    global paused
    paused = not paused # Changes paused from False to True so when it's used in move(), it determines if the move() def will be ran or not

# Movement
speed = 1.5
# Set up a direction variable
direction = "right"
# Make def statements to determine the direction variable value when keys are pressed
def go_up():
    global direction
    if direction == "right":
        snake.left(90)
    if direction == "left":
        snake.right(90)
    if direction != "down": # If the snake is not going in the opposote direction then the key will work when pressed
        direction = "up"

def go_down():
    global direction
    if direction == "right":
        snake.right(90)
    if direction == "left":
        snake.left(90)
    if direction != "up": # If the snake is not going in the opposote direction then the key will work when pressed
        direction = "down"

def go_right():
    global direction
    if direction == "up":
        snake.right(90)
    if direction == "down":
        snake.left(90)
    if direction != "left": # If the snake is not going in the opposote direction then the key will work when pressed
        direction = "right"

def go_left():
    global direction
    if direction == "up":
        snake.left(90)
    if direction == "down":
        snake.right(90)
    if direction != "right": # If the snake is not going in the opposote direction then the key will work when pressed
        direction = "left"

def move(): # Defines by how much the snake will move by when the keys are presssed
 if not paused: # Since initially paused is False, it won't run the next step unless pasued is changed from False to True by pressing space and vice versa
    if direction == "up":
        yCordinate = snake.ycor()
        snake.sety(yCordinate + speed)
    if direction == "down":
        yCordinate = snake.ycor()
        snake.sety(yCordinate - speed)
    if direction == "right":
        xCordinate = snake.xcor()
        snake.setx(xCordinate + speed)
    if direction == "left":
        xCordinate = snake.xcor()
        snake.setx(xCordinate - speed)

# Setup the trigger for when keys are pressed
window.listen()
window.onkey(go_up, "Up") # If the up key is pressed then it will trigger def go_up
window.onkey(go_down, "Down") # If the down key is pressed then it will trigger def go_down
window.onkey(go_right, "Right") # If the right key is pressed then it will trigger def go_right
window.onkey(go_left, "Left") # If the left key is pressed then it will trigger def go_left
window.onkey(pause_game, "space") # if space is pressed it will run the pause_game def and switch between True or Flase value for paused

# FOOD 
Body = [] # Create a array to hold the new body segments after eating food

def eat_food():
    global speed
    global score

    num_body = random.randint(1,5)

    if snake.distance(food) <= 15:
        score += 1
        update_score()
        food.goto(random.randint(-250,250), random.randint(-250,250))  # Spawns food at a random location
        speed = speed + 0.05  # Increases the speed after eating food
        # Makes a new segment 
        for i in range(num_body):
            new_body = turtle.Turtle()
            new_body.penup()
            new_body.shape("circle")
            new_body.color("red")
            new_body.goto(333,333)
            new_body.shapesize(0.8,0.8)
            Body.append(new_body) # Adds the new body part to the Body array that has all the other body parts

def move_body():
    # Check if there is any body parts to replace the snake head
    if not paused:
        if len(Body) > 0:
        #             (    start   , end , increment )
            for i in range( len(Body)-1,  0  ,   -1 ):  
                x = Body[i-1].xcor() 
                y = Body[i-1].ycor()

                # Just making sure that for any reason the body doesn't go beyond the walls
                if x > 300:
                    x = 300
                if x < -300:
                    x = -300
                if y > 300:
                    y = 300
                if y < -300:
                    y = -300
            
                Body[i].goto(x,y)

            # Move the first body to the snake's position
            x = snake.xcor()
            y = snake.ycor()
            Body[0].goto(x, y)

def game_over():
    global Body
    global paused
    global score
    x = snake.xcor()
    y = snake.ycor() 


    # Wall Collision
    if x > 290 or x < -290 or y > 290 or y < -290:  # These are the endpoints so if the snake is at the end of map, these commands below will be triggered
        paused = True  # Stops snake from moving since paused is True, it will not run any of the codes that moves the snake
        snake.goto(random.randint(-250,250), random.randint(-250,250)) # Respawn in a random location
        food.goto(random.randint(-250,250), random.randint(-250,250))
        for i in Body:   # Loops though the Body array and hides the turtles
            i.hideturtle()
        Body.clear() # Removes all the data in Body array
        # Reset score
        score = 0
        update_score()

    # Body Collision
    for index, segment in enumerate(Body):  # Check if snake head touches any body segment
        if index > 10:
            if snake.distance(segment) < 5:  # Small threshold to detect collision
                paused = True  # Pause the game
                snake.goto(random.randint(-250, 250), random.randint(-250, 250))  # Respawn snake
                food.goto(random.randint(-250, 250), random.randint(-250, 250))  # Respawn food
                for i in Body:  # Hide body segments
                    i.hideturtle()
                Body.clear()  # Reset body
                # Reset score
                score = 0
                update_score()

# Score Counter
score = 0
# Setup a counter turtle 
counter = turtle.Turtle()
counter.penup()
counter.color("black")
counter.hideturtle()
counter.goto(170,265)
counter.write(f"Score: {score}", font=("Arial", 18, "normal"))

# Everytime food is eaten, this code resets the counter turtle and gives it new characteristics
def update_score():
    global score
    counter.clear()  # Used in order to prevent overlapping of numbers
    counter.goto(170,265)
    counter.write(f"Score: {score}", font=("Arial", 18, "normal"))

# Make it move
while True: # It will make sure it's always watching out for when a key is pressed and keeps the snake in continious motion
    window.update()  # Needs to update the window in order to see the changes
    if paused == False:  # Just making sure no def is running if game is not on
        move() # Makes sure to keep the move() def running at all times while the game is on
        eat_food() # Makes sure to keep the eat_food() def running at all times while the game is on
        move_body() # Makes sure to keep the move_body() def running at all times while the game is on
        game_over() # Makes sure to keep the game_over() def running at all times while the game is on