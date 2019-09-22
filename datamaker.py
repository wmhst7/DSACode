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


# # 每组数据10个，长度为10
# dataMaker(10, 5000)

def dataMaker(n,m,k):
	f = sys.stdout
	f.write(str(n)+' '+str(m)+' '+str(k)+'\n')
	S1 = ''
	S2 = ''
	for itr in range(n):
		S1 += str(random.randint(0, 9))
	for itr in range(m):
		S2 += str(random.randint(0, 9))
	f.write(S1 + " " + S2 + "\n")

dataMaker(10, 30, 20)
