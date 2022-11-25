#include "AVLTreeTemplate.h"

/**
 * @brief �ҵ���node�ڵ�Ϊ���ڵ�������У����һ�����ֵĽڵ㣬ʵ���Ͼ���avl��������������õ��������е����һ��ֵ�Ľڵ�
 * @param node �����ĸ��ڵ�
 * @return ��������һ���ڵ�
*/
template<class T>
Node<T>* AVLTreeTemplate<T>::subTreeLast(Node<T>* node)
{
	Node<T>* p = node;
	while (p->right)
	{
		p = p->right;
	}
	return p;
}

/**
 * @brief AVL���Ĺ��캯����ͨ��һ����С������������飬����һ��AVL��
 * @param vec ��С�������������
*/
template<class T>
AVLTreeTemplate<T>::AVLTreeTemplate(vector<T>& vec)
{
	if (!vec.empty())
	{
		root = build(vec, 0, vec.size() - 1, nullptr);
	}
}

/**
 * @brief AVL�����캯�����������õĽ���������ͨ������Ĵ�С������������齨AVL��
 * @param vec ��С�������������
 * @param left �ֶ�����������±꣬������int
 * @param right �ֶ�����������±꣬������int
 * @param parent �����������½ڵ�ĸ��ڵ�
 * @return �������ɹ������ظ�AVL���ĸ��ڵ�root�����򷵻�nullptr
*/
template<class T>
Node<T>* AVLTreeTemplate<T>::build(vector<T>& vec, int left, int right, Node<T>* parent)
{
	if (left > right) return nullptr;
	int mid = left + (right - left) / 2;
	Node<T>* node = new Node<T>(vec[mid], parent);
	node->left = build(vec, left, mid - 1, node);
	node->right = build(vec, mid + 1, right, node);
	if (node) calculate(node);
	return node;
}

/**
 * @brief Ѱ�ҵ�k��С��ֵ��������������ۣ�
 *				1. ��ǰ�ڵ�����������ܽڵ���С��k-1��˵����k��С��ֵһ�������ڵ�ǰ�ڵ������������Ϊ��ǰ�ڵ�����������ܽڵ���+��ǰ�ڵ�<=k-1��ת�Ƶ���������ʱ��Ҫ���ȥ1����ΪҪ�ѵ�ǰ�ڵ�Ҳ��ȥ
 *				2. ��ǰ�ڵ���������ܽڵ�������k-1��˵����ǰ�ڵ����Ҫ�ҵĵ�k��С��ֵ��
 *				3. ��ǰ�ڵ���������ܽڵ�������k-1��˵����k��С��ֵ���ڵ�ǰ�ڵ���������С�
 * @param k Ҫ�ҵĵ�k��С������1 <= k <= n��n��ʾAVL���Ľڵ���
 * @return �ҵ��������������λ�õ�ֵ�����򷵻�-1
*/
template<class T>
T AVLTreeTemplate<T>::avlSearch(T k)
{
	Node<T>* node = root;
	while (node)
	{
		int leftNum = getSize(node->left);
		if (leftNum < k - 1)
		{
			node = node->right;
			k -= leftNum + 1;
		}
		else if (leftNum == k - 1)//�ҵ��ˣ���ǰ�ڵ���ǵ�k��С����
		{
			break;
		}
		else
		{
			node = node->left;
		}
	}
	return node ? node->val : -1;//�Ҳ����ͷ���-1
}

/**
 * @brief ��AVL���в���һ���ڵ㣬����������㣬�����Ȱ�ֵΪv�Ľڵ���뵽������
 * @param v ������ڵ��ֵ
*/
template<class T>
void AVLTreeTemplate<T>::avlInsert(T v)
{
	if (!root)
	{
		root = new Node<T>(v);
	}
	else
	{
		Node<T>* node = searchSubTree(root, v);
		bool isAddLeft = (node->val >= v);
		if (node->val == v)
		{
			if (node->left)
			{
				node = subTreeLast(node->left);
				isAddLeft = false;
			}
			else
			{
				isAddLeft = true;
			}
		}

		//����½ڵ�
		Node<T>* leaf = new Node<T>(v, node);
		if (isAddLeft)
		{
			node->left = leaf;
		}
		else
		{
			node->right = leaf;
		}
		rebalance(leaf);
	}
}

