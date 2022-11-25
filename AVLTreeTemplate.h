#pragma once
#ifndef _AVLTREETEMPLATE_H
#define _AVLTREETEMPLATE_H

template<class T>
struct Node
{
	T val;			//节点的值
	int size;			//节点本身和该节点所有孩子节点总和
	int height;			//路径所经过的边数总和
	Node* left;			//左孩子指针
	Node* right;		//右孩子指针
	Node* parent;		//父节点指针

	Node() : val(0), size(0), height(0), left(nullptr), right(nullptr), parent(nullptr) {}
	Node(T a) : val(a), size(1), height(0), left(nullptr), right(nullptr), parent(nullptr) {}
	Node(T a, Node* p) : val(a), size(1), height(0), left(nullptr), right(nullptr), parent(p) {}
	Node(T a, Node* p, Node* l, Node* r) : val(a), size(1), height(0), left(l), right(r), parent(p) {}
};

#include<vector>
using namespace std;
template<class T>
class AVLTreeTemplate
{
private:
	Node<T>* root;

	void rotate(Node<T>* node);
	void avlDelete(Node<T>* node);
	void calculate(Node<T>* node);
	void rebalance(Node<T>* node);
	bool isBalance(Node<T>* node);
	int getSize(Node<T>* node);		//返回节点的size，size一定是int型
	int getHeight(Node<T>* node);	//返回节点的height，height一定是int型
	Node<T>* childHeight(Node<T>* node);
	Node<T>* childchildHeight(Node<T>* node);
	Node<T>* searchSubTree(Node<T>* node, T v);
	Node<T>* restructure(Node<T>* node);
	static void relink(Node<T>* parent, Node<T>* child, bool existLeft);
	static Node<T>* subTreeFirst(Node<T>* node);
	static Node<T>* subTreeLast(Node<T>* node);


public:
	AVLTreeTemplate() : root(nullptr) {}
	AVLTreeTemplate(vector<T>& vec);

	Node<T>* build(vector<T>& vec, int left, int right, Node<T>* parent);
	T avlSearch(T k);
	void avlInsert(T v);
	bool avlDeleteForOne(T v);
	bool avlDeleteForAll(T v);
	vector<T> getInOrderNums();
};

#endif