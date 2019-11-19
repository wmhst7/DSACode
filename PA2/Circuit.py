buff = input().split(' ')
n = int(buff[0])
k = int(buff[1])

num = []
for i in range(0,n):
    num.append(int(input().split(' ')[0], base=2))

for i in range(0, n):
    a = max(0, i-k-1)
    b = min(n, i+k+2)
    Num=-1
    Val=-111111
    for j in range(a, b):
        if j==i:
            continue
        if num[i]^num[j] > Val:
            Num = j
            Val = num[i]^num[j]
    print(Num)