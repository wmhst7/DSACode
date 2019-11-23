#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

void swap(int& a, int& b){
    int tem = a;
    a = b;
    b = tem;
}

int nth_element(int *a, int l, int k, int r)
{
    //对数组a[l, r]排序,使a[k]左侧均<=它，右侧均大于它
    if (l == r)
        return a[l];
    int pivot = a[l];
    int i = l+1, j = r;
    while (i < j)
    {
        while (i < j && a[j] > pivot) j--;
        while (i < j && a[i] <= pivot) i++;
        if (i < j){
            swap(a[i], a[j]);
        }
    }
    swap(a[i], pivot);
    if (i > k)
        return nth_element(a, l, k, i - 1);
    else if (i < k)
        return nth_element(a, i + 1, k, r);
    else
        return 0;
}



int main(){
    int a[10] = {2, 4, 3, 1, 6, 0, 2, 0, 5, 7};
    nth_element(a, 0, 4, 9);
    for(int i=0;i<10;i++) cout<<a[i]<<' ';
    cout<<endl;
}