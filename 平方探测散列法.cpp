#include "pch.h"


using namespace std;

bool isPrime(int n)
{
	int flag, i;
	flag = 1;
	for (i = 2; i <= sqrt(n); i++){
		if (n % i == 0){
			flag = 0;
			break;
		}
	}
	return flag;
}

int nextPrime(int n) {
	bool state = isPrime(n);
	while (state) {
		state = isPrime(++n);
	}
	return n;
}

template<typename HashedObj>
class HashTable {
private:
	//记录数据状态的枚举
	enum EntryType{ACTIVE, EMPTY, DELETED};
	//散列表项单元
	struct HashEntry {
		HashedObj element;
		EntryType info;
		HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY) :element(e), info(i) {};
	};
	//数据成员为数组
	vector<HashEntry> array;
	int currentSize;

	int myHash(const HashedObj& x)const {
		return x % array.size();
	}

	bool isActive(int currentpos) const {
		return array[currentpos].info == ACTIVE;
	}

	bool findPos(const HashedObj& x) const {
		int offset = 1;
		int currentPos = myHash(x);
		while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
			currentPos += offset; //计算第i次探测
			offset += x;
			if (currentPos >= array.size())
				currentPos -= array.size();
		}
		return currentPos;
	}
	//在散列，即放入一个更大的散列表中
	void rehash(){
		vector<HashEntry> oldArray = array;
		//创建两倍大的空表
		array.resize(nextPrime( 2 * oldArray.size()));
		for(auto &x : array)
			x.info = EMPTY;
		//复制整个表
		currentSize = 0;
		for(auto & entry : oldArray)
			if(entry.info == ACTIVE)
				insert(std::move(entry.element));
	}

public:

	HashTable(int size = 101) :array(nextPrime(size)), currentSize(0) {
		makeEmpty();
	}

	void makeEmpty() {
		currentSize = 0;
		for (auto& entry : array)
			entry.info = EMPTY;
	}

	bool contains(const HashedObj& x) const {
		return isActive(findPos(x));
	}

	bool insert(const HashedObj& x) {
		int currentPos = myHash(x);
		if (isActive(currentPos))
			return false;
		array[currentPos].element = x;
		array[currentPos].info = ACTIVE;
		//如装载超过了一半则再散列
		if (++currentSize >= array.size() / 2)
			rehash();
		return true;
	}

	bool remove(const HashedObj& x) {
		int currentPos = findPos(x);
		if (isActive(currentPos))
			return false;
		array[currentPos].info == DELETED;
		return true;
	}
};


int main(){
	HashTable<int> ht;
	ht.insert(1);
	ht.insert(99);
	return 0;
}