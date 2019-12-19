#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 20000010
#define ll long long
char S[MAXN];
int n;
int N[MAXN];
int L[MAXN];
ll res = 0;

void buildNext(){
    N[0] = -1;
    int t = -1, j = 0;
    while(j < n){
        if(S[j] == S[t] || t < 0){
            j++; t++;
            N[j] = t; //next[j+1] = next[j] + 1
            L[j] = L[t] + 1;
            res += L[j];
        }else{
            t = N[t]; //t go forward
        }
    }
}


inline char nc(){
    static const int _N = 120000;
    static char buf[_N], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf)+fread(buf, 1, _N, stdin), p1 == p2) ? EOF : *p1++;
}

int main(){
    n = -1;
    do{
        S[++n] = nc();
    }while(S[n] != '\n');
    buildNext();
    printf("%lld\n", res);
    return 0;
}