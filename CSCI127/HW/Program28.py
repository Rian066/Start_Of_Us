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
