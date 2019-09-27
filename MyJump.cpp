#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long
int N;
ll l[1000010], r[1000010], t[1000010], T[1000010];
int m, n;

int mmin(int a, int b)
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
    T[1] = 0;
    for (int i = 2; i <= N; i++)
        T[i] = INF;
    for (int i = 1; i < N; i++)
    {
        for (int j = l[i]; j <= r[i]; j++)
        {
            T[j] = mmin(T[j], T[i] + t[i]);
        }
    }
    //for (int i = 2; i <= N; i++)
        //cout << "T[" << i << "]: " << T[i] << endl;
    printf("%lld\n", T[N]);
    return 0;
}
