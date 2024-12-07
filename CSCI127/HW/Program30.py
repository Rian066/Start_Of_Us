# Name:  Rian M Alif
# Email: rian.alif58@myhunter.cuny.edu
# Date: December 6, 2024
# This program is used to give different population info from a csv file

import pandas as pd

df = pd.read_csv("nycHistPop.csv", skiprows=5)

borough = input("Enter borough: ")

print(
    f"Minimum population: {df[borough].min()} \nAverage population: {df[borough].mean()} \nMaximum population: {df[borough].max()}"
)
