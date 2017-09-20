/*
* author: fyy
* datetime: 2017/9/18 10:35
* description: �����̰����˺ܶೣ�õ��㷨��ʵ��
* purpose: �����Լ���Ϥc++��һЩ���ԣ���ϰһЩ���������ݽṹ�Լ��㷨�������̱�������Ҫ����ֱ������ʹ�ã��������Ļ���
*/
#include "heap.h"
/*
 * ���Զ����
 */

// ���������ݽṹ�� �ȽϹ����ǱȽ����ݽṹ�ڵ����������ĳ˻�
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