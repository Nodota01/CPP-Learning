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


template<>
class hash<string> {
public:
	size_t operator()(const string& key) {
		size_t hashVal = 0;
		for (auto x : key)
			hashVal = 37 * hashVal + x;
		return hashVal;
	}
};


template<typename HashedObj>
class HashTable{
private:
	vector<list<HashedObj>> theLists;
	int currentSize;

	//如平均期望长度大于1则调用rehash
	void rehash() {
		vector<list<HashedObj>> oldLists = theLists;
		//创建两倍大的空表
		theLists.resize(nextPrime(2 * theLists.size()));
		for (auto& theList : theLists)
			theList.clear;
		//复制整个表
		currentSize = 0;
		for (auto& theList : oldLists)
			for (auto& x : theList)
				insert(std::move(x)); 
	}


	//获取散列序列
	size_t myhash(const HashedObj& x) const {
		static hash<HashedObj> hf;
		return hf(x) % theLists.size();
	}
public:
	HashTable(int size = 101) :currentSize(size) {
		theLists.resize(size, list<HashedObj>{});
	}
	void makeEmpty() {
		for (auto &theList : theLists)
			theList.clear();
	}

	bool contains(const HashedObj& x) const {
		auto &whichList = theLists[myhash(x)];
		//寻找该值的迭代器，如未找到则find()会返回尾部的迭代器
		auto itr = find(whichList.begin(), whichList.end(), x);
		return itr != whichList.end();
	}

	bool remove(const HashedObj& x) {
		auto& whichList = theLists[myhash(x)];
		auto itr = find(whichList.begin(), which.end(), x);
		//如果未找到需要移除的值则返回false
		if (itr == whichList.end())
			return false;
		whichList.erase(itr);
		--currentSize;
		return true;
	}

	bool insert(const HashedObj& x) {
		auto& whichList = theLists[myhash(x)];
		//如在插入前已经存在则返回false
		if (contains(x))
			return false;
		whichList.push_back(x);
		/*
		if(++currentSize > theLists.size())
			rehash();
		*/
		return true;
	}
};



int main() {
	HashTable<string> h;
	h.insert("132");
	return 0;
}

