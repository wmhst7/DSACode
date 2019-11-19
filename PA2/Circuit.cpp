#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

//Queue Implementaion Based in List Begin
class QueueNode{
public:
    int data;
    QueueNode * next;
    QueueNode(int d):data(d){
        next = nullptr;
    }
};
class Queue{
public:
    QueueNode * head = nullptr;

    void enqueue(int d){
        if(head == nullptr){
            head = new QueueNode(d);
            return;
        }
        QueueNode * p = head;
        while(p->next != nullptr){
            p = p->next;
        }
        p->next = new QueueNode(d);
        return;
    }
    int query(int num){
        QueueNode * p = head;
        if(head == nullptr){
            return -1;
        }
        if(num == p->data && p->next != nullptr){
            return p->next->data;
        }
        return p->data;
    }
    bool remove(){
        if(head == nullptr) return true;
        QueueNode * p = head;
        head = head->next;
        delete p;
        if(head == nullptr) return true;
        return false;
    }
};
//Queue Implementaion End


#define MAXN 25000000
#define MAXM 500005
int K, N, cnt = 1, cntl = 1;
int lc[MAXN], rc[MAXN];
Queue queue[MAXM]; //叶节点对应的输出编号
char ch[MAXM][64];

void insert(char str[], int p, int d, int n){
    //当前串，当前节点树编号,当前递归深度,当前串编号
    if(d == 64){//最深到第64层（0->64）
        if(lc[p] == 0){
            lc[p] = cntl;
            cntl++;
        }
        queue[lc[p]].enqueue(n);
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
        if(queue[lc[p]].remove()){
            lc[p] = 0;
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
        return queue[lc[p]].query(n);
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

int main(){
    int a, b;
    char * buffer = new char[100];
    scanf("%d %d\n", &N, &K);
    for(int i = 0;i < N;i++){//预处理
        cin.getline(buffer, 100);
        for(int j = 0;j<64;j++){
            ch[i][j] = buffer[j];
        }
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
    return 0;
}