/**
 * @brief ɾ��1��ֵΪv�Ľڵ㣬�����vֵ�Ľڵ���ڶ������ֻ��ɾ������һ��
 * @param v Ҫɾ���Ľڵ��ֵ
 * @return ɾ���ɹ�����true�����򷵻�false
*/
template<class T>
bool AVLTreeTemplate<T>::avlDeleteForOne(T v)
{
	if (!root)
	{
		return false;
	}

	Node<T>* node = searchSubTree(root, v);
	if (node->val != v)
	{
		return false;
	}

	if (node->left && node->right)
	{
		Node<T>* replacement = nullptr;
		if (node->left->height >= node->right->height)
		{
			replacement = subTreeLast(node->left);
		}
		else
		{
			replacement = subTreeFirst(node->right);
		}
		node->val = replacement->val;
		node = replacement;
	}

	Node<T>* parent = node->parent;
	avlDelete(node);
	rebalance(parent);
	return true;

}

/**
 * @brief ɾ�������ظ��Ľڵ㣬������ֻɾ��һ��
 * @param v ��ɾ���Ľڵ��ֵ
 * @return ���ɾ���ɹ�������true�����һ��ʼ��û����ɾ������ô�ͷ���false
*/
template<class T>
bool AVLTreeTemplate<T>::avlDeleteForAll(T v)
{
	if (!root)
	{
		return false;
	}

	bool flag = false;
	while (Node<T>* node = searchSubTree(root, v))
	{
		if (node->val != v)
		{
			if (flag)
			{
				break;
			}
			else
			{
				return false;
			}

		}

		flag = true;	//˵���ҵ���ֵΪv�Ľڵ㣬ֻҪ�ҵ�һ�Σ���˵��ɾ�������ɹ����С���ɾ����ֵΪv�Ľڵ�֮����ô��Ҫֱ������whileѭ��

		if (node->left && node->right)
		{
			Node<T>* replacement = nullptr;
			if (node->left->height >= node->right->height)
			{
				replacement = subTreeLast(node->left);
			}
			else
			{
				replacement = subTreeFirst(node->right);
			}
			node->val = replacement->val;
			node = replacement;
		}

		Node<T>* parent = node->parent;
		avlDelete(node);
		rebalance(parent);
	}
	return true;
}

#include<stack>
#include<vector>
/**
 * @brief �õ�AVL����������µĴ�С���������
 * @return ���ظ�����
*/
template<class T>
vector<T> AVLTreeTemplate<T>::getInOrderNums()
{
	vector<T> res;
	stack<Node<T>*> st;
	st.push(root);
	while (!st.empty())
	{
		Node<T>* node = st.top();
		if (node)
		{
			st.pop();
			if (node->right) st.push(node->right);
			st.push(node);
			st.push(nullptr);
			if (node->left) st.push(node->left);
		}
		else
		{
			st.pop();
			node = st.top();
			st.pop();
			res.push_back(node->val);
		}
	}
	return res;
}

/**
 * @brief �Խڵ������ת�������������������������������������������ת�ı����Ǹı�ĳ�ڵ������ָ���ָ�����һ���ڵ㸸ָ���ָ��
 * @param node ������ת�����Ľڵ�
*/
template<class T>
void AVLTreeTemplate<T>::rotate(Node<T>* node)
{
	Node<T>* parent = node->parent;
	Node<T>* grandParent = parent->parent;
	if (!grandParent)	 //��ƽ��Ľڵ���root������Ѱ��root���������и߶Ƚϸߵ�������������Ϊ�µ�root
	{
		root = node;
		node->parent = nullptr;
	}
	else	//��ƽ��Ľڵ㲻��root
	{
		relink(grandParent, node, parent == grandParent->left);
	}

	if (node == parent->left)	//���node��parent�����
	{
		relink(parent, node->right, true);
		relink(node, parent, false);
	}
	else	//���node��parent���ұ�
	{
		relink(parent, node->left, false);
		relink(node, parent, true);
	}
}

