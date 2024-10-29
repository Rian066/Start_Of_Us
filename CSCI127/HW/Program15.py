#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: October 12, 2024
#This program uses ceaser cipher

text = input("Type something: ")

cipher_text = ''
for char in text:
    shift = ord(char) + 13
    if shift > ord('z'):
        shift = ord('a') - 1 + (shift - ord('z'))
    cipher_text += chr(shift)

print(cipher_text)
