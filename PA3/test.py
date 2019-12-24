import numpy as np 
import sys
import random

def get(n, limit):
    with open("PA3/Input.txt", 'w') as f:
        f.write('{} {}\n'.format(n, limit))
        ls = list(range(n))
        random.shuffle(ls)
        for l in ls:
            f.write(str(l) + ' ')
        
get(10000, 2000000)