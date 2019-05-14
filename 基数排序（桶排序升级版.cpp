#include "pch.h"
#include <initializer_list>

using namespace std;  

//获取最大值的位数
int getDigit(const vector<int>& a) {
	int max = a[0];
	int digit = 0;
	for (const int& i : a)
		if (i > max)
			max = i;
	while (max) {
		max /= 10;
		digit++;
	}
	return digit;
}

//获取特定位上的数字
int getNum(int n, int digit) {
	for (int i = 1; i < digit; i++) {
		n /= 10;
	}
	return n % 10;
}


void radixSort(vector<int>& a) {
	int digits = getDigit(a);
	vector<list<int>> bucket(10);
	//循环到最大位数
	for (int digit = 1; digit <= digits; digit++) {
		//根据对应位上的数字大小放入桶中
		for (auto& i : a) {
			bucket[getNum(i, digit)].push_back(i);
		}
		a.clear();
		//从0到9号桶通过队列取出后放入数组
		for(int j = 0; j < 10; j++)
			while (!bucket[j].empty()) {
				a.push_back(bucket[j].front());
				bucket[j].pop_front();
			}
	}
}

int main() {
	vector<int> a = { 100, 22, 36, 45, 68, 100, 22 };
	radixSort(a);
	for (int i : a)
		cout << i << endl;
	return 0;
}