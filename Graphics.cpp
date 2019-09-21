#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
#define ll long long

int n, m;
ll x[200005], y[200005];
ll xp, yp;

int cmp(const void *a, const void *b)
{
    return (int)(*(ll *)a - *(ll *)b);
}

ll BinSearch(ll lo, ll hi)
{
    while (1 < hi - lo)
    {
        ll mi = (lo + hi) / 2;
        if (x[mi] * yp + xp * y[mi] - x[mi] * y[mi] <= 0)
        {
            hi = mi;
        }
        else
        {
            lo = mi;
        }
    }
    if (lo == 0)
    {
        return x[0] * yp + xp * y[0] - x[0] * y[0] >= 0 ? 1 : 0;
    }
    return lo + 1;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &x[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &y[i]);
    }
    qsort(x, n, sizeof(ll), cmp);
    qsort(y, n, sizeof(ll), cmp);
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%lld", &xp);
        scanf("%lld", &yp);
        printf("%lld\n", BinSearch(0, n));
    }
    return 0;
}