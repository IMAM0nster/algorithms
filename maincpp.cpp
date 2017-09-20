/*
* author: fyy
* datetime: 2017/9/18 10:35
* description: 本工程包含了很多常用的算法的实现
* purpose: 帮助自己熟悉c++的一些特性，复习一些基础的数据结构以及算法，如果编程笔试中需要可以直接拿来使用（如果允许的话）
*/
#include "heap.h"
/*
 * 测试二叉堆
 */

// 测试用数据结构， 比较规则是比较数据结构内的两个整数的乘积
struct A{
	int x;
	int y;
};

bool cmpA(A a1, A a2){
	return a1.x*a1.y > a2.x*a2.y;
}

void testCaseHeap(){
	A a1 = { 1, 2 };
	A a2 = { 2, 3 };
	A a3 = { 4, 1 };
	A a4 = { 1, 5 };
	A as[4] = { a1, a2, a3, a4 };
	MyHeap<A> myheap2 = MyHeap<A>((A*)as, 4, cmpA);
	assert(myheap2.get_size() == 4);
	assert(myheap2.peek().x == 2);
	myheap2.pop();
	assert(myheap2.peek().y == 5);
	myheap2.insert({ 3, 1 });
	A* rs = myheap2.toList();
	A ans[4] = { a4, { 3, 1 }, a3, a1 };
	for (int i = 0; i < myheap2.get_size(); ++i){
		assert(rs[i].x == ans[i].x);
		assert(rs[i].y == ans[i].y);
	}
}

int main(){
	testCaseHeap();
	cout << "Congratulations! All test cases are passed" << endl;
	return 0;
}