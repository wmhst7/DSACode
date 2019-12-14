#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define MAXN 20000010
char S[MAXN];
int n;
int next[MAXN];

void buildNext(char * P){
    int m = strlen(P), j = 0;
    int * N = new int [m]
}

inline char nc(){
    static const int n = 100000;
    static char buf[n], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf)+fread(buf, 1, n, stdin), p1 == p2) ? EOF : *p1++;
}

int main(){
    n=0;
    do{
        S[n++] = nc();
    }while(S[n - 1] != '\n');
    S[n] = '\0';
    n--;
    return 0;
}