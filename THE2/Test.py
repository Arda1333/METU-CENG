#import random
#random.seed(111)
#for i in range(10):
#    print(random.randint(0, 1000))
#import random
#
#print(random.choices(["notinfected", "infected"], [0.5, 0.5], k = 1))
from evaluator import *
from the2 import * 
for i in range(15):
    print("Call "+str(i+1)+" : ", end="")
    print(new_move())