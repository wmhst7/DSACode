#include <stdio.h>
#include <stdlib.h>
#define MAXN 20000010
#define _buf_size 5000000
#define ll long long
char S[MAXN];
int n;
int N[MAXN];
int L[MAXN];
ll res = 0;
char _buf[_buf_size];
char *p1, *p2;


void buildNext()
{
    N[0] = -1;
    int t = -1, j = 0;
    while (j < n)
    {
        if (S[j] == S[t] || t < 0)
        {
            j++;
            t++;
            N[j] = t; //next[j+1] = next[j] + 1
            L[j] = L[t] + 1;
            res += L[j];
        }
        else
        {
            t = N[t]; //t go forward
        }
    }
}

inline char nc()
{
    return p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, _buf_size, stdin), p1 == p2) ? EOF : *p1++;
}

int main()
{
    p1 = p2 = _buf;
    n = -1;
    do{
        S[++n] = nc();
    } while (S[n] != '\n');
    buildNext();
    printf("%lld\n", res);
    return 0;
}