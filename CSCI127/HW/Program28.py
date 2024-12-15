# Name:  Rian M Alif
# Email: rian.alif58@myhunter.cuny.edu
# Date: December 14, 2024
# This program makes a C

import matplotlib.pyplot as plt
import numpy as np

height = 30
width = 30
dimension = np.ones((height, width, 3))

dimension[:, :10, 0] = 0
dimension[:, :10, 1] = 0

dimension[:10, 10:, 0] = 0
dimension[:10, 10:, 1] = 0

dimension[20:, 10:, 0] = 0
dimension[20:, 10:, 1] = 0

plt.imsave("logo.png", dimension)
