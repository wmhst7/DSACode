#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

#define DEAFAULT_CAPACITY 64
#define Rank int

//My Vector
template <typename T> 
class Vector{
	private:
		Rank _size; 
		int _capacity; 
		T* _elem; 

	protected:
		void copy_from(const T* A, Rank lo, Rank hi){
			_capacity = std::max(DEAFAULT_CAPACITY, hi - lo);_size = 0;
			_elem = new T[_capacity];
			while(_size < hi - lo){
				_elem[_size] = A[lo + _size];_size++;
			}
		}
		void expand(){
			if(_size < _capacity) return;
			T* oldelem = _elem;
			_elem = new T[_capacity*2];
			for(int i = 0;i < _capacity;i++)
				_elem[i] = oldelem[i];
			_capacity *= 2;
			delete[] oldelem;
		}
		void shrink(){
			if (_size > _capacity >> 1)
				return;
			T *oldelem = _elem;
			_elem = new T[_capacity >> 1];
			for(int i = 0; i < _size; i++)
				_elem[i] = oldelem[i];
			_capacity >>= 1;
			delete[] oldelem;
		}
		//相邻逆序对个数
		int disordered() const {
			int count = 0, i = 0;
			while(i < _size - 1) if(_elem[i] > _elem[i+1]) count++;
			return count;
		}

	public:
		Vector(int c = DEAFAULT_CAPACITY){
			_elem = new T[_capacity = c];
			_size = 0;
		}
		Vector(const T * A, Rank lo, Rank hi){
			copy_from(A, lo, hi);
		}
		Vector(Vector<T> const& V, Rank lo, Rank hi){
			copy_from(V._elem, lo, hi);
		}
		~Vector(){
			delete[] _elem;
		}
		int size(){return _size;}
		T& operator[](Rank i){
			//assert(0 <= i && i < _size);//为假停止
			return _elem[i];
		}
		void clear(){
			_size = 0;
		}
		void print(){
			if(_size < 1) {
				std::cout<<"Null"<<std::endl;
				return;
			}
			std::cout<<"[";
			for(Rank i = 0;i < _size - 1;i++)
				std::cout<<_elem[i]<<", ";
			std::cout<<_elem[_size - 1]<<"]\n";
		}
		Rank insert(Rank r, T const & e){
			expand();
			for(int i=_size;i>r;i--)
				_elem[i] = _elem[i-1];
			_elem[r] = e; _size++;
			return r;
		}
		int remove(Rank lo, Rank hi){
			if(lo >= hi) return 0;
			while(hi < _size) _elem[lo++] = _elem[hi++];
			_size = lo;shrink();
			return hi - lo;
		}
		T remove(Rank r){
			T e = (*this)[r];
			remove(r, r+1);
			return e;
		}
		Rank find(T const & e, Rank lo, Rank hi){
			while((lo < hi--) && e != _elem[hi]);
			return hi;//返回lo-1则无（注意最后一次while)
		}

		//返回不大于e的最后一个元素(rank max)
		Rank search(T const & e, Rank lo, Rank hi){
			return fibSearch(_elem, e, lo, hi);
		}
		
		int deduplicate(){//无序O(n^2)
			int oldSize = _size;
			Rank i = 1;
			while(i < _size)
				(find(_elem[i],0,i) < 0)? i++ 
				: remove(i);//自动减_size
			return oldSize - _size;
		}	
		int uniquify(){//有序向量的唯一化O(n)
			this->sort();
			Rank i=0,j=0;
			while(++j < _size){//用remove则O(n^2)
				if(_elem[i] != _elem[j]) _elem[++i] = _elem[j];
			}
			_size = ++i;shrink();
			return j - i;
		}
		//函数指针
		void traverse(void (*visit)(T&));
		//函数对象 优
		template <typename VST> 
		void traverse(VST& visit);

		void push_back(T e){
			_size++;
            expand();
			_elem[_size - 1] = e;
		}

		//Sort Algorithm
        void sort(){
            sort(0, _size);
        }
		void sort(Rank lo, Rank hi){
            bubbleSort(lo, hi);
		}
		void bubbleSort(Rank lo, Rank hi){
            while( lo < --hi ) 
                for( Rank i = lo; i < hi; i++ ) 
                    if( _elem[i] > _elem[i + 1] ){
                        T tem = _elem[i];
                        _elem[i] = _elem[i+1];
                        _elem[i+1] = tem;
                    }
		}
		void mergeSort(Rank lo, Rank hi){
			if(hi - lo < 2) return;
			Rank mi = (lo + hi)/2;
			mergeSort(lo, mi);
			mergeSort(mi, hi);
			merge(lo, mi, hi);
		}
		void merge(Rank lo, Rank mi, Rank hi){
			//std::cout<<lo<<' '<<mi<<' '<<hi<<std::endl;
			T* A = _elem + lo;
			Rank lb = mi - lo; 
			T* B = new T[lb]; //划出缓冲区B
			Rank lc = hi - mi;
			T* C = _elem + mi;
			for (Rank i = 0; i < lb; B[i] = A[i++]) 
			//B + C -> A
			for(Rank i = 0, j = 0, k = 0; j < lb; ){
				if ((k < lc) && (C[k] < B[j]))
					A[i++] = C[k++];
				if(lc <= k || (B[j] <= C[k]))
					A[i++] = B[j++];
			}
			delete[] B;
		}

};


template <typename T>
class Increase{//Increase i;i(T& e);
	virtual void operator()(T & e){e++;}
};

template <typename T> //封装实现的increase功能
void increase(Vector<T> & V){//increase(v);
	V.traverse(Increase<T>());
}

template <typename K, typename V> 
struct Entry
{
	K key; V value;
	Entry(K k = K(), V v = V()): key(k), value(v){}
	Entry(Entry<K,V> const & e): key(e.key), value(e.value){}
	bool operator== (Entry<K,V> const & e){return key == e.key;}
	bool operator!= (Entry<K,V> const & e){return key != e.key;}
	bool operator< (Entry<K,V> const & e){return key < e.key;}
	bool operator> (Entry<K,V> const & e){return key > e.key;}
	bool operator<= (Entry<K,V> const & e){return key <= e.key;}
	bool operator>= (Entry<K,V> const & e){return key >= e.key;}
};

