#include "pch.h"

using namespace std;  

/*对于任意位置i的元素，其左儿子在2i位置上
*右儿子在2i+1上，父节点在2/i上
*/
template<typename Comparable>
class BinaryHeap {
private:
	int currrentSize;
	vector<Comparable> array;
	void buildHeap();
	void percolateDown(int hole);
public:
	explicit BinaryHeap(int capacity = 100) :currrentSize(0), array(capacity) {};
	explicit BinaryHeap(const vector<Comparable>& item);
	bool isEmpty() const {
		return currrentSize == 0 ? true : false;
	}
	const Comparable& findMin() const;
	void insert(const Comparable& x);
	void insert(Comparable&& x);
	void deleteMin();
	void deleteMin(Comparable& minItem);
	void makeEmpty();
};

template<typename Comparable>
const Comparable& BinaryHeap<Comparable>::findMin() const{
	return array[1];
}

template<typename Comparable>
//空洞上滤，允许重复元
void BinaryHeap<Comparable>::insert(const Comparable& x){
	//如空间不足则扩大两倍
	if (currrentSize == array.size() - 1)
		array.resize(array.size() * 2);
	//确定空洞位置
	int hole = ++currrentSize;
	Comparable copy = x;
	//在零处放置需插入元素用于终止在根部的插入
	array[0] = std::move(copy);
	//上滤
	for (; x < array[hole / 2]; hole /= 2)
		array[hole] = std::move(array[hole / 2]);
	array[hole] = std::move(array[0]);
}

template<typename Comparable>
void BinaryHeap<Comparable>::insert(Comparable&& x){
	if (currrentSize == array.size() - 1)
		array.resize(array.size() * 2);
	int hole = ++currrentSize;
	array[0] = std::move(x);
	for (; x < array[hole / 2]; hole /= 2)
		array[hole] = std::move(array[hole / 2]);
	array[hole] = std::move(array[0]);
}

template<typename Comparable>
//删除最小项，如果为空则抛出underflow_error
void BinaryHeap<Comparable>::deleteMin(){
	if (isEmpty())
		throw underflow_error("123");
	array[1] = std::move(array[currrentSize--]);
	percolateDown(1);
}

template<typename Comparable>
//删除最小项并放在minItem处，如为空则抛出underflow_error
void BinaryHeap<Comparable>::deleteMin(Comparable& minItem){
	if (isEmpty())
		throw underflow_error("123");
	minItem = std::move(array[1]);
	array[1] = std::move(array[currrentSize--]);
	percolateDown(1);
}

template<typename Comparable>
void BinaryHeap<Comparable>::makeEmpty(){
	array.clear();
	currrentSize = 0;
}

template<typename Comparable>
//在堆中进行下滤的内部方法，空穴是下滤开始的下标
void BinaryHeap<Comparable>::percolateDown(int hole){
	int child;
	Comparable tmp = std::move(array[hole]);
	for (; hole * 2 <= currrentSize; hole = child) {
		child = hole * 2;
		if (child != currrentSize && array[int(child) + 1] < array[child])
			child++;
		if (array[child] < tmp)
			array[hole] = std::move(array[child]);
		else
			break;
	}
	array[hole] = std::move(tmp);
}

template<typename Comparable>
//先拷贝一个无序数组，再调用下滤使其有序
BinaryHeap<Comparable>::BinaryHeap(const vector<Comparable>& item):array(int(item.size()) + 10), currrentSize(item.size()){
	for (int i = 0; i < item.size(); i++)
		array[i + 1] = item[i];
	buildHeap();
}

template<typename Comparable>
//对非叶节点进行下滤
void BinaryHeap<Comparable>::buildHeap(){
	for (int i = currrentSize / 2; i > 0; --i)
		percolateDown(i);
}

int main() {
	BinaryHeap<int> a;
	for (int i = 1; i < 100; i++)
		a.insert(i);
	cout << a.findMin() << endl;
	a.makeEmpty();	
	return 0;
}