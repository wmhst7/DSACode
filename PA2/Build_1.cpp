#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;
#define MAXN 1000000+5
#define MAXM 10000+5
//#define DEBUG
int N, M;
int lc[MAXN], rc[MAXN], father[MAXN];
int height[MAXN];//此节点及其弟弟高度的最大值
int size_sum[MAXN];//此节点及其弟弟规模的和
int queue[MAXN];
int head, tail;

void Print(){
    for(int i=0;i<=N;i++){
        cout<<"i = "<<i
        <<" lc = "<<lc[i]
        <<" rc = "<<rc[i]
        <<" father = "<<father[i]
        <<" h = "<<height[i]
        <<" s = "<<size_sum[i]
        <<" queue = "<<queue[i]<<endl;
    }
}

void Initial(){//初始化h,s
    head = 0;
    tail = 0;
    queue[tail++] = 1;
    while(tail - head > 0){
        int now = queue[head++];
        if(lc[now] > 0){
            queue[tail++] = lc[now];
            now = lc[now];
            while(rc[now] > 0){
                queue[tail++] = rc[now];
                now = rc[now];
            }
        }
    }
    for(int i=0;i<=N;i++){
        height[i] = -1;
    }
    size_sum[0] = 0;
    father[0] = 0;
    for(int k = tail-1;k>=0;--k){
        int i = queue[k];
        height[i] = max(height[rc[i]], height[lc[i]] + 1);
        size_sum[i] = size_sum[rc[i]] + size_sum[lc[i]] + 1;
    }
    #ifdef DEBUG
    Print();
    #endif
}

void Create(){
    int a, b, t;
    for(int i = 1;i<=N;i++){
        a = i;
        scanf("%d", &t);
        for(int j = 0;j < t;j++){
            scanf("%d", &b);
            if(j == 0){
                lc[a] = b;
                father[b] = a;
                a = b;
            }else{
                rc[a] = b;
                father[b] = a;
                a = b;
            }
        }
    }
    Initial();
}

int Search(){
    int pos = 1, num, tem;
    scanf("%d", &num);
    bool end = false;
    for(int i=0;i<num;i++){
        scanf("%d", &tem);
        if(end) continue;
        if(tem == 0 && lc[pos] > 0){
            pos = lc[pos];
        }else if(lc[pos] > 0){
            int cnt = 0;
            int now = lc[pos];
            while(cnt != tem){
                now = rc[now];
                cnt++;
                if(now == 0){
                    end = true;
                    break;
                }
            }
            if(now != 0) pos = now;
        }else{
            end = true;
        }
    }
    #ifdef DEBUG
    cout<<"Search: "<<pos<<endl;
    #endif
    return pos;
}

void Move(){
    //删除并更新
    int s = Search();
    if(father[s]){//有父亲
        int f = father[s];
        if(lc[f] == s){//删的是长子
            lc[f] = rc[s];
        }else if(rc[f] == s){//删的是其它儿子
            rc[f] = rc[s];
        }
        if(rc[s]) father[rc[s]] = f;
        while(f != 0){
            height[f] = max(height[lc[f]]+1, height[rc[f]]);
            size_sum[f] = size_sum[lc[f]] + size_sum[rc[f]] + 1;
            f = father[f];
        }
    }
    if(s < 2) return;//删除空树或根
    //插入并更新,将s插入到t的第d个儿子处
    int t = Search();
    int d, ori;
    scanf("%d", &d);
    if(d == 0){
        ori = lc[t];
        lc[t] = s;
        rc[s] = ori;
        father[s] = t;
        if(ori) father[ori] = s;
    }else{
        ori = lc[t];
        while(--d > 0){
            ori = rc[ori];
        }
        int tem = rc[ori];
        rc[ori] = s;
        father[s] = ori;
        rc[s] = tem;
        if(tem) father[tem] = s;
    }
    int ff = s;
    while(ff != 0){
        height[ff] = max(height[lc[ff]] + 1, height[rc[ff]]);
        size_sum[ff] = size_sum[lc[ff]] + size_sum[rc[ff]] + 1;
        ff = father[ff];
    }
}

void QueryHeight(){
    printf("%d\n", height[lc[Search()]] + 1);
}

void QuerySize(){
    printf("%d\n", size_sum[lc[Search()]] + 1);
}

int main()
{
    scanf("%d %d", &N, &M);
    Create();
    int flag;
    for (int i = 0; i < M; i++)
    {
        scanf("%d", &flag);
        switch (flag)
        {
        case 0:
            Move();
            break;

        case 1:
            QueryHeight();
            break;

        case 2:
            QuerySize();
            break;
        }
    }
    return 0;
}