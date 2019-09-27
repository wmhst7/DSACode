#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long
int N;
ll l[1000010], r[1000010], t[1000010], T[1000010];

ll mmin(ll a, ll b)
{
    return a < b ? a : b;
}

int main()
{
    scanf("%d", &N);
    for (int i = 1; i < N; i++)
    {
        scanf("%lld %lld %lld", &l[i], &r[i], &t[i]);
    }
    T[N] = 0;
    for(int i = N-1;i>=1;i--){
        ll tem = INF;
        for(int j = l[i];j<=r[i];j++){
            tem = mmin(tem, T[j]);
        }
        T[i] = t[i]+tem;
    }
    // for (int i = 1; i <= N; i++)
    //     cout << "T[" << i << "]: " << T[i] << endl;
    printf("%lld\n", T[1]);
    return 0;
}