/**
 * @brief AVL����ĳ�ڵ�ɾ�������������һ��private��������粻��ֱ�ӵ��ã������ʹ�õ�ֻ����һ�����غ���avlDelete(int v)
 * @param node Ҫɾ���Ľڵ�
*/
template<class T>
void AVLTreeTemplate<T>::avlDelete(Node<T>* node)
{
	//������һ���delete����֮�󣬰�����˵Ҫɾ���Ľڵ㲻���������Һ��ӣ������������ֱ�ӷ���
	if (node->left && node->right)
	{
		return;
	}

	Node<T>* child = node->left ? node->left : node->right;

	if (child)
	{
		child->parent = node->parent;
	}

	if (node == root)
	{
		root = child;
	}
	else
	{
		Node<T>* parent = node->parent;
		if (parent->left == node)	//nodeλ�ڸ��ڵ�����
		{
			parent->left = child;
		}
		else		//nodeλ�ڸ��ڵ���ұ�
		{
			parent->right = child;
		}
	}
	node->parent = node;
	delete node;
}

/**
 * @brief ����ýڵ�ĸ�height��size��height��ʾ�����нڵ�ĸ߶ȣ��������������нϸ������ĸ߶ȼ���������
 *				size��ʾ�����иýڵ������������size֮�ͼ���������
 * @param node Ҫ����height��size����Ľڵ�
*/
template<class T>
void AVLTreeTemplate<T>::calculate(Node<T>* node)
{
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	node->size = getSize(node->left) + getSize(node->right) + 1;
}

/**
 * @brief ƽ��AVL��
 *				ÿ�β��룬ƽ��ļ��㶼��Ӳ���ڵ㿪ʼ�����ϼ��ڵ�����������Ƿ�ƽ�⣻
 *				ÿ��ɾ������ɾ���ڵ����������������ڵ���н���֮�󣬴ӱ�ɾ���Ľڵ�ĸ���㿪ʼ����ƽ�⣻
 * @param node ���ƽ�����ʼ�ڵ�
*/
template<class T>
void AVLTreeTemplate<T>::rebalance(Node<T>* node)
{
	while (node)
	{
		T oldHeight = node->height;
		T oldSize = node->size;
		if (!isBalance(node))
		{
			node = restructure(childchildHeight(node));
			calculate(node->left);
			calculate(node->right);
		}
		calculate(node);
		if (node->height == oldHeight && node->size == oldSize)
		{
			node = nullptr;
		}
		else
		{
			node = node->parent;
		}
	}
}

/**
 * @brief �жϽڵ�����������Ƿ�ƽ�⣬ƽ������������������ĸ߶�֮��ľ���ֵС�ڵ���1
 * @param node �����ƽ��Ľڵ�
 * @return ����ڵ���������ƽ�⣬����true�����򷵻�false
*/
template<class T>
bool AVLTreeTemplate<T>::isBalance(Node<T>* node)
{
	return abs(getHeight(node->left) - getHeight(node->right)) <= 1;
}

/**
 * @brief �õ�node�ڵ��size
 * @param node AVL���е�ĳ���ڵ�
 * @return �ýڵ��size
*/
template<class T>
int AVLTreeTemplate<T>::getSize(Node<T>* node)
{
	return node != nullptr ? node->size : 0;
}

/**
 * @brief �õ�node�ڵ��height
 * @param node AVl���е�ĳ���ڵ�
 * @return �ýڵ��height
*/
template<class T>
int AVLTreeTemplate<T>::getHeight(Node<T>* node)
{
	return node != nullptr ? node->height : 0;
}

/**
 * @brief �õ�node�ڵ�����������нϸ������ĸ��ڵ�
 * @param node AVL���е�ĳ���ڵ�
 * @return node�ڵ�����������нϸ������ĸ��ڵ�
*/
template<class T>
Node<T>* AVLTreeTemplate<T>::childHeight(Node<T>* node)
{
	return (getHeight(node->left) > getHeight(node->right)) ? node->left : node->right;
}

