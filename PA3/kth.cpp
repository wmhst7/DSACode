#include "kth.h"
#include <cstdlib>
#include <cstdio>
#define COMa(x, u) compare(x, 1, 1, u, 1, 1)
#define COMb(x, u) compare(1, x, 1, 1, u, 1)
#define COMc(x, u) compare(1, 1, x, 1, 1, u)
#define MAXn 500010
#define MAXk 500000
int ak[MAXn], bk[MAXn], ck[MAXn]; 
//a[ak[1]...ak[n]] is Sorted.

struct Point{
	int x, y, z;
	Point(){
		x = 0; y = 0; z = 0;
	}
	Point(int q, int w, int e):x(q), y(w), z(e){} 
};

int cmp_a(const void * u, const void * v){
	//printf("cmp_a(%d, %d)\n", *(int *)u, *(int *)v);
	return COMa(*(int *)v, *(int *)u);
}
int cmp_b(const void * u, const void * v){
	return COMb(*(int *)v, *(int *)u);
}
int cmp_c(const void * u, const void * v){
	return COMc(*(int *)v, *(int *)u);
}

bool COM(Point p1, Point p2){
	// printf("COM(%d, %d, %d, %d, %d, %d)\n", p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
	// printf("compare(%d, %d, %d, %d, %d, %d)\n", ak[(p1).x], bk[(p1).y], ck[(p1).z], ak[(p2).x], bk[(p2).y], ck[(p2).z]);
	return compare(ak[(p1).x], bk[(p1).y], ck[(p1).z], ak[(p2).x], bk[(p2).y], ck[(p2).z]);
}

void Sort(int n){
	// printf("Sort\n");
	for(int i = 0;i <= n;i++){
		ak[i] = i; bk[i] = i; ck[i] = i;
	}
	qsort(ak + 1, n, sizeof(int), cmp_a);
	qsort(bk + 1, n, sizeof(int), cmp_b);
	qsort(ck + 1, n, sizeof(int), cmp_c);
	// for(int i=1;i<=n;i++){
	// 	printf("ak[%d] = %d, ", i, ak[i]);
	// 	printf("bk[%d] = %d, ", i, bk[i]);
	// 	printf("ck[%d] = %d\n", i, ck[i]);
	// }
	return;
}

//Heap Implementation Begin
template <typename T>
class Heap{
private:
	T elem[MAXk];//Root in 0
	int size = 0;

	void swap_elem(int i, int j){
		int t;
		t = elem[j].x; elem[j].x = elem[i].x; elem[i].x = t;
		t = elem[j].y; elem[j].y = elem[i].y; elem[i].y = t;
		t = elem[j].z; elem[j].z = elem[i].z; elem[i].z = t;
	}
	int percolateDown(int i){
		int j;
		while(i < size){
			if(2 * i + 2 < size){
				if (COM(elem[2 * i + 1], elem[2 * i + 2]))
					j = 2 * i + 1;
				else
					j = 2 * i + 2;
			}else if(2 * i + 1 < size){
				j = 2 * i + 1;
			}else{
				break;
			}
			if(COM(elem[j], elem[i])){
				swap_elem(i, j);
				i = j;
			}else{
				break;
			}
		}
		return i;
	}
	int percolateUp(int i){
		int j;
		while(i > 0){
			j = (i - 1) / 2;
			if(COM(elem[i], elem[j])){
				swap_elem(i, j);
				i = j;
			}else{
				break;
			}
		}
		return i;
	}
public:
	T getMin(){
		return elem[0];
	}

	void delMin(){
		// printf("delMin(%d, %d, %d)\n", elem[0].x, elem[0].y, elem[0].z);
		swap_elem(0, --size);
		percolateDown(0);
	}
	void insert(T p){
		// printf("insert(%d, %d, %d)\n",p.x, p.y, p.z);
		elem[size] = p;
		size++;
		percolateUp(size - 1);
	}

};
//Heap Implementation End

void get_kth(int n, int k, int *x, int *y, int *z) {
	//Sort
	Sort(n);
	Heap<Point> heap;
	heap.insert(Point(1, 1, 1));
	Point p;
	while(k){
		k--;
		p = heap.getMin();
		heap.delMin();
		// printf("k = %d, p = (%d, %d, %d)\n", k, p.x, p.y, p.z);
		if(p.x < n) heap.insert(Point(p.x + 1, p.y, p.z));
		if(p.y < n && p.x == 1) heap.insert(Point(p.x, p.y + 1, p.z));
		if(p.z < n && p.x == 1 && p.y == 1) heap.insert(Point(p.x, p.y, p.z + 1));
	}
	*x = ak[p.x]; *y = bk[p.y], *z = ck[p.z];
	return;
}



