#include "sort.h"
#include <cstdlib>
#include <cstdio>
int buff[1000010];
using namespace std;

bool comp(int x, int y){ // x < y 
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
	int data[5];
    int p[4], end[4];
	int dmax = -1;
public:
    void build(int L, int ml, int m, int mr, int R){
        p[0] = L, p[1] = ml+1, p[2] = m + 1, p[3] = mr + 1;
        end[0] = ml, end[1] = m, end[2] = mr, end[3] = R;
        for(int i = 0;i < 4;i++){
            data[i] = buff[p[i]];
            p[i]++;
        }
		dmax = -1;
    }
	void initial(){
		int max, min;
		compare(data[0], data[1], data[2], &max, &min);
		dmax = comp(max, data[3]) ? data[3] : max;
	}
	void print(){
        for (int i = 0; i < 4; i++)
        {
            printf("data[%d] = %d\n", i, data[i]);
        }
    }
	void compare_(int a, int b, int c, int * ma, int * mi){
		if(a == -1){
			if(b == -1){
				b = c; a = c;
			}else{
				a = b;
				if(c == -1) c = b;
			}
		}else{
			if(b == -1) b = a;
			if(c == -1) c = a;
		}
		if(a == b && b == c){
			*ma = a; *mi = a;
			return;
		}
		compare(a, b, c, ma, mi);
	}
    int get(){
		if(dmax == -1){
			initial();
		}
		int max, min;
		int temp[4], cnt = 0;
		if(dmax == -2){
			for(int i=0;i<3;i++){
				if(data[i] != -1){
					temp[cnt++] = i;
				}else{
					temp[cnt++] = 3;
				}
			}
		}else{
			for(int i=0;i<4;i++){
				if(dmax != data[i]){
					temp[cnt++] = i;
				}
			}
		}
		compare_(data[temp[0]], data[temp[1]], data[temp[2]], &max, &min);
		dmax = max;
		for(int i=0;i<4;i++){
			if(data[i] == -1) dmax = -2;
			if(min == data[i]){
				if(p[i] <= end[i]){
					data[i] = buff[p[i]++];
				}else{
					data[i] = -1;
				}
			}
		}
		return min;
    }
}tt;

inline void merge_2(int * a, int l, int r){
	int max, min;
	compare(a[l], a[l], a[r], &max, &min);
	a[l] = min, a[r] = max;
	return;
}

inline void merge_3(int * a, int l, int m, int r){
	int max, min;
	compare(a[l], a[m], a[r], &max, &min);
	int mid = a[l] + a[m] + a[r] - max - min;
	a[l] = min, a[m] = mid, a[r] = max;
	return;
}

void merge_4(int * a, int L, int ml, int m, int mr, int R){
	//[L, ml], [ml + 1, m], [m + 1, mr], [mr + 1, R]
	for(int i = L;i <= R;i++) buff[i] = a[i];
    tt.build(L, ml, m, mr, R);
    int p = L;
    while(p <= R){
        a[p++] = tt.get();
    }
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
