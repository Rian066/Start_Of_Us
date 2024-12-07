# Name:  Rian M Alif
# Email: rian.alif58@myhunter.cuny.edu
# Date: December 6, 2024
# This program displays the fraction between total and borough population
import matplotlib.pyplot as plt
import pandas as pd

borough = input("Enter borough name: ")
output = input("Enter output file name: ")

df = pd.read_csv("nycHistPop.csv", skiprows=5)
df["Fraction"] = df[borough] / df["Total"]
df.plot(x="Year", y="Fraction")

fig = plt.gcf()
fig.savefig(output)
