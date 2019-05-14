#include <iostream>
#include <vector>

using namespace std;
template<typename Comparable>
void quickSort(vector<Comparable> &a, int left, int right);
//插入排序
template<typename Comparable>
void insertSort(vector<Comparable>& array, int left, int right) {
	for (int i = left + 1; i < right + 1; i++) {
		Comparable temp = std::move(array[i]);
		int j;
		for (j = i; j > left && temp < array[j - 1]; j--)
			array[j] = std::move(array[j - 1]);
		array[j] = std::move(temp);
	}
}

//快排驱动程序
template<typename Comparable>
void quickSort(vector<Comparable> &a){
	quickSort(a, 0, int(a.size() - 1));
}

/*
*返回left, center, right中的中位数
*将他们排序并隐匿枢纽元
*/
template<typename Comparable>
const Comparable & median3(vector<Comparable>& a, int left, int right){
	int center = (left + right) / 2;
	if(a[center] < a[left])
		std::swap(a[center], a[left]);
	if(a[right] < a[left])
		std::swap(a[right], a[left]);
	if(a[right] < a[center])
		std::swap(a[right], a[center]);
	//将center枢纽元置于right - 1，起到警戒标志的作用
	std::swap(a[center], a[right - 1]);
	return a[right - 1];
}

/*
*递归调用的内部快速排序方法
*使用三数值分割法以及截止范围是10(元素过少的话效率低
*a是数组，left是左下标，right是右下标
*/
template<typename Comparable>
void quickSort(vector<Comparable> &a, int left, int right){
	if(left + 10 <= right){
		const Comparable & pivot = median3(a, left, right);
		//开始分割
		int i = left, j = right - 1;
		while(1){
			//一直推进到a[i] >= pivot
			while(a[++i] < pivot){}
			//一直推进到a[j] <= pivot
			while(pivot < a[--j]){}
			if( i < j)
				std::swap(a[i], a[j]);
			else
				break;
		}
		std::swap(a[i], a[right - 1]);//恢复枢纽元
		quickSort(a, left, i - 1);//将小于枢纽元的元素排序
		quickSort(a, i + 1, right);//将大于枢纽元的元素排序
	}
	else
		//对最小子数组进行插入排序
		insertSort(a, left, right);
}


int main(){
	vector<int> a = {99, 11, 88, 22, 77, 33, 44, 66, 55, 12 ,98, 65, 45, 78, 34, 12, 65 ,95 ,15, 24};
	quickSort(a);
	for(const auto &i : a)
		cout << i << endl;
	return 0;
}