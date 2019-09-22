#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
#define INF 0x3f3f3f3f
int N, M, K;
char A[501010], B[501010];
int res;
bool flag; //true->d is the first
int *d, *p, *a, *b;

int mmin(int a, int b, int c = INF)
{
    int t = a < b ? a : b;
    return t < c ? t : c;
}

int main()
{
    a = new int[501010];
    b = new int[501010]; //优化存储
    scanf("%d %d %d", &N, &M, &K);
    scanf("%s", A);
    scanf("%s", B);
    flag = true;
    d = a;
    p = b;
    for (int i = 0; i <= M; i++)
    {
        d[i] = i;
    }
    for (int i = 1; i <= N; i++)
    {
        int lo = i - K - 1 < 0 ? 0 : i - K - 1;
        int hi = i + K + 1 > M ? M : i + K + 1;
        for (int j = lo; j <= hi; j++)
        {
            if (flag)
            {
                d = a;
                p = b;
            }
            else
            {
                d = b;
                p = a;
            }
            if (j == 0)
            {
                p[j] = i;
                continue;
            }
            if (A[i - 1] == B[j - 1])
            {
                if (j == i - K - 1)
                {
                    p[j] = mmin(d[j] + 1, d[j - 1]);
                }
                else if (j == i + K + 1)
                {
                    p[j] = mmin(p[j - 1], d[j - 1] + 2);
                }
                else
                {
                    p[j] = mmin(p[j - 1] + 1, d[j] + 1, d[j - 1]);
                }
            }
            else
            {
                if (j == i + K + 1)
                {
                    p[j] = mmin(p[j - 1], d[j - 1] + 2);
                }
                else if (j == i - K - 1)
                {
                    p[j] = mmin(d[j] + 1, d[j - 1]);
                }
                else
                {
                    p[j] = mmin(p[j - 1] + 1, d[j] + 1, d[j - 1] + 2);
                }
            }
        }
        flag = !flag;
    }
    res = p[M] > K ? -1 : p[M];
    cout << res << endl;
    return 0;
}
