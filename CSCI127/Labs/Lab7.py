import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('nycHistPop.csv', skiprows=5)

max = df["Year"].max()
print(df)
print(max)