#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: November 11, 2024
#This program changes pixels to blue only

import matplotlib.pyplot as plt
import numpy as np
height= 20
width = 30
#An image is an array with height, width, and depth
#The height and width can be any integers but
# the depth is always 3 for the red, green, and blue channels
img = np.zeros((height, width, 3))
img[2:height//2:, :width//2, 0] = 1 #upper left corner

img[height//2:, :width//2, 1] = 1 #lower left corner
img[:height//2:2, width//2:, 2] = 1 #upper right corner
img[height//2:, width//2::2, :2] = 1 #lower right corner
plt.imshow(img)
plt.show()

'''
for i in range(height):
    for j in range(width//2, width, 10):
        img2[i::2,j::2,0] = 0
        img2[i::2,j::2,1] = 0
for i in range(height):
    for j in range(width//2, width, 1):
        if img2[i,j,0] == 0:
            continue
        img2[i::2,j::2,2] = 0
        img2[i::2,j::2,1] = 0


plt.imshow(img)
plt.show()
# plt.imsave(outputFile, img2)
'''