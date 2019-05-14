#include "pch.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>

using namespace std;

template<typename Object>
class List {
public:
	//节点结构体，储存前一个节点的指针和后一个节点的指针，以及需要储存的数据
	struct Node {
		Object data;
		Node *next;
		Node *prev;
		Node(const Object &d = Object(), Node * p = nullptr, Node *n = nullptr):data(d), prev(p), next(n){}
		Node(Object &&d, Node *p = nullptr, Node *n = nullptr):data(move(d)), prev(p), next(n){}
	};
private:
	int theSize;
	Node *head;
	Node *tail;  
public:
	//迭代器类
	class iterator {
	protected:
		Node *current;
		//返回迭代器当前指向的节点的值
		Object &retrieve() {
			return current->data;
		}
		friend class List<Object>;
	public:
		iterator(Node *p = nullptr):current(p){}
		Object &operator*() {
			return retrieve();
		}
		iterator &operator++() {
			current = current->next;
			return *this;
		}

		iterator &operator++(int) {
			iterator old =  *this;
			++(*this);
			return old;
		}		
		iterator &operator--() {
			current = current->prev;
			return *this;
		}
		iterator &operator--(int) {
			iterator old = *this;
			--(*this);
			return old;
		}
		bool operator==(const iterator &a) {
			return current == a.current;
		}
		bool operator!= (const iterator &a) {
			return current != a.current;
		}
	};
public:
	//无参构造函数，制造空表
	List() {
		init();
	}
	//复制构造函数
	List(const List &lis) {
		for (auto &x : lis)
			push_back(x);
	}
	List &operator =(const List &lis) {
		List copy = lis;
		swap(copy, *this);
		return *this;
	}
	//析构函数，回收表头和表尾，并执行clear方法
	~List() {
		clear();
		delete head;
		delete tail;
	}
	//清空列表
	void clear() {
		while (!empty()) {
			pop_front();
		}
	}

	//返回是否为空表
	bool empty() {
		return size() == 0;
	}
	//返回表的大小
	int size() {
		return theSize;
	}
	Object &front() {
		return *begin();
	}
	Object &back() {
		return *--end();
	}
	void push_front(const Object &x) {
		insert(begin(), x);
	}
	void push_back(const Object &x) {
		insert(end(), x);
	}
	void pop_front() {
		erase(begin());
	}
	void pop_back() {
		erase(--end());
	}
	//制造空表的表头和表尾
	void init() {
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}

	//获取开头和结尾的迭代器
	iterator begin() {
		return iterator(head->next);
	}
	iterator end() {
		return iterator(tail);
	}

	//插入，返回新节点的迭代器
	iterator insert(iterator it, const Object&x) {
		Node *p = it.current;
		Node *node = new Node(x, p->prev, p);
		p->prev->next = node;
		p->prev = node;
		theSize++;
		return iterator(node);
	}
	iterator insert(iterator it, Object &&x) {
		Node *p = it.current;
		Node *node = new Node(move(x), p->prev, p);
		p->prev->next = node;
		node->next = p;
		theSize++;
		return iterator(node);
	}
	//清除，返回清除节点的下一个节点的迭代器
	iterator erase(iterator it) {
		Node *p = it.current;
		iterator reit(p->next);
		p->prev->next = p->next;
		p->next->prev = p->prev;
		theSize--;
		delete p;
		return reit;
	}
	iterator erase(iterator from, iterator to) {
		while (from != to)
			from = erase(from);
		return to;
	}
};

int main() {
	List<int> myList;
	for(int i = 0; i < 10; i++)
		myList.push_back(i);
	for (auto it = myList.begin(); it != myList.end(); ++it)
		cout << *it << endl;
	return 0;
}