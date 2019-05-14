#include "pch.h"

using namespace std;  

template<typename Comparable>
//堆排序，下标从0开始，左儿子下标为2i+1
void heapSort(vector<Comparable>& array) {
	//构建二叉堆
	for (int i = array.size() / 2 - 1; i >= 0; i--)
		percDown(array, i, array.size());
	//最大项放在数组尾部，以达到删除最大项
	for (int j = array.size() - 1; j > 0; j--) {
		std::swap(array[0], array[j]);
		percDown(array, 0, j);
	}
}

//返回左儿子的下标，因为数组下标从0开始
inline int leftChild(int i) {
	return 2 * i + 1;
}

//i是开始下滤的位置，n是二叉堆的逻辑大小
template<typename Comparable>
void percDown(vector<Comparable>& array, int i, int n) {
	int child;
	Comparable temp;
	for (temp = std::move(array[i]); leftChild(i) < n; i = child) {
		child = leftChild(i);
		if (child != n - 1 && array[child] < array[child + 1])
			child++;
		if (temp < array[child])
			array[i] = std::move(array[child]);
		else
			break;
	}
	array[i] = std::move(temp);
}



int main() {
	vector<int> array = { 11, 52 ,3 ,99, 65, 25, 45 ,19 ,35 };
	heapSort(array);
	for (const auto& a : array)
		cout << a << endl;
	return 0;
}