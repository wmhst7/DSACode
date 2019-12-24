#include "sort.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
int buff[1000010];
using namespace std;
#define _MIN -1
#define _MAX -2

bool comp(int x, int y){ // x < y 
	if(x == _MIN || y == _MAX) return true;
	if(y == _MIN || x == _MAX) return false;
	int max, min;
	compare(x, y, y, &max, &min);
	return max == y;
}

inline void swap(int &a, int &b){
	int t = a;
	a = b, b = t;
}

class LoserTree_4{
private:
	int ls[5], data[5];
    int p[4], end[4];
	void adjust(int i){
        //printf("adjust(%d)\n", i);
		int f = (i + 4) >> 1;
        // while(f > 0){
        //     if(comp(data[ls[f]], data[i])){ // f < i 
        //         swap(i, ls[f]);
        //     }
        //     f /= 2;
        // }
        // ls[0] = i;
		
	}
public:
    void build(int L, int ml, int m, int mr, int R){
        p[0] = L, p[1] = ml+1, p[2] = m + 1, p[3] = mr + 1;
        end[0] = ml, end[1] = m, end[2] = mr, end[3] = R;
        for(int i = 0;i < 4;i++){
            ls[i] = 4;
            data[i] = buff[p[i]];
            p[i]++;
        }
        data[4] = _MIN;
        for(int i = 3;i >= 0;i--){
            adjust(i);
        }
        //print();
    }
    void print(){
        for (int i = 0; i < 4; i++)
        {
            printf("%d: ls = %d, data = %d\n", i, ls[i], data[i]);
        }
    }
    int get(){
        int i = ls[0];
        int res = data[i];
        //printf("\nget: %d\n", res);
        //print(); 
        if(p[i] <= end[i]){
            data[i] = buff[p[i]];
            p[i]++;
        }else{
            data[i] = _MAX;
        }
        adjust(i);
        return res;
    }
}tt;

inline void merge_2(int * a, int l, int r){
	//printf("merge_2(%d, %d)\n", l, r);
	int max, min;
	compare(a[l], a[l], a[r], &max, &min);
	a[l] = min, a[r] = max;
	return;
}

inline void merge_3(int * a, int l, int m, int r){
	//printf("merge_3(%d, %d, %d)\n", l , m, r);
	int max, min;
	compare(a[l], a[m], a[r], &max, &min);
	int mid = a[l] + a[m] + a[r] - max - min;
	a[l] = min, a[m] = mid, a[r] = max;
	return;
}

void merge_4(int * a, int L, int ml, int m, int mr, int R){
	//printf("merge_4(%d, %d, %d, %d, %d)\n", L, ml, m, mr, R);
	//[L, ml], [ml + 1, m], [m + 1, mr], [mr + 1, R]
	for(int i = L;i <= R;i++) buff[i] = a[i];
    tt.build(L, ml, m, mr, R);
    int p = L;
    while(p <= R){
        a[p++] = tt.get();
    }
}

void mergesort(int * a, int L, int R){
	//printf("mergesort(%d, %d)\n", L, R);
	if(L == R){
		return;
	}else if(R - L == 1){
		merge_2(a, L, R);
	}else if(R - L == 2){
		merge_3(a, L, L + 1, R);
	}else{
		int m = (L + R) >> 1; //1
		int ml = (L + m) >> 1; //0
		int mr = (R + m) >> 1; //2
		mergesort(a, L, ml); //0,0
		mergesort(a, ml+1, m); //1,1
		mergesort(a, m+1, mr); //2,2
		mergesort(a, mr+1, R); //3,3
		merge_4(a, L, ml, m, mr, R);
	}
}

void sort(int n, int limit, int *a) {
	mergesort(a, 0, n - 1); //Closed interval
}
