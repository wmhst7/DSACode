#encoding=utf-8

import random
import sys

# def dataMaker(n, valuelength):
# 	f = sys.stdout
# 	f.write(str(n) + "\n")
# 	for datanum in range(n):
# 		S1 = str(random.randint(1, 9))
# 		S2 = str(random.randint(1, 9))
# 		for itr in range(valuelength - 1):
# 			S1 += str(random.randint(0, 9))
# 			S2 += str(random.randint(0, 9))
# 		f.write(S1 + " " + S2 + "\n")


# 每组数据10个，长度为10
import random
import string

def dataMaker(n, k):
    
    f = sys.stdout
    f.write('{} {}\n'.format(n,k))
    for i in range(0,int(n)):
        f.write('1101100011111101111001001000010101111111001101100000010101111')
        for j in range(0,3):
            f.write(str(random.randint(0, 1)))
        f.write(' \n')
    f.close()

dataMaker(10, 2)

