#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: October 12, 2024
#This program uses ceaser cipher

cipher_text = input("Type something: ")

final_text = ''
for char in cipher_text:
    shift = ord(char) + 13
    if shift > ord('a') + 26:
        shift = ord('a') + (shift - (26 + ord('a')))
    final_text += chr(shift)

print(final_text)
