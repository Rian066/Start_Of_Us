#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: October 12, 2024
#This program uses pyplot to count the number of white pixels grater than 0.75

import matplotlib.pyplot as plt

image = plt.imread(input("Filename: "))
snow_count = 0
T = 0.75

for i in range(image.shape[0]):
    for j in range(image.shape[1]):
        if image[i,j,0] > T and image[i,j,1] > T and image[i,j,2] > T:
            snow_count += 1

print ("Snow count is", snow_count)