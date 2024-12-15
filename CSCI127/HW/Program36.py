# Name:  Rian M Alif
# Email: rian.alif58@myhunter.cuny.edu
# Date: December 14, 2024
# This program modifies Lab 8 parking ticket program

import pandas as pd

fileName = input("Enter file name: ")
attribute = input("Enter attribute: ")

print("The 10 worst offenders are: ")

df = pd.read_csv(fileName)

print(df[attribute].value_counts()[:10])
