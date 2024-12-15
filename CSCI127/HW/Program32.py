# Name:  Rian M Alif
# Email: rian.alif58@myhunter.cuny.edu
# Date: December 14, 2024
# This program edits the flood map

import matplotlib.pyplot as plt
import numpy as np

elevations = np.loadtxt("elevationsNYC.txt")

amBlue = float(input("How blue you want: "))
outputFile = input("Save file as: ")

while not 0 <= amBlue <= 1:
    amBlue = float(input("Blue must be between 0 and 1: "))

mapShape = elevations.shape + (3,)
newMap = np.zeros(mapShape)

for row in range(mapShape[0]):
    for col in range(mapShape[1]):
        if elevations[row, col] <= 0:
            newMap[row, col] = [0, 0, amBlue]
        elif elevations[row, col] % 10 == 0:
            newMap[row, col] = [0, 0, 0]
        else:
            newMap[row, col] = [1, 1, 1]

print("Thank You for using my program!")
plt.imsave(outputFile, newMap)
print(f"Your map is stored {outputFile}.")
