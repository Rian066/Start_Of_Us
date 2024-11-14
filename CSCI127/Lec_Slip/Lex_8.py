import inflect

def num2String(num): 
    p = inflect.engine()
    return p.number_to_words(num)

print(num2String(5))
