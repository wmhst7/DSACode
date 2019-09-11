#include <iostream>
using namespace std;
int n;
char **a, **b;

//分治大整数乘法
char* multi(char* A, char* B){
    char *res = new char[10010];
    res[0] = '1';
    return res;
}

int main(){
    cin>>n;
    a = new char * [n];
    b = new char * [n];
    for(int i=0;i<n;++i){
        a[i] = new char[5005];
        b[i] = new char[5005];
        scanf("%s %s", a[i], b[i]);
        printf("%s\n", multi(a[i], b[i]));
    }
    return 0;
} 