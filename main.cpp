#include<iostream>
#include "AVLTreeTemplate.h"	//һ�㺯��ֻ��Ҫ����ͷ�ļ��Ϳ���ʹ�ø�ͷ�ļ��а�������ͺ���
#include "AVLTreeTemplate.cpp"	//��������ģ��֮����Ҫ�Ѹ����cpp��ģ��ľ��嶨��ҲҪinclude��main������
#include<vector>				//��ҪΪ�˽����C++ error LNK2019: �޷��������ⲿ���š��������
using namespace std;

//����int���͵�AVL��
void testForAVLTreeTemplateWithInt()
{
	cout << "**********����int���͵�AVL��**********" << endl;
	//����AVL��
	vector<int> nums({ 1,2,3,4,5,6 });
	AVLTreeTemplate<int> oneTree(nums);
	vector<int> res = oneTree.getInOrderNums();
	cout << "�����AVL����";
	for (int i : res)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;

	//��AVL������ֵΪ3�Ľڵ�
	oneTree.avlInsert(3);
	cout << "����ֵΪ3�Ľڵ㣺";
	res = oneTree.getInOrderNums();
	for (int i : res)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;

	//ɾ��AVL��ֵΪ4�Ľڵ�
	oneTree.avlDeleteForOne(4);
	res = oneTree.getInOrderNums();
	cout << "ɾ��ֵΪ4�Ľڵ㣺";
	for (int i : res)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;

	//ɾ��AVL��ȫ�����ظ�ֵ����ֵΪ3�Ľڵ�
	oneTree.avlDeleteForAll(3);
	res = oneTree.getInOrderNums();
	cout << "ɾ��ֵΪ3�������ظ��ڵ㣺";
	for (int i : res)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
}

//����double���͵�AVL��
void testForAVLTreeTemplateWithDouble()
{
	cout << "**********����double���͵�AVL��**********" << endl;
	//����AVL��
	vector<double> nums({ 1.2, 3.4, 6.0, 8.9, 11.2, 15.6});
	AVLTreeTemplate<double> oneTree(nums);
	vector<double> res = oneTree.getInOrderNums();
	cout << "�����AVL����";
	for (double i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;

	//��AVL������ֵΪ8.9�Ľڵ�
	oneTree.avlInsert(8.9);
	cout << "����ֵΪ8.9�Ľڵ㣺";
	res = oneTree.getInOrderNums();
	for (double i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;

	//ɾ��AVL��ֵΪ3.4�Ľڵ�
	oneTree.avlDeleteForOne(3.4);
	res = oneTree.getInOrderNums();
	cout << "ɾ��ֵΪ3.4�Ľڵ㣺";
	for (double i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;

	//ɾ��AVL��ȫ�����ظ�ֵ����ֵΪ8.9�Ľڵ�
	oneTree.avlDeleteForAll(8.9);
	res = oneTree.getInOrderNums();
	cout << "ɾ��ֵΪ8.9�������ظ��ڵ㣺";
	for (double i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
}

//����char���͵�AVL��
//��ĸ�Ļ������ֵ����������Ҳ����˵ͨ��26����ĸ��˳�������������a��С��z���
void testForAVLTreeTemplateWithChar()
{
	cout << "**********����char���͵�AVL��**********" << endl;
	//����AVL��
	vector<char> nums({ 'a', 'b', 'c', 'd', 'e', 'f', 'g'});
	AVLTreeTemplate<char> oneTree(nums);
	vector<char> res = oneTree.getInOrderNums();
	cout << "�����AVL����";
	for (char i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;

	//��AVL������ֵΪc�Ľڵ�
	oneTree.avlInsert('c');
	cout << "����ֵΪc�Ľڵ㣺";
	res = oneTree.getInOrderNums();
	for (char i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;

	//ɾ��AVL��ֵΪd�Ľڵ�
	oneTree.avlDeleteForOne('d');
	res = oneTree.getInOrderNums();
	cout << "ɾ��ֵΪd�Ľڵ㣺";
	for (char i : res)
	{
		cout << i << "  ";
	}
	cout << endl;
	cout << endl;

	//ɾ��AVL��ȫ�����ظ�ֵ����ֵΪc�Ľڵ�
	oneTree.avlDeleteForAll('c');
	res = oneTree.getInOrderNums();
	cout << "ɾ��ֵΪc�������ظ��ڵ㣺";
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