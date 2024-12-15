# Name:  Rian M Alif
# Email: rian.alif58@myhunter.cuny.edu
# Date: December 14, 2024
# This program edits the flood map

import matplotlib.pyplot as plt
import numpy as np

elevations = np.loadtxt("elevationsNYC.txt")

mapShape = elevations.shape + (3,)
newMap = np.zeros(mapShape)

for row in range(mapShape[0]):
    for col in range(mapShape[1]):
        if elevations[row, col] <= 0:
            newMap[row, col] = [0, 0, 1]
        elif elevations[row, col] <= 6:
            newMap[row, col] = [1, 0, 0]
        elif 6 < elevations[row, col] <= 20:
            newMap[row, col] = [0.5, 0.5, 0.5]
        else:
            newMap[row, col] = [0, 1, 0]

plt.imsave("floodMap.png", newMap)
