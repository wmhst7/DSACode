#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "Vector.h"
using namespace std;

// 非“割点”必然不是答案
// 同双联通分量的点必然无必经点
// 将“双联通分量”看做一个整体，再拿出所有“割点”出来，可构成一棵“树”。
// 等价于问某两个“双联通分量”在这棵“树”上会经过多少“割点”
// 由于q较小，暴力即可。

#define MAXM 200000+5
#define MAXN 100000+5

int n, m;//vertex, edge
int low[MAXN], dfn[MAXN], vis[MAXN];//Tarjan
int stack[MAXN];//Stack
int top = -1;//Stack
int cnt_t = 0;//Tarjan
int father[MAXN];//Tarjan Tree Father
Vector<int> edge[MAXM];//edge
int fa[MAXN];//记录BCC
bool cut[MAXN];//true->割点
int bcc = 0;//bcc+割点的个数(1,2,3..)
Vector<int> bccedge[MAXN];//新图的边

void makeSet(int s){
    for(int i=0;i<=s;i++) fa[i] = i;
}

int find(int x){
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void unionSet(int x, int y){
    x = find(x);
    y = find(y);
    if(x != y) fa[x] = y;
}

void Tarjan(int u, int f){
    father[u] = f;
    dfn[u] = ++cnt_t, low[u] = cnt_t;
    stack[++top] = u;
    for(int i = 0;i < edge[u].size();i++){
        int v = edge[u][i];
        if(f == v) continue;
        if(!dfn[v]){
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }else{
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] >= dfn[f]){
        cout<<"BCC("<<bcc+1<<"): ";
        bcc++;
        do{
            cout<<stack[top]<<' ';
            fa[stack[top]] = bcc;
        }while(stack[top--] != u);
        cout<<endl;
    }
}

void compress(){
    for(int u=1;u<=n;u++){
        if(cut[u]){
            for(int i=0;i<edge[u].size();i++){
                int& v = edge[u][i];
                if(!cut[v]) v = fa[v];
            }
            continue;
        }
        for(int i=0;i<edge[u].size();i++){
            int& v = edge[u][i];
            if(!cut[v]) v = fa[v];
            if(v == fa[u]) continue;
            if(fa[v] == fa[u] && !cut[v]) continue;
            edge[fa[u]].push_back(v);//可能有边多次push入
        }
    }
    for(int i=1;i<=n;i++){
        if(cut[i]){
            edge[i].deduplicate();
        }else if(!vis[fa[i]]){
            edge[fa[i]].deduplicate();
            vis[fa[i]] = 1;
        }
    }
}

void solve(){
    makeSet(n);
    Tarjan(1, 0);
    int nRootSons = 0;
    for(int i=2;i<=n;i++){
        int v = father[i];
        if(v == 1) nRootSons++;
        else if(dfn[v] <= low[i]){
            cut[v] = true; 
            fa[v] = ++bcc;
        }
    }
    if(nRootSons > 1){
        cut[1] = true;
        fa[1] = ++bcc;
    }
    cout<<"DEBUG:\n";
    for(int i=1;i<=n;i++){
        cout<<"i: "<<i<<" dfn: "<<dfn[i]<<" low: "<<low[i]<<" father: "<<father[i];
        cout<< " fa: "<<fa[i];
        if(cut[i]) cout<<" CUT ";
        cout<<endl;
    }

    compress();
    
    cout<<"DEBUG:\n";
    for(int i=1;i<=n;i++){
        cout<<i<<": ";
        edge[i].print();
    }
}

void qdfs(int s, int t, bool & f){
    if(s == t) {f = true; return;}
    vis[s] = 1;
    for(int i=0;i<edge[s].size();i++){
        if(f) return;
        int v = edge[s][i];
        v = cut[v] ? v : fa[v];
        if(v == s || vis[v] == 1) continue;
        stack[++top] = v;
        qdfs(v, t, f);
        if(!f) top--;
    }
    return;
}

int cmp(const void * a, const void * b){
    return *(int *) a - *(int *)b;
}

void query(int s, int t){
    memset(vis, 0, 4*MAXN);
    top = -1;
    stack[++top] = s;
    stack[++top] = t;
    bool f = false;
    qdfs(fa[s], fa[t], f);
    if(top > 2) top--;
    //sort
    qsort(stack, top+1, sizeof(int), cmp);
    for(int i=0;i<=top;i++){
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main()
{
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