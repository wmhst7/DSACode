#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "Vector.h"
using namespace std;
#define MAXM 200010
#define MAXN 220000

int n, m;//vertex, edge
int low[MAXN], dfn[MAXN], vis[MAXN];//Tarjan
int stack[MAXN];//Stack
int top = -1;//Stack
int cnt_t = 0;//Tarjan
int father[MAXN];//Tarjan Tree Father
Vector<int> edge[MAXM];//edge
int fa[MAXN];//记录BCC
bool cut[MAXN];//true->割点
int ori[MAXN];//记录割点的原编号
int bcc = 0;//bcc+割点的个数(1,2,3..)
Vector<int> bccedge[MAXN];//新图的边


void Tarjan(int u, int f){
    father[u] = f;
    dfn[u] = ++cnt_t;
    low[u] = cnt_t;
    vis[u] = 1;
    stack[++top] = u;
    for(int i=0;i<edge[u].size();i++){
        int v = edge[u][i];
        if(vis[v]){
            if(f != v) low[u] = min(low[u], dfn[v]);
        }else{
            Tarjan(v, u);
            if(low[v] < dfn[u]){
                low[u] = min(low[u], low[v]);
            }else{
                bcc++;
                do{
                    fa[stack[top]] = bcc;
                }while(stack[top--] != v);
                fa[u] = bcc;
            }
        }
        vis[v] = 1;
    }
}

void compress(){
    for(int u = 1;u <= n;u++){
        for(int i=0;i<edge[u].size();i++){
            int v = edge[u][i];
            if(fa[u] != fa[v]){
                bccedge[fa[u]].push_back(fa[v]);
            }
        }
    }
    for(int i = 1;i<=bcc;i++){
        bccedge[i].deduplicate();
    }
}

void solve(){
    Tarjan(1, 0);
    //割点
    for(int i=0;i<=n;i++) vis[i] = 0;
    int nRootSons = 0;
    for(int i=2;i<=n;i++){
        int v = father[i];
        if(v == 1) nRootSons++;
        else if(dfn[v] <= low[i]){
            cut[v] = true; 
            fa[v] = ++bcc;
            ori[fa[v]] = v;
        }
    }
    if(nRootSons > 1){
        cut[1] = true;
        fa[1] = ++bcc;
        ori[fa[1]] = 1;
    }
    //建新树
    compress();
}

void bfs(int s, int t){//最短路径
    int v, head=0, tail=0;
    stack[tail++] = s;
    father[s] = s;
    while(tail - head > 0){
        v = stack[head++];//出队
        vis[v] = 1;
        if(v == t) break;
        for(int i = 0;i<bccedge[v].size();i++){
            int u = bccedge[v][i];
            if(vis[u]) continue;
            if(father[u] == -1){
                father[u] = v;
                stack[tail++] = u; //入队
            }
        }
    }
    top = -1;
    v = father[t];
    while(v != s){
        if(ori[v]) stack[++top] = ori[v];
        v = father[v];
    }
}

int cmp(const void * a, const void * b){
    return *(int *) a - *(int *)b;
}

void query(int s, int t){
    for(int i=0;i<MAXN;i++){
        vis[i] = 0;
        father[i] = -1;
    }
    //stack, father重利用
    bfs(fa[s], fa[t]);
    stack[++top] = s;
    if(s != t) stack[++top] = t;
    qsort(stack, top+1, sizeof(int), cmp);
    for(int i=0;i<=top;i++){
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main(){
    scanf("%d %d", &n, &m);
    int u, v;
    for(int i=1;i<=m;i++){
        scanf("%d %d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    solve();
    int q, s, t;
    scanf("%d", &q);
    for(int i=0;i<q;i++){
        scanf("%d %d", &s, &t);
        query(s, t);
    }
    return 0;
}