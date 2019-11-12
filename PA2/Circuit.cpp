#include <stdlib.h>
#include <stdio.h>
#define MAXN 500000
int K, N, cnt = 1;
int lc[MAXN], rc[MAXN], s[MAXN];

void insert(char str[], int p, int d){//当前串，当前节点编号,当前深度
    if(d >= 64) return;
    s[p]++;
    if(str[d] == '0'){
        if(lc[p] == 0) lc[p] = ++cnt;
        insert(str, lc[p], d+1);
    }else{
        if(rc[p] == 0) rc[p] = ++cnt;
        insert(str, rc[p], d+1);
    }
    return;
}

void remove(char str[], int p, int d){
    if(d >= 64) return;
    s[p]--;
    if(str[d] == '0'){
        //if(lc[p] == 0) lc[p] = ++cnt;
        remove(str, lc[p], d+1);
    }else{
        //if(rc[p] == 0) rc[p] = ++cnt;
        remove(str, rc[p], d+1);
    }
    return;
}

int query(char str[], int p, int d){
    //Base
    if(d == 63){
        
    }
    if(str[d] == '0'){
        if(s[rc[p]] > 0){
            query(str, rc[p], d + 1);
        }else{
            query(str, lc[p], d + 1);
        }
    }else{
        if(s[lc[p]] > 0){
            query(str, lc[p], d+1);
        }else{
            query(str, rc[p], d+1);
        }
    }
}

int main(){
    int a, b;
    scanf("%d %d\n", &N, &K);
    char ** ch = new char*[N];
    for(int i=0;i<N;i++){
        ch[i] = new char[64];
    }
    for(int i = 0;i < N;i++){//预处理
        scanf("%s\n", ch[i]);
    }
    for(int i = 0;i <= K;i++){
        insert(ch[i], 1, 0);
    }
    for(int i = 0;i < N;i++){
        if(i - K - 1 >= 0){
            remove(ch[i - K - 1], 0, 0);
        }
        if(i + K + 1 < N){
            insert(ch[i + K + 1], 0, 0);
        }
        printf("%d\n", query(ch[i]));
    }
    return 0;
}

