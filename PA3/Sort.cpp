#include "sort.h"
#include <cstdlib>
#include <cstdio>

inline void swap(int &a, int &b) {
	int t = a;
	a = b, b = t;
}

inline void merge_2(int * a, int l, int r){
	int max, min;
	compare(a[l], a[l], a[r], &max, &min);
	a[l] = min, a[r] = max;
}

inline void merge_3(int * a, int l, int m, int r){
	int max, min;
	compare(a[l], a[m], a[r], &max, &min);
	int mid = a[l] + a[m] + a[r] - max - min;
	a[l] = min, a[m] = mid, a[r] = max;
}

void merge_4(int * a, int L, int ml, int m, int mr, int R){
	//[L, ml], [ml + 1, m], [m + 1, mr], [mr + 1, R]
	
}

void mergesort(int * a, int L, int R){
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
