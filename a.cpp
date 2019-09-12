#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
int n;
char *res = new char[10010];

//大整数乘法
char *multi(char *A, char *B)
{
	int lA = 0, lB = 0, t = 0;
	int *a = new int[5005];
	int *b = new int[5005];
	int *tem = new int[10010];
	memset(res, '#', 10010);
	memset(tem, 0, 10010);
	memset(a, 0, 5005);
	memset(b, 0, 5005);
	for (int i = 5004; i > -1; --i)
	{ //倒序存大数
		if (A[i] != '#' && A[i] >= '0')
		{
			a[lA] = A[i] - '0';
			lA++;
		}
		if (B[i] != '#' && B[i] >= '0')
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
	for (int i = 0; i < 10010 - 1; ++i)
	{
		if (tem[i] == 0)
			break;
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
	res[cnt] = '\n';
	return res;
}

int main()
{
	cin >> n;
	// cout << "n = " << n << endl;
	char *a = new char[5005];
	char *b = new char[5005];
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 5050; ++j)
		{
			a[j] = '#';
			b[j] = '#';
		}
		scanf("%s %s", a, b);
		// cout << a << ' ' << b << endl;
		multi(a, b);
		for (int t = 0; t < 10010; t++)
		{
			if (res[t] != '#')
			{
				printf("%c", res[t]);
			}
		}
	}
	return 0;
}
