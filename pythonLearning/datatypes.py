import random

"""
Numbers
"""

x = 1    # int
y = 2.8  # float
z = 1j   # complex

x = 35e3 # Number elevated to 3 

#convert from int to float:
a = float(x)

#convert from float to int:
b = int(y)

#convert from int to complex:
c = complex(x)

print(random.randrange(1, 10))


mystr = '''
STRING's
multiline string
'''

# String's are arrays of char
print(mystr[2])

# looping characteres of string
# for x in mystr:
    # print(x)

# length of string
print( len(mystr) )
if "string" in mystr:
    print("there's string")
if "siom" not in mystr:
    print("there isn't siom")
# substring
b = "Hello, World! "
print( b[2:5] )

# # Modify strings.
# strip, lower y upper
print( b.upper() )
print( b.lower() )
print( b.strip() ) # elimina espacios al final

print( b.replace("H", "J") ) # Reemplaza un string por otro en el texto.

print( b.split(",") )

# F-Strings
age = 20
ntxt = f"The age is {age} \n"
print( "age" in ntxt and "k" not in ntxt )

# booleans.
# True, False sirven para manejo de operadores.

# Python operators
# +	Addition	x + y	
# -	Subtraction	x - y	
# *	Multiplication	x * y	
# /	Division	x / y	
# %	Modulus	x % y	
# **	Exponentiation	x ** y	
# //	Floor division	x // y

print(5**3)