#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <assert.h>
using namespace std;

template<class T>
class MyHeap{
	class MyHeapUnderflow : public exception{
		virtual const char* what() const throw(){
			return "My Heap Underflow";
		}
	};
	class MyHeapCompareErr : public exception{
		virtual const char* what() const throw(){
			return "You should provide compare function";
		}
	};

	inline int left(int i){ return (i << 1) | 0x1; }
	inline int right(int i){ return (i << 1) + 2; }
	inline int parent(int i){ return i >> 1; }
	inline bool safe_compare(T a, T b){
		if (compare != NULL)
			return (*compare)(a, b);
		else
			throw MyHeapCompareErr();
	}
	const int MAX_SIZE = 1 << 16;

	T* elements;
	int size = 0;
	int capcity = 1024;
	bool(*compare)(T element1, T element2);
	void heapify(int i);
	void build_heap();
	void heap_sort();

public:
	MyHeap(); // default constructor
	MyHeap(T* eles, int n, bool(*cmp)(T e1, T e2));
	~MyHeap(); // destructor

	// 拷贝初始化和赋值初始化，不急着实现
	//MyHeap(const MyHeap&); // copy contructor
	//MyHeap& operator= (const MyHeap&); // assignment constructor

	int get_size();
	T peek(); // peek the top of the heap
	T pop(); // return the top of the heap and remove it from the heap
	bool insert(T element); // insert an element into the key
	T* toList(); // return the 
};

template<class T>
void MyHeap<T>::heapify(int i){
	int l = left(i);
	int r = right(i);
	int largest = i;

	if (l < size && safe_compare(elements[l], elements[i])){
		largest = l;
	}
	if (r < size && safe_compare(elements[r], elements[largest])){
		largest = r;
	}
	if (largest != i){
		swap(elements[i], elements[largest]);
		heapify(largest);
	}
}

// 构建堆
template<class T>
void MyHeap<T>::build_heap(){
	for (int i = ((size - 1) >> 1); i >= 0; i--)
		heapify(i);
}

// 堆排序
template<class T>
void MyHeap<T>::heap_sort(){
	int size_cp = size;
	build_heap();
	for (int i = size_cp - 1; i >= 1; i--){
		swap(T[0], T[i]);
		heapify(0);
		size--;
	}
	size = size_cp;
}

// 默认构造函数
template<class T>
MyHeap<T>::MyHeap(){
	try{
		elements = new T[capcity];
		compare = NULL;
		size = 0;
	}
	catch (exception &e){
		cout << "Error occurs when initiate my heap:" << e.what() << endl;
	}

}

template<class T>
MyHeap<T>::MyHeap(T * eles, int n, bool(*cmp)(T e1, T e2)){
	try{
		// resize if necessary
		if (n > capcity)
		{
			while (n > capcity)capcity <<= 1;
		}
		elements = new T[capcity];
		memcpy(elements, eles, n*sizeof(T));
		compare = cmp;
		size = n;
		build_heap();
	}
	catch (exception & e){
		cout << "Error occurs when initaiate my heap:" << e.what() << endl;
	}
}


// 析构函数
template<class T>
MyHeap<T>::~MyHeap(){
	delete elements;
	//delete compare;
}

// 返回堆顶元素
template<class T>
T MyHeap<T>::peek(){
	if (size > 0){
		return elements[0];
	}
	else{
		throw MyHeapUnderflow();
	}
}

// 返回堆的大小
template<class T>
int MyHeap<T>::get_size(){
	return size;
}


// 弹出堆顶元素并将该元素返回
template<class T>
T MyHeap<T>::pop(){
	T top = peek();
	elements[0] = elements[size - 1];
	size--;
	heapify(0);
	return top;
}

// 插入元素，如果达到容量峰值，则返回false，成功插入返回true
template<class T>
bool MyHeap<T>::insert(T element){
	if (size == MAX_SIZE)
		return false;
	// double the capcity if necessary
	if (size == capcity){
		capcity <<= 1;
		T* elements_copy = new T[capcity];
		memcpy(elements_copy, elements, size*sizeof(T));
		delete elements;
		elements = elements_copy;
	}

	elements[size] = element;
	int i = size;
	while (i > 0 && safe_compare(elements[i], elements[parent(i)])){
		swap(elements[i], elements[parent(i)]);
		i = parent(i);
	}
	size++;
}

template<class T>
T* MyHeap<T>::toList(){
	T* result = new T[size];
	memcpy(result, elements, size*sizeof(T));
	return result;
}