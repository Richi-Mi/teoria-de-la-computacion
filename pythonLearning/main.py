import sys

# Python intro
print("Hello World") # This is a comment

"""
This is a comment
written in
more than just one line
but in reality this is not a comment, 
is a do not multiline string 
"""

# In Python, variables are created when you assign a value to it:
x = 5
y = "Hello world"

# Variables do not need to be declared with any particular type, and can even change type after they have been set.

x = 4       # x is of type int
x = "Sally" # x is now of type str
print(x)

# casting 
x = str(3)    # x will be '3'
y = int(3)    # y will be 3
z = float(3)  # z will be 3.0

# print(sys.version + str(900)) - Versión of python

# You can get the data type of a variable with the type() function.
print( type(x) ) # type of x

# Python allows you to assign values to multiple variables in one line:
x, y, z = "Orange", "Banana", "Cherry"
print(x)
print(y)
print(z)

a = b = c = 9 # a, b and c have the same value

# Unpack a collection.
fruits = ["apple", "banana", "cherry"]
x, y, z = fruits
# x y z has the value of x=apple y = banana z = cherry

x = "awesome"

def myfunc():
    x = "fantastic"
    print("Python is " + x)

    # If I want to create a global variable inside a function, we use global
    global h 
    h = "hi"

myfunc()

print("Python is " + x, h) # awesome
