import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('nycHistPop.csv', skiprows=5)


df["Fraction"] = df["Bronx"]/df["Total"]
print(df)
print(df["Fraction"])


