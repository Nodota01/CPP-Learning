#include "pch.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <list>

using namespace std;

template<typename Comparable>
class BST {
private:
	//节点结构体
	struct BinaryNode {
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;
		int height;
		BinaryNode(const Comparable & ele, BinaryNode * l, BinaryNode *r, int h = 0) :element(ele), left(l), right(r), height(h){}
		BinaryNode(Comparable &&ele, BinaryNode *l, BinaryNode *r, int h = 0) : element(std::move(ele)), left(l), right(r), height(h){}
	};
	//私有成员为树根
	BinaryNode *root;

	//操作

	//返回节点的高度
	int height(BinaryNode *t) const {
		return t == nullptr ? -1 : t->height;
	}
	//每次插入完成后平衡节点并更新各节点高度
	void balance(BinaryNode *&t) {
		if (t == nullptr)
			return;
		//判断不平衡的四种情形
		if (height(t->left) - height(t->right) > 1)
			if (height(t->left->left) >= height(t->left->right))
				rotateLeft(t);
			else
				doubleLeft(t);
		else if(height(t->right) - height(t->left) > 1)
			if (height(t->right->right) >= height(t->right->left))
				rotateRight(t);
			else
				doubleRight(t);
		//更新节点高度
		t->height = max(height(t->left), height(t->right)) + 1;
	}
	//左单旋转
	void rotateLeft(BinaryNode *&k2) {
		BinaryNode * k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		//更新k1为新的根
		k2 = k1;
	}
	//右单旋转
	void rotateRight(BinaryNode *&k2) {
		BinaryNode *k1 = k2->right;
		k2->right = k1->left;
		k1->left = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), height(k2->right)) + 1;
		//更新k1为新的根
		k2 = k1;
	}
	/*
	*左双旋转
	*先对k3左儿子k1和k1的右儿子k2进行右单旋转
	*再对k3和左儿子k2进行左单旋转
	*/
	void doubleLeft(BinaryNode *&k3) {
		rotateRight(k3->left);
		rotateLeft(k3);
	}
	//右双旋转，即左双旋转反过来
	void doubleRight(BinaryNode *&k3) {
		rotateLeft(k3->right);
		rotateRight(k3);
	}



	void insert(const Comparable &x, BinaryNode *&t) {
		//为空树或插入时的基准情形
		if (t == nullptr)
			t = new BinaryNode(x, nullptr, nullptr);
		if (x < t->element)
			insert(x, t->left);
		else if (x > t->element)
			insert(x, t->right);
		balance(t);
	}
	void insert(Comparable && x, BinaryNode *& t) {
		if (t == nullptr)
			t = new Node(std::move(x), nullptr, nullptr);
		else if (x < t->element)
			insert(std::move(x), t->left);
		else if (x > t->element)
			insert(std::move(x), t->right);
		else
			;
	}
	void remove(Comparable &x, BinaryNode *& t) {
		if (t == nullptr)
			returnl;
		if (x < t->element)//先找到要删除的项
			remove(x, t->left);
		else if (x > t->element)
			remove(x, t->right);
		/*如有两个儿子，在右树找到最小项并替代它，再删除替代项
		*因右树最小项一定比左儿子大且比右儿子小
		*/
		else if (t->left != nullptr && t->right != nullptr) {
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		/*只有一个儿子或没有儿子的情形
		*如只有一个儿子则指向其儿子并释放自身
		*如没有儿子则为空指针并释放
		*/
		else {
			BinaryNode *oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}
		balance(t);
	}
	BinaryNode *findMax(BinaryNode *t) const {
		//确保不为空树
		if (t != nullptr)
			while (t->right != nullptr)//如果有右儿子则继续找
				t = t->right;
		return t;
	}
	BinaryNode *findMin(BinaryNode *t) const {
		//确保不为空树
		if (t == nullptr)
			return t;
		if (t->left == nullptr)
			return t;
		//如果有左儿子则继续找
		return findMin(t->left);
	}
	bool contains(const Comparable &x, BinaryNode *t) const {
		if (t == nullprt)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (x > t->element)
			return contains(x, t->right);
		else
			return true;//基准情形，如找到则返回真
	}
	void makeEmpty(BinaryNode *&t) {
		if (t != nullptr) {
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}
	void printTree(BinaryNode *t, int depth = 0) const {
		if (t == nullptr)
			return;
		for (int i = 0; i < depth; i++)
			cout << "	";
		cout << t->element << endl;
		printTree(t->left, depth + 1);
		printTree(t->right, depth + 1);
	}
	BinaryNode *clone(BinaryNode *t) const {
		if (t == nullptr)
			return nullptr;
		else
			return new BinaryNode(t->element, clone(e->left), clone(t->right));
	}
	int max(int a, int b) const {
		return a > b ? a : b;
	}

public:

	BST() {
		root = nullptr;
	}
	BST(const BST &rhs) {
		root = clone(rhs.root);
	}
	~BST() {
		makeEmpty(root);
	}

	const Comparable &findMax() const {
		return findMax(root)->element;
	}
	const Comparable &findMin() const {
		return findMin(root)->element;
	}
	bool contains(const Comparable &x) const {
		return contains(x, root);
	}
	bool isEmpty() const {
		if (root == nullptr)
			return true;
		else
			return false;
	}
	void printTree() const {
		printTree(root);
	}

	void makeEmpty() {
		makeEmpty(root);
	}
	void insert(const Comparable &x) {
		insert(x, root);
	}
	void insert(Comparable &&x) {
		insert(x, root);
	}
	void remove(const Comparable &x) {
		remove(x, root);
	}

	BST &operator=(const BST &rhs);
	BST &operator=(BST &&rhs);
};


int main()
{
	BST<int> tree;
	tree.insert(6);
	tree.insert(8);
	tree.insert(2);
	tree.insert(1);
	tree.insert(5);
	tree.insert(3);
	tree.insert(4);
	tree.printTree();
	return 0;
}