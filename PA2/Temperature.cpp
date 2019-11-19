// PA2-5 Temperature
#include "temperature.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#define MAXN 600000+5
#define DEBUG
#define ll long long
#define cmax(a,b) (a<b?a=b:a)
#define cmin(a,b) (a<b?a=a:b)
using namespace std;
int D = 0, N, cnt = 0, tmi, tma, Root;

struct node{
    int d[2]; //当前节点坐标
    int ma, mi; //区域内温度极值
    int lc, rc; //子节点
    int lb[2], hb[2]; //区域边界
    //方法
    int & operator[](int i){
        return d[i];
        }
    friend bool operator < (node & a, node & b){
        return a[D] < b[D];//D为0：按x比大小
    }
}tr[MAXN];//KDTree 

struct Point{
    int d[2];
    int tem;
    int & operator[](int i){
        return d[i];
        }
    friend bool operator < (node & a, node & b);
}p[MAXN];//存节点信息
//点编号：[0, n)

int nth_element(Point * a,int l, int k, int r){
    //对数组a[l, r]排序,使a[k]左侧均小于它，右侧均大于它
    
}

void tr_equal_p(int m){//将p[m]的位置信息更新到tr[m]中
    tr[m][0] = tr[m].lb[0] = tr[m].hb[0] = p[m][0];
    tr[m][1] = tr[m].lb[1] = tr[m].hb[1] = p[m][1];
    tr[m].mi = tr[m].ma = p[m].tem;
}

int check(int X1, int X2, int Y1, int Y2, int x1, int x2, int y1, int y2){
    //X,Y包含于x,y return 0
    //相交 return 1
    //相离 return 2
    int minx = max(X1,x1);
    int miny = max(Y1,y1);
    int maxx = min(X2,x2);
    int maxy = min(Y2,y2);
    if(minx > maxx || miny > maxy){
        return 2;
    }else if(minx == X1 && miny == Y1 && 
            maxx == X2 && maxy == Y2){
        return 0;
    }else{
        return 1;
    }
}

void pushup(int mid){
    if(tr[mid].lc != -1){
        cmax(tr[mid].ma, tr[tr[mid].lc].ma);
        cmin(tr[mid].mi, tr[tr[mid].lc].mi);
    }
    if(tr[mid].rc != -1){
        cmax(tr[mid].ma, tr[tr[mid].rc].ma);
        cmin(tr[mid].mi, tr[tr[mid].rc].mi);
    }
}

int build(int l, int r, int now){
    if(l > r) return -1;//双-1代表为叶子
    int mid = (l+r)>>1;
    D = now;//操作哪一维
    nth_element(p, l, mid, r);
    tr_equal_p(mid);
    tr[mid].lc = build(l, mid-1, now^1);
    tr[mid].rc = build(mid+1, r, now^1);
    pushup(mid);
    return mid;
}

bool isLeaf(int m){
    if(tr[m].lc >= 0 || tr[m].rc >= 0) 
        return false;
    return true;
}

bool inside(int m, int x1, int x2, int y1, int y2){
    int x = tr[m][0];
    int y = tr[m][1];
    if(x1 <= x && y1 <= y && x <= x2 && y <= y2)
        return true;
    return false;
}

int checkregion(int m, int x1, int x2, int y1, int y2){
    int X1 = tr[m].lb[0];
    int X2 = tr[m].hb[0];
    int Y1 = tr[m].lb[1];
    int Y2 = tr[m].hb[1];
    return check(X1, X2, Y1, Y2, x1, x2, y1, y2);
}

void report(int m){
    if(tmi != -1)
        cmin(tmi, tr[m].mi);
    else
        tmi = tr[m].mi;
    if(tma != -1)
        cmax(tma, tr[m].ma);
    else
        tma = tr[m].ma;
}

void search(int m, int x1, int x2, int y1, int y2)
{
    if(isLeaf(m)){
        if(inside(m, x1, x2, y1, y2)){
            report(m);
            return;
        }
    }
    int m_lc = tr[m].lc;
    int ch = checkregion(m_lc ,x1, x2, y1, y2);
    if(ch == 0){//包含于
        report(m_lc);
    }else if(ch == 1){//相交
        search(m_lc, x1, x2, y1, y2);
    }//相离
    int m_rc = tr[m].rc;
    ch = checkregion(m_rc ,x1, x2, y1, y2);
    if(ch == 0){//包含于
        report(m_rc);
    }else if(ch == 1){//相交
        search(m_rc, x1, x2, y1, y2);
    }//相离
    return;
}

void init(int n, const int *x, const int *y, const int *temp){
    N = n;
    for(int i = 0;i<n;i++){
        p[i][0] = x[i];
        p[i][1] = y[i];
        p[i].tem = temp[i];
    }
    Root = (N-1)>>1;
    build(0, N-1, 0);
}

void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax){
    tmi = -1;
    tma = -1;
    search(x1, x2, y1, y2, Root);
    tmin[cnt] = tmi;
    tmax[cnt] = tma;
    cnt++;
}
