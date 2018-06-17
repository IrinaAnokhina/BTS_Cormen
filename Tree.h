#pragma once
#include<iostream>
using std::cout;
using std::endl;

#include"TreeNode.h"

template<typename NODETYPE>class Tree
{
public:
	Tree();
	~Tree();
	void insertNode(const NODETYPE &);
	void preOrderTraversal()const;
	void inOrderTraversal()const;
	void postOrderTraversal()const;
	TreeNode<NODETYPE>* search(const NODETYPE&);
	TreeNode<NODETYPE>* treeMin();
	TreeNode<NODETYPE>* treeMax();
	TreeNode<NODETYPE>* treeSuccessor(TreeNode<NODETYPE>*);
	TreeNode<NODETYPE>* treePredeccessor(TreeNode<NODETYPE>*);
	void nodeDelete(TreeNode<NODETYPE> *);

private:
	TreeNode<NODETYPE> *rootPtr;
	//service functions
	TreeNode<NODETYPE>* searchHelper(TreeNode<NODETYPE> *, const NODETYPE &);
	void insertNodeHelper(TreeNode<NODETYPE>**, TreeNode<NODETYPE>*, const NODETYPE&);
	void preOrderHelper(TreeNode<NODETYPE> *)const;
	void inOrderHelper(TreeNode<NODETYPE> *)const;
	void postOrderHelper(TreeNode<NODETYPE> *)const;
	TreeNode<NODETYPE>* TreeMin(TreeNode<NODETYPE> *);
	TreeNode<NODETYPE>* TreeMax(TreeNode<NODETYPE> *);
	void DestroyTree(TreeNode<NODETYPE> *ptr);
	TreeNode<NODETYPE> * transplant(TreeNode<NODETYPE> *, TreeNode<NODETYPE> *);
};

template<typename NODETYPE>
Tree<NODETYPE>::Tree()
{
	rootPtr = 0;
}

template<typename NODETYPE>
Tree<NODETYPE>::~Tree()
{
	DestroyTree(rootPtr);
}

template<typename NODETYPE>
void Tree<NODETYPE>::DestroyTree(TreeNode<NODETYPE> *ptr)
{
	if (ptr != 0)
	{
		DestroyTree(ptr->leftPtr);
		DestroyTree(ptr->rightPtr);
		delete ptr;
	}
}
template<typename NODETYPE>
void Tree<NODETYPE>::insertNode(const NODETYPE &value)
{
	insertNodeHelper(&rootPtr, nullptr, value);
}

template<typename NODETYPE>
void Tree<NODETYPE>::insertNodeHelper(TreeNode<NODETYPE>**ptr, TreeNode<NODETYPE> *parent, const NODETYPE &value)
{
	if (*ptr == 0)
	{
		*ptr = new TreeNode<NODETYPE>(value);
		(*ptr)->parentPtr = parent;
	}
	else
	{
		if (value < (*ptr)->data)
			insertNodeHelper(&((*ptr)->leftPtr), *ptr, value);
		else
		{
			if (value > (*ptr)->data)
				insertNodeHelper(&((*ptr)->rightPtr), *ptr, value);
			else
				cout << value << " dup" << endl;
		}
	}
}

template<typename NODETYPE>
void Tree<NODETYPE>::preOrderTraversal()const
{
	preOrderHelper(rootPtr);
}

template<typename NODETYPE>
void Tree<NODETYPE>::preOrderHelper(TreeNode<NODETYPE> *ptr)const
{
	if (ptr != 0)
	{
		cout << ptr->data << ' ';
		if (ptr->parentPtr != nullptr)
			cout << " ptr->parent = " << ptr->parentPtr;
		else
			cout << " ptr->parent = nullptr";
		if (ptr->leftPtr != nullptr)
			cout << " ptr->left = " << ptr->leftPtr->data;
		else
			cout << " ptr->left = nullptr";

			if (ptr->rightPtr != nullptr)
				cout << " ptr->right = " << ptr->rightPtr->data << "\n";
			else
				cout << " ptr->right = nullptr\n";
		preOrderHelper(ptr->leftPtr);
		preOrderHelper(ptr->rightPtr);
	}
}

template<typename NODETYPE>
void Tree<NODETYPE>::inOrderTraversal()const
{
	inOrderHelper(rootPtr);
}

template<typename NODETYPE>
void Tree<NODETYPE>::inOrderHelper(TreeNode<NODETYPE> *ptr)const
{
	if (ptr != 0)
	{
		inOrderHelper(ptr->leftPtr);
		cout << ptr->data << ' ';
		inOrderHelper(ptr->rightPtr);
	}
}

template<typename NODETYPE>
void Tree<NODETYPE>::postOrderTraversal()const
{
	postOrderHelper(rootPtr);
}

template<typename NODETYPE>
void Tree<NODETYPE>::postOrderHelper(TreeNode<NODETYPE> *ptr)const
{
	if (ptr != 0)
	{
		postOrderHelper(ptr->leftPtr);
		postOrderHelper(ptr->rightPtr);
		cout << ptr->data << ' ';
	}
}

template<typename NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::search(const NODETYPE &val)
{
	return searchHelper(rootPtr, val);
}

template<typename NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::searchHelper(TreeNode<NODETYPE> *ptr, const NODETYPE &val)
{
	if (ptr == 0)
		return 0;

	else if (val != ptr->data)
	{
		if (val < ptr->data)
			return searchHelper(ptr->leftPtr, val);
		else
			if (val > ptr->data)
				return searchHelper(ptr->rightPtr, val);
	}
	return ptr;
}

template<typename NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::treeMin()
{
	return TreeMin(rootPtr);
}

template<typename NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::TreeMin(TreeNode<NODETYPE>*ptr)
{
	if (ptr->leftPtr == 0)
		return ptr;
	else
		return TreeMin(ptr->leftPtr);
}

template<typename NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::treeMax()
{
	return TreeMax(rootPtr);
}

template<typename NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::TreeMax(TreeNode<NODETYPE>*ptr)
{
	if (ptr->rightPtr == 0)
		return ptr;
	else
		return TreeMax(ptr->rightPtr);
}

template<typename NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::treeSuccessor(TreeNode<NODETYPE> *ptr)
{
	if (ptr != 0)
	{
		if (ptr->rightPtr != 0)
			return TreeMin(ptr->rightPtr);
		TreeNode<NODETYPE>*y = ptr->parentPtr;
		while (y != 0 && ptr == y->rightPtr)
		{
			ptr = y;
			y = y->parentPtr;
		}
		return y;
	}
	else
		cout << "Value not found\n";
	return nullptr;
}

template<typename NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::treePredeccessor(TreeNode<NODETYPE> *ptr)
{
	if (ptr->leftPtr != 0)
		return TreeMax(ptr->leftPtr);
	TreeNode<NODETYPE>*y = ptr->parentPtr;
	while (y != 0 && ptr == y->leftPtr)
	{
		ptr = y;
		y = y->parentPtr;
	}
	return y;
}

template<typename NODETYPE>
TreeNode<NODETYPE> * Tree<NODETYPE>::transplant(TreeNode<NODETYPE> *ptr, TreeNode<NODETYPE> *newPtr)
{
	if (ptr->parentPtr == nullptr)
		rootPtr = newPtr;
	else if (ptr == ptr->parentPtr->leftPtr)
		ptr->parentPtr->leftPtr = newPtr;
	else
		ptr->parentPtr->rightPtr = newPtr;
	if (newPtr != nullptr)
		newPtr->parentPtr = ptr->parentPtr;
	return ptr;
}

template<typename NODETYPE>
void Tree<NODETYPE>::nodeDelete(TreeNode<NODETYPE> *ptr)
{
	if (ptr->leftPtr == nullptr && ptr->rightPtr == nullptr)
		transplant(ptr, nullptr);
	else if (ptr->leftPtr == nullptr)
		transplant(ptr, ptr->rightPtr);
	else if (ptr->rightPtr == nullptr)
		transplant(ptr, ptr->leftPtr);
	else
	{
		TreeNode<NODETYPE> *y = TreeMin(ptr->rightPtr);

		if (y->parentPtr != ptr)
		{
			y = transplant(y, y->rightPtr);
			y->rightPtr = ptr->rightPtr;
			y->rightPtr->parentPtr = y;
		}
		ptr = transplant(ptr, y);
		y->leftPtr = ptr->leftPtr;
		ptr->leftPtr->parentPtr = y;
	}
	delete ptr;
}



