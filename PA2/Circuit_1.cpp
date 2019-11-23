#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;

#define MAXN 26000000
#define MAXM 500005
int K, N, cnt = 1;
int lc[MAXN], rc[MAXN];
char ch[MAXM][68];

void insert(char str[], int p, int d, int n){
    //当前串，当前节点树编号,当前递归深度,当前串编号
    if(d == 64){//最深到第64层（0->64）
        while(lc[p] != 0){
            p = lc[p];
        }
        lc[p] = ++cnt;
        rc[p] = n;
        return;
    }
    if(str[d] == '0'){
        if(lc[p] == 0) lc[p] = ++cnt;
        insert(str, lc[p], d+1, n);
    }else{
        if(rc[p] == 0) rc[p] = ++cnt;
        insert(str, rc[p], d+1, n);
    }
    return;
}

void remove(char str[], int p, int d, int f){ 
    //str,当前节点编号，当前深度，父亲的编号
    if(d == 64){
        int q = lc[p];
        if(q == 0) return;
        lc[p] = lc[q];
        rc[p] = rc[q];
        if(lc[p] == 0){
            if(lc[f] == p) lc[f] = 0;
            if(rc[f] == p) rc[f] = 0;
        }
        return;
    }
    if(str[d] == '0'){
        remove(str, lc[p], d+1, p);
    }else{
        remove(str, rc[p], d+1, p);
    }
    if(lc[p] == 0 && rc[p] == 0){
        if(lc[f] == p) lc[f] = 0;
        if(rc[f] == p) rc[f] = 0;
    }
    return;
}

int query(char str[], int p, int d, int n){
    //Base
    if(d == 64){
        if(rc[p] == n){
            return rc[lc[p]];
        }else{
            return rc[p];
        }
    }
    if(str[d] == '0'){
        if(rc[p] > 0){
            return query(str, rc[p], d + 1, n);
        }else{
            return query(str, lc[p], d + 1, n);
        }
    }else{
        if(lc[p] > 0){
            return query(str, lc[p], d + 1, n);
        }else{
            return query(str, rc[p], d + 1, n);
        }
    }
}

void run(){
    int a, b;
    scanf("%d %d\n", &N, &K);
    for(int i = 0;i < N;i++){//预处理
        scanf("%s", ch[i]);
    }
    for(int i = 0;i <= K + 1;i++){
        if(i >= N) continue;
        insert(ch[i], 1, 0, i);
    }
    for(int i = 0;i < N;i++){
        printf("%d\n", query(ch[i], 1, 0, i));
        if(i + K + 2 < N){
            insert(ch[i + K + 2], 1, 0, i + K + 2);
        }
        if(i - K - 1 >= 0){
            remove(ch[i - K - 1], 1, 0, 1);
        }
    }
}

int main(){
    run();
    return 0;
}

