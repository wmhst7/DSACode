#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
int n;
char *res = new char[10010];
int *a = new int[5005];
int *b = new int[5005];
long long *tem = new long long[10010];
char *A = new char[5005];
char *B = new char[5005];

//竖式大整数乘法
void multi()
{
    int lA = 0, lB = 0, t = 0;
    memset(res, '#', 10010 * sizeof(char));
    memset(tem, 0, 10010 * sizeof(long long));
    memset(a, 0, 5005 * sizeof(int));
    memset(b, 0, 5005 * sizeof(int));
    for (int i = 5004; i > -1; --i)
    { //倒序存大数
        if (A[i] >= '0')
        {
            a[lA] = A[i] - '0';
            lA++;
        }
        if (B[i] >= '0')
        {
            b[lB] = B[i] - '0';
            lB++;
        }
    }
    t = lB;
    while (t > 0)
    {
        for (int i = 0; i < lA; ++i)
        {
            tem[i + lB - t] += a[i] * b[lB - t];
        }
        t--;
    }
    //处理进位
    for (int i = 0; i < 10010-1; ++i)
    {
        tem[i + 1] += tem[i] / 10;
        tem[i] = tem[i] % 10;
    }
    //得到结果
    bool be = false;
    int cnt = 0;
    for (int i = 10009; i > -1; --i)
    {
        if (tem[i] != 0)
            be = true;
        if (be)
        {
            res[cnt] = char(tem[i] + '0');
            cnt++;
        }
    }
    if(cnt > 0){
        res[cnt] = '\0';
    }else{
        res[0] = '0';
        res[1] = '\0';
    }
    return;
}

int main()
{
    cin >> n;
    // cout << "n = " << n << endl;
    
    for (int i = 0; i < n; ++i)
    {
        memset(A, '#', 5005 * sizeof(char));
        memset(B, '#', 5005 * sizeof(char));
        scanf("%s %s", A, B);
        multi();
        cout<<res<<endl;
    }
    return 0;
}
