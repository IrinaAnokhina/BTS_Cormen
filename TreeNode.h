#pragma once
#include<iostream>
using std::ostream;
template<typename NODETYPE>class Tree;

template<typename NODETYPE>
class TreeNode
{
	friend class Tree < NODETYPE >;
public:
	TreeNode(const NODETYPE &d)
		:leftPtr(0), data(d), rightPtr(0), parentPtr(0)
	{}
	TreeNode(const TreeNode<NODETYPE>*);
	NODETYPE getData() const
	{
		return data;
	}
private:
	TreeNode<NODETYPE> *leftPtr;
	NODETYPE data;
	TreeNode<NODETYPE> *rightPtr;
	TreeNode<NODETYPE> *parentPtr;
	template<typename NODETYPE>
	friend ostream & operator<<(ostream & output, const TreeNode<NODETYPE>* node);
};

template<typename NODETYPE>
TreeNode<NODETYPE>::TreeNode(const TreeNode<NODETYPE> *ptr)
	:leftPtr(ptr->leftPtr), data(ptr->data), rightPtr(ptr->rightPtr), parentPtr(ptr->parentPtr)
{}

template<typename NODETYPE>
ostream& operator<<(ostream &output, const TreeNode<NODETYPE> *node)
{
	if (node != nullptr)
		output << node->getData();
	else
		output << "***nullptr***";
	return output;
}
