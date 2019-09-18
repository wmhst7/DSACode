#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

ll a[630], b[630], c[1260];          //计算中间数据
char res[10010], aa[5005], bb[5005]; //存结果，输入数据
int n;                               //记录规模
const int base = pow(10, 8);         //压位大小为8位

void Multiply()
{
    //初始化处理，得到倒序存储的压位数组
    memset(a, 0, 630 * sizeof(ll));
    memset(b, 0, 630 * sizeof(ll));
    memset(c, 0, 1260 * sizeof(ll));
    memset(res, 0, 10010 * sizeof(char));
    int hi = 5000, tem, la = 0, lb = 0;
    while (hi-- > 0)
    {
        if (aa[hi] == '#' || aa[hi] == 0)
            continue;
        if (hi <= 7)
        {
            tem = 0;
            for (int i = 0; i <= hi; i++)
            {
                tem += (aa[i] - '0') * pow(10, hi - i);
            }
            a[la++] = tem;
            break;
        }
        tem = 0;
        for (int i = 0; i < 8; i++)
        {
            tem += (aa[hi - i] - '0') * pow(10, i);
        }
        hi -= 7;
        a[la++] = tem;
    }
    hi = 5000;
    while (hi-- > 0)
    {
        if (bb[hi] == '#' || bb[hi] == 0)
            continue;
        if (hi <= 7)
        {
            tem = 0;
            for (int i = 0; i <= hi; i++)
            {
                tem += (bb[i] - '0') * pow(10, hi - i);
            }
            b[lb++] = tem;
            break;
        }
        tem = 0;
        for (int i = 0; i < 8; i++)
        {
            tem += (bb[hi - i] - '0') * pow(10, i);
        }
        hi -= 7;
        b[lb++] = tem;
    }
    //计算过程
    ll t = 0;
    for (int i = 0; i < la; i++)
    {
        for (int j = 0; j < lb; j++)
        {
            c[j + i] += a[i] * b[j]; //按位乘积
            t = c[j + i] / base;     //进位
            c[j + i + 1] += t;       //进位
            c[j + i] %= base;        //进位
        }
    }
    //得到结果
    hi = la + lb;
    ll m = 0;           //临时变量
    bool begin = false; //用于去除首位的0
    while (hi > 0)
    {
        if (c[hi] != 0)
            break;
        hi--;
    }
    t = 0; //临时变量，表示res长度
    for (int i = hi; i >= 0; i--)
    {
        for (int k = 0; k < 8; k++)
        {
            m = (c[i] / (ll)pow(10, 7 - k)) % 10; //提取10进制下一个数位
            if (m != 0)
                begin = true;
            if (begin)
            {
                res[t++] = (char)(m + '0');
            }
        }
    }
    if (t == 0) //如果结果为0
    {
        res[t] = '0';
        t++;
    }
    res[t] = '\0'; //处理字符串末位
}

int main()
{
    cin >> n;
    for (int k = 0; k < n; k++)
    {
        memset(aa, '#', 5005 * sizeof(char));
        memset(bb, '#', 5005 * sizeof(char));
        scanf("%s %s", aa, bb);
        Multiply();
        printf("%s\n", res);
    }
    return 0;
}