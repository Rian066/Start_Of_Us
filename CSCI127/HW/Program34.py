# Name:  Rian M Alif
# Email: rian.alif58@myhunter.cuny.edu
# Date: December 14, 2024
# This program follows a computational pseudocode

seconds = int(input("Seconds before lecture starts: "))

remSec = seconds % 3600
print(
    "Hours: "
    + str(seconds // 3600)
    + "\nMinutes: "
    + str(remSec // 60)
    + "\nSeconds: "
    + str(remSec % 60)
)
