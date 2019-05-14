#include <iostream>
#include <vector>

using namespace std;

int getMax(vector<int>& array){
	int max = array[0];
	for(int& i : array)
		if(i > max)
			max = i;
	return max;
}

bool bucketSort(vector<int>& array){
	int size = getMax(array);
	vector<int> bucket(size, 0);
	for(int& i : array)
		bucket[i]++;
	array.clear();
	for(int i = 0; i < size; i++)
		for(int j = 0; j < bucket[i]; j++)
			array.push_back(i);
}

int main(){
	vector<int> array = {11, 22, 35, 65, 65, 65, 88, 15, 45, 15};
	bucketSort(array);
	for(int& i : array)
		cout << i << endl;
	return 0;
}