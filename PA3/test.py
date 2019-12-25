import numpy as np 
import sys
import random

def get(n, limit):
    with open("/Users/wmhst7/Desktop/DSA/DSACode/PA3/Input.txt", 'w') as f:
        f.write('{} {}\n'.format(n, limit))
        ls = list(range(n))
        random.shuffle(ls)
        for l in ls:
            f.write(str(l) + ' ')
        
get(1000000, 10300000)