#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;
#define ll long long
#define MAXN 10000000
int N, M, cnt = 1;
ll tree[MAXN], lazy[MAXN];
int lc[MAXN], rc[MAXN];

void push_down(ll l, ll r, ll pos)
{ //下传
    if (lc[pos] == 0)
    {
        cnt++;
        lc[pos] = cnt;
    }
    if (rc[pos] == 0)
    {
        cnt++;
        rc[pos] = cnt;
    }
    ll mid = (l + r) >> 1;
    if (lazy[pos] > 0 && l != r)
    {
        lazy[lc[pos]] += lazy[pos];
        lazy[rc[pos]] += lazy[pos];
        tree[lc[pos]] += lazy[pos] * (mid - l + 1);
        tree[rc[pos]] += lazy[pos] * (r - mid);
        lazy[pos] = 0;
    }
}

void update(ll L, ll R, ll l, ll r, ll delta, ll pos)
{
    //递归基
    if (L <= l && r <= R)
    {
        lazy[pos] += delta;
        tree[pos] += delta * (r - l + 1);
        return;
    }
    //递归
    push_down(l, r, pos);
    ll mid = (l + r) >> 1;
    if (L <= mid)
        update(L, R, l, mid, delta, lc[pos]);
    if (mid < R)
        update(L, R, mid + 1, r, delta, rc[pos]);
    tree[pos] = tree[lc[pos]] + tree[rc[pos]];
    return;
}

ll query(ll L, ll R, ll l, ll r, ll pos)
{
    //递归基
    if (L <= l && r <= R)
    {
        return tree[pos];
    }
    //递归
    push_down(l, r, pos);
    ll mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid)
        res += query(L, R, l, mid, lc[pos]);
    if (mid < R)
        res += query(L, R, mid + 1, r, rc[pos]);
    return res;
}

int main()
{
    scanf("%d %d\n", &N, &M);
    char ch;
    ll a, b;
    for (int i = 0; i < M; i++)
    {
        scanf("%c %lld %lld\n", &ch, &a, &b);
        if (ch == 'H')
        {
            update(a, b, 1, N, 1, 1);
        }
        else if (ch == 'Q')
        {
            printf("%lld\n", query(a, b, 1, N, 1));
        }
    }
    return 0;
}