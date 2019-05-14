#include "pch.h"

using namespace std;  

template<typename Comparable>
//插入排序，相当于挖空后把所有比他大的数往后移动
void insertSort(vector<Comparable>& array) {
	for (int i = 1; i < array.size(); i++) {
		Comparable temp = std::move(array[i]);
		int j;
		for (j = i; j > 0 && temp < array[j - 1]; j--)
			array[j] = std::move(array[j - 1]);
		array[j] = std::move(temp);
	}
}

template<typename Comparable>
//希尔排序，折半分组再每一组进行插入排序
void shellSort(vector<Comparable>& array) {
	//依次折半，对数组进行分组
	for (int gap = array.size() / 2; gap > 0; gap /= 2)
		//相当于插入法的两次循环
		for (int i = gap; i < array.size(); i++) {
			Comparable temp = std::move(array[i]);
			int j;
			//此循环的gap相当于插入排序的0
			for (j = i; j >= gap && temp < array[j - gap]; j -= gap)
				array[j] = std::move(array[j - gap]);
			array[j] = std::move(temp);
		}
}

int main() {
	vector<int> array = { 34, 8, 64, 51, 32, 21 };
	shellSort<int>(array);
	for (const auto& a : array)
		cout << a << endl;
	return 0;
}