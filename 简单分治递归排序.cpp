#include <iostream>
#include <vector>

using namespace std;
//递归分治排序，选取中间项，分出三组再进行合并
template<typename Comparable>
void sort(vector<Comparable> &items){
	if(items.size() > 1){
		vector<Comparable> smaller;
		vector<Comparable> same;
		vector<Comparable> bigger;
		Comparable chosenItem = items[items.size() / 2];
		//分组
		for(auto &i : items){
			if(i < chosenItem)
				smaller.push_back(i);
			else if(i > chosenItem)
				bigger.push_back(i);
			else
				same.push_back(i);
		}
		sort(smaller);
		sort(bigger);
		std::move(smaller.begin(), smaller.end(), items.begin());
		std::move(same.begin(), same.end(), items.begin() + smaller.size());
		std::move(bigger.begin(), bigger.end(), items.end() - bigger.size());
	}	
}


int main(){
	vector<int> a = {1, 55, 29, 44, 65 ,35, 84, 84 ,15, 64 ,0 ,145};
	sort(a);
	for(const auto & i : a)
		cout << i << endl;
	return 0;
}