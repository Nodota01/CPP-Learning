#include "pch.h"

using namespace std;  

//并归排序算法，典型的分治算法
template<typename Comparable>
void mergeSort(vector<Comparable>& a) {
	//临时数组用于排序时临时储存
	vector<Comparable> tmpArray(a.size()); 
	mergeSort(a, tmpArray, 0, a.size() - 1);
}

/**“分”
*进行递归调用的内部方法
*a为Comparable项的数组
*tmpArray为放置归并结果的数组
*left为子数组最左元素的下标
*right为子数组最右元素的下标
*/
template<typename Comparable>
void mergeSort(vector<Comparable>& a, vector<Comparable>& tmpArray, int left, int right) {
	//一直分到只有两个元素
	if (left < right) {
		int center = (left + right) / 2;
		mergeSort(a, tmpArray, left, center);
		mergeSort(a, tmpArray, center + 1, right);
		merge(a, tmpArray, left, center + 1, right);
	}
}

/**“治”
*合并子数组已排序两部分的内部方法
*a 为 Comparable项的数组
*tempArray为放置归并结果的数组
*leftPos为最左元素的下标
*rightPos为后半部分起点的下标
*rightEnd为子数组最有元素的下标
*/
template<typename Comparable>
void merge(vector<Comparable>& a, vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd) {
	int leftEnd = rightPos - 1;
	//用于推进临时数组下标的指针数
	int tmpPos = leftPos;
	//记录子数组元素个数
	int elementNums = rightEnd - leftPos + 1;

	//主循环
	while (leftPos <= leftEnd && rightPos <= rightEnd){
		if (a[leftPos] <= a[rightPos])
			tmpArray[tmpPos++] = std::move(a[leftPos++]);
		else
			tmpArray[tmpPos++] = std::move(a[rightPos++]);
	}

	//当有一个部分还有剩余时全部复制进去
	while (leftPos <= leftEnd)
		tmpArray[tmpPos++] = std::move(a[leftPos++]);
	while (rightPos <= rightEnd)
		tmpArray[tmpPos++] = std::move(a[rightPos++]);

	//最后将临时数组的元素复制进子数组
	for (int i = 0; i < elementNums; i++, rightEnd--)
		a[rightEnd] = std::move(tmpArray[rightEnd]);
}

int main() {
	vector<int> a = { 11, 25, 0, 1, 98, 55, 44, 23 ,75 };
	mergeSort(a);
	for (const auto& a : a)
		cout << a << endl;
	return 0;
}