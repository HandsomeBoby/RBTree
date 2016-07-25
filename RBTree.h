#pragma once

#include <iostream>

using namespace std;

enum color
{
	RED,
	BLACK
};

template <typename K,typename V>

struct RBTreeNode
{
	K _key;
	V _value;

	RBTreeNode<K, V> * _left;
	RBTreeNode<K, V> * _right;
	RBTreeNode<K, V> * _parent;

	color _col;//节点的颜色

	RBTreeNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_col(RED)
	{}
};

template <typename K, typename V>

class RBTree
{
	typedef RBTreeNode<K,V> Node;

public:
	RBTree()
		:_root(NULL)
	{}
	//插入
	bool Insert(const K& key,const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return true;
		}
		Node * cur = _root;
		Node * parent = NULL;
		//先找到对应的位置
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			//有相同的key值
			else
			{
				return false;
			}
		}
		//插入对应的位置
		cur = new Node(key, value);
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		//调整节点的颜色以及树的形状
		while (cur != _root&&parent->_col == RED)
		{
			Node * grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node * uncle = grandfather->_right;
				//第一种情况
				if (uncle != NULL&&uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//第三种情况
					if (cur == parent->_right)
					{
						_RotateL(parent);
						swap(parent, cur);
					}
					//第二种情况（包括有第三种情况转化来的）
					_RotateR(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
					break;
				}
			}
			//parent == grandfather -> _right
			else
			{
				Node * uncle = grandfather->_left;
				//第一种情况
				if (uncle != NULL&&uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//第三种情况
					if (cur == parent->_left)
					{
						_RotateR(parent);
						swap(parent, cur);
					}
					//第二种情况
					_RotateL(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}
	//查找
	Node * Find(const K & key)
	{
		if (_root == NULL)
		{
			return NULL;
		}
		Node * cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return NULL;
	}
	//中序遍历
	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

	bool IsRBTree()
	{
		if (_root == NULL)
		{
			return true;
		}
		if (_root->_col == RED)
		{
			return false;
		}
		int k = 0;
		Node * cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				k++;
			}
			cur = cur->_left;
		}
		int count = 0;
		return _IsRBTree(_root, k, count);
	}

protected:

	//左旋
	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
				subR->_parent = ppNode;
			}
			else
			{
				ppNode->_right = subR;
				subR->_parent = ppNode;
			}
		}
	}

	//右旋
	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;

		if (subLR)
		{
			subLR->_parent = parent;
		}

		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}

		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
				subL->_parent = ppNode;
			}
			else
			{
				ppNode->_right = subL;
				subL->_parent = ppNode;
			}
		}
	}

	void _Inorder(Node * root)
	{
		if (root == NULL)
		{
			return;
		}
		_Inorder(root->_left);
		cout << root->_key << "->";
		_Inorder(root->_right);
	}

	bool _IsRBTree(Node * root, const int k, int count)
	{
		if (root == NULL)
		{
			return true;
		}
		//第三条规则：没有连续的红节点
		if (root->_col == RED&&root->_parent->_col == RED)
		{
			cout << "连续的红节点" << root->_key << endl;
			return false;
		}
		if (root->_col == BLACK)
		{
			count++;
		}
		if (root->_left == NULL&&root->_right == NULL&&count != k)
		{
			cout << "黑色节点个数不相等" << root->_key << endl;
			return false;
		}
		return _IsRBTree(root->_left, k, count) && _IsRBTree(root->_right, k, count);
	}

private:
	Node * _root;
};
