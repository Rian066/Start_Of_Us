#Name:  Rian M Alif
#Email: rian.alif58@myhunter.cuny.edu
#Date: October 26, 2024
#This program gives the length and GC-content of a DNA string

dna = input("DNA String: ")

length = len(dna)
gc = dna.count('G') + dna.count('C')

print("Length is", length, "\nGC-content is", gc/length)