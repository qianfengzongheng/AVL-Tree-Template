#include<iostream>
#include "AVLTreeTemplate.h"	//一般函数只需要引入头文件就可以使用该头文件中包含的类和函数
#include "AVLTreeTemplate.cpp"	//但是引入模板之后，需要把该类的cpp即模板的具体定义也要include进main函数中
#include<vector>				//主要为了解决“C++ error LNK2019: 无法解析的外部符号”这个问题
using namespace std;

//测试int类型的AVL树
void testForAVLTreeTemplateWithInt()
{
	cout << "**********测试int类型的AVL树**********" << endl;
	//构造AVL树
	vector<int> nums({ 1,2,3,4,5,6 });
	AVLTreeTemplate<int> oneTree(nums);
	vector<int> res = oneTree.getInOrderNums();
	cout << "构造的AVL树：";
	for (int i : res)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;

	//往AVL树插入值为3的节点
	oneTree.avlInsert(3);
	cout << "插入值为3的节点：";
	res = oneTree.getInOrderNums();
	for (int i : res)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;

	//删除AVL树值为4的节点
	oneTree.avlDeleteForOne(4);
	res = oneTree.getInOrderNums();
	cout << "删除值为4的节点：";
	for (int i : res)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;

	//删除AVL树全部的重复值——值为3的节点
	oneTree.avlDeleteForAll(3);
	res = oneTree.getInOrderNums();
	cout << "删除值为3的所有重复节点：";
	for (int i : res)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
}

//测试double类型的AVL树
void testForAVLTreeTemplateWithDouble()
{
	cout << "**********测试double类型的AVL树**********" << endl;
	//构造AVL树
	vector<double> nums({ 1.2, 3.4, 6.0, 8.9, 11.2, 15.6});
	AVLTreeTemplate<double> oneTree(nums);
	vector<double> res = oneTree.getInOrderNums();
	cout << "构造的AVL树：";
	for (double i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;

	//往AVL树插入值为8.9的节点
	oneTree.avlInsert(8.9);
	cout << "插入值为8.9的节点：";
	res = oneTree.getInOrderNums();
	for (double i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;

	//删除AVL树值为3.4的节点
	oneTree.avlDeleteForOne(3.4);
	res = oneTree.getInOrderNums();
	cout << "删除值为3.4的节点：";
	for (double i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;

	//删除AVL树全部的重复值——值为8.9的节点
	oneTree.avlDeleteForAll(8.9);
	res = oneTree.getInOrderNums();
	cout << "删除值为8.9的所有重复节点：";
	for (double i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
}

//测试char类型的AVL树
//字母的话是以字典序进行排序，也就是说通过26个字母的顺序进行排序，其中a最小，z最大
void testForAVLTreeTemplateWithChar()
{
	cout << "**********测试char类型的AVL树**********" << endl;
	//构造AVL树
	vector<char> nums({ 'a', 'b', 'c', 'd', 'e', 'f', 'g'});
	AVLTreeTemplate<char> oneTree(nums);
	vector<char> res = oneTree.getInOrderNums();
	cout << "构造的AVL树：";
	for (char i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;

	//往AVL树插入值为c的节点
	oneTree.avlInsert('c');
	cout << "插入值为c的节点：";
	res = oneTree.getInOrderNums();
	for (char i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;

	//删除AVL树值为d的节点
	oneTree.avlDeleteForOne('d');
	res = oneTree.getInOrderNums();
	cout << "删除值为d的节点：";
	for (char i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;

	//删除AVL树全部的重复值——值为c的节点
	oneTree.avlDeleteForAll('c');
	res = oneTree.getInOrderNums();
	cout << "删除值为c的所有重复节点：";
	for (char i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
}


int main()
{
	testForAVLTreeTemplateWithInt();
	testForAVLTreeTemplateWithDouble();
	testForAVLTreeTemplateWithChar();
	return 0;
}