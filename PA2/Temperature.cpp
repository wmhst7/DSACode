// PA2-5 Temperature
#include "temperature.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#define MAXN 600000
#define cmax(a,b) (a = a < b ? b : a)
#define cmin(a,b) (a = a < b ? a : b)
using namespace std;
int D = 0, N, tmi, tma, cnt = -1;

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
}tr[MAXN*4];//KDTree 

struct Point{
    int d[2];
    int ma, mi;
    int & operator[](int i){
        return d[i];
    }
    friend bool operator < (node & a, node & b);
}p[MAXN+5];//存节点信息, 点编号：[0, n)

void swap(Point & a, Point & b){
    Point tem = a;
    a = b;
    b = tem;
}

Point nth_element(Point * a, int l, int k, int r){
    //对数组a[l, r]排序,使a[k]左侧均小于等于它，右侧均大于它
    if (l == r)
        return a[l];
    Point & pivot = a[l];
    int i = l + 1, j = r;
    while (i < j)
    {
        while (i < j && a[j][D] > pivot[D]) j--;
        while (i < j && a[i][D] <= pivot[D]) i++;
        if (i < j){
            swap(a[i], a[j]);
        }
    }
    swap(a[i], pivot);
    if (i > k)
        return nth_element(a, l, k, i - 1);
    else if (i < k)
        return nth_element(a, i + 1, k, r);
    else
        return pivot;
}

void tr_equal_p(int m, int i){//将p[i]的位置信息更新到tr[m]中
    tr[m][0] = tr[m].lb[0] = tr[m].hb[0] = p[i][0];
    tr[m][1] = tr[m].lb[1] = tr[m].hb[1] = p[i][1];
    tr[m].mi = p[i].mi;
    tr[m].ma = p[i].ma;
}

int check(int X1, int X2, int Y1, int Y2, int x1, int x2, int y1, int y2){
    //X,Y包含于x,y return 0, 相交 return 1, 相离 return 2
    int minx = max(X1,x1), miny = max(Y1,y1);
    int maxx = min(X2,x2), maxy = min(Y2,y2);
    if(minx > maxx || miny > maxy){
        return 2;
    }else if(minx == X1 && miny == Y1 && 
            maxx == X2 && maxy == Y2){
        return 0;
    }else{
        return 1;
    }
}

void maintain(int f, int m){
    if(m != -1 && f != -1){
        cmax(tr[f].ma, tr[m].ma);
        cmin(tr[f].mi, tr[m].mi);
        cmin(tr[f].lb[0], tr[m].lb[0]);
        cmin(tr[f].lb[1], tr[m].lb[1]);
        cmax(tr[f].hb[0], tr[m].hb[0]);
        cmax(tr[f].hb[1], tr[m].hb[1]);
    }
}

void pushup(int mid){
    maintain(mid, tr[mid].lc);
    maintain(mid, tr[mid].rc);
}

int build(int l, int r){
    if(l == r){
        ++cnt;
        tr_equal_p(cnt, l);
        tr[cnt].lc = -1;
        tr[cnt].rc = -1;
        return cnt;
    }
    int mid = (l + r)>>1;
    //按方差划分
    double var0 = 0.0, mean0 = 0.0;
    double var1 = 0.0, mean1 = 0.0;
    int num = r - l + 1;
    for(int i=l;i<=r;i++){
        mean0 += p[i][0]/num;
        mean1 += p[i][1]/num;
    }
    for(int i=l;i<=r;i++){
        var0 += (p[i][0] - mean0) * (p[i][0] - mean0) / num;
        var1 += (p[i][1] - mean1) * (p[i][1] - mean1) / num;
    }
    D = var0 > var1 ? 0 : 1;
    nth_element(p, l, mid, r);
    int t = ++cnt;
    tr_equal_p(t, mid);
    tr[t].lc = build(l, mid);
    tr[t].rc = build(mid+1, r);
    pushup(t);
    return t;
}

bool isLeaf(int m){
    if(tr[m].lc >= 0 || tr[m].rc >= 0) 
        return false;
    return true;
}

bool inside(int m, int x1, int x2, int y1, int y2){
    int x = tr[m][0];
    int y = tr[m][1];
    if(x1 <= x && y1 <= y && 
        x <= x2 && y <= y2)
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
    //剪枝
    if(tr[m].mi >= tmi && tmi != -1 && tr[m].ma <= tma && tma != -1){
        return;
    }
    int ch;
    int m_lc = tr[m].lc;
    int m_rc = tr[m].rc;
    if(m_lc != -1){
        ch = checkregion(m_lc ,x1, x2, y1, y2);
        if(ch == 0){//包含于
            report(m_lc);
        }else if(ch == 1){//相交
            search(m_lc, x1, x2, y1, y2);
        }//相离
    }
    if(m_rc != -1){
        ch = checkregion(m_rc ,x1, x2, y1, y2);
        if(ch == 0){//包含于
            report(m_rc);
        }else if(ch == 1){//相交
            search(m_rc, x1, x2, y1, y2);
        }//相离
    }
    return;
}

void init(int n, const int *x, const int *y, const int *temp){
    for(int i = 0;i<n;i++){
        p[i][0] = x[i];
        p[i][1] = y[i];
        p[i].ma = temp[i];
        p[i].mi = temp[i];
    }
    N = n;
    build(0, N - 1);
}

void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax){
    tmi = -1;
    tma = -1;
    search(0, x1, x2, y1, y2);
    *tmin = tmi;
    *tmax = tma;
}