/**
 * @brief �õ�node�ڵ�����������нϸ������ĸ��ڵ��е����������нϸ������ĸ��ڵ�
 * @param node AVL����ĳ���ڵ�
 * @return node�ڵ�����������нϸ������ĸ��ڵ��е����������нϸ������ĸ��ڵ㡣���childHeight�ȣ��õ���������һ��ĸ��ڵ�
*/
template<class T>
Node<T>* AVLTreeTemplate<T>::childchildHeight(Node<T>* node)
{
	Node<T>* child = childHeight(node);
	return childHeight(child);
}

/**
 * @brief ����AVL����ֵΪv�Ľڵ�
 * @param node ֵΪv�Ľڵ�
 * @param v Ҫ������ֵ
 * @return ����ɹ��ҵ�ֵΪv�Ľڵ㣬�򷵻ظýڵ㣻���򷵻�Ҫ���ҵ�ֵ���뵽AVL���ĸ��ڵ�
*/
template<class T>
Node<T>* AVLTreeTemplate<T>::searchSubTree(Node<T>* node, T v)
{
	if (node->val < v && node->right)
	{
		return searchSubTree(node->right, v);
	}
	else if (node->val > v && node->left)
	{
		return searchSubTree(node->left, v);
	}
	else
	{
		return node;
	}
}

/**
 * @brief ���ĳ�ڵ㲻ƽ���ˣ��ͻᴥ�����������Ҫ��node�ڵ����������ת���������Ƕ�node�ڵ�ĸ��ڵ����һ����ת����
 *				LL�������ָgrandparent�ڵ��������parent�ڵ㣬parent�ڵ��������node�ڵ�
 *				RR�������ָgrandparent�ڵ���Һ�����parent�ڵ㣬parent�ڵ���Һ�����node�ڵ�
 *				LR�������ָgrandparent�ڵ��������parent�ڵ㣬parent�ڵ���Һ�����node�ڵ�
 *				RL�������ָgrandparent�ڵ���Һ�����parent�ڵ㣬parent�ڵ��������node�ڵ�
 * @param node
 * @return
*/
template<class T>
Node<T>* AVLTreeTemplate<T>::restructure(Node<T>* node)
{
	Node<T>* parent = node->parent;
	Node<T>* grandParent = parent->parent;
	if ((node == parent->left) == (parent == grandParent->left))	//�����LL��RR�������ֻ��Ҫ��parent�ڵ���תһ��
	{
		rotate(parent);
		return parent;
	}
	else	//�����LR��RL���������Ҫ��node�ڵ���ת����
	{
		rotate(node);
		rotate(node);
		return node;
	}
}

/**
 * @brief ÿһ����תʵ�����Ǹı�parent�ڵ�������ָ���ָ���Լ�child�ڵ�ĸ�ָ���ָ��
 * @param parent Ҫ�ı�����ָ���ָ��Ľڵ�
 * @param child Ҫ�ı丸ָ���ָ��Ľڵ�
 * @param existLeft parent�ڵ������Ƿ���ڣ����������parent�ڵ���ָ���ָ���Ϊnode�ڵ㣬�����������parent�ڵ���ָ���ָ���Ϊnode�ڵ�
*/
template<class T>
void AVLTreeTemplate<T>::relink(Node<T>* parent, Node<T>* child, bool existLeft)
{
	if (existLeft)
	{
		parent->left = child;
	}
	else
	{
		parent->right = child;
	}
	if (child)
	{
		child->parent = parent;
	}
}

/**
 * @brief �õ���node�ڵ�Ϊ���ڵ�������У���һ�����ֵĽڵ㣬ʵ���Ͼ���avl��������������õ��������еĵ�һ��ֵ�Ľڵ�
 * @param node �����ĸ��ڵ�
 * @return ��node�ڵ�Ϊ���ڵ�������У���һ�����ֵĽڵ�
*/
template<class T>
Node<T>* AVLTreeTemplate<T>::subTreeFirst(Node<T>* node)
{
	while (node->left)
	{
		node = node->left;
	}
	return node;
}
