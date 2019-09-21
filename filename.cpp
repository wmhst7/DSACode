#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
#define ll long long
int N, M, K;
char A[5010010], B[5010010];
int f[5010010][5010010];
int res;

int mmin(int a, int b, int c)
{
    int t = a < b ? a : b;
    return t < c ? t : c;
}

int main()
{
    scanf("%d %d %d", &N, &M, &K);
    scanf("%s", A);
    scanf("%s", B);
    for (int i = 0; i <= N; i++)
    {
        f[i][0] = i;
    }
    for (int j = 0; j <= M; j++)
    {
        f[0][j] = j;
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            if (A[i] == B[j])
            {
                f[i][j] = mmin(f[i - 1][j - 1], f[i][j - 1], f[i - 1][j]);
            }
            else
            {
                f[i][j] = mmin(f[i - 1][j - 1] + 2, f[i][j - 1] + 1, f[i - 1][j] + 1);
            }
        }
    }
    res = f[N][M] > K ? -1 : f[N][M];
    printf("%d\n", res);
    return 0;
}
