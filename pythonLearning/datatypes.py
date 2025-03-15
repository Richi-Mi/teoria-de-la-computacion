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
b = "Hello, World!"

list = [ 9, 8 , 4, 2, 2 ]

print(b[2:5])