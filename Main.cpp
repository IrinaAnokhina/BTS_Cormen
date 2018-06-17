#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include"Tree.h"
#include"vld.h"
int main()
{
	Tree<int>intTree;
	int intValue;
	size_t treeSize{};
	cout << "Enter the size of tree:\n";
	cin >> treeSize;
	cout << "\nEnter integer values:\n";

	for (int i = 0; i < treeSize; ++i)
	{
		cin >> intValue;
		intTree.insertNode(intValue);
	}
	cout << "\nPreorder traversal:\n";
	intTree.preOrderTraversal();

	cout << "\nInorder traversal:\n";
	intTree.inOrderTraversal();

	cout << "\nPostorder traversal:\n";
	intTree.postOrderTraversal();
	int value;
	cout << "\nMin of tree is: " << intTree.treeMin();
	cout << "\nMax of tree is: " << intTree.treeMax();
	
	cout << "\nEnter value, which successor you want to know: ";
	cin >> value;
	cout << "\nThe successor of value " << value << " is " << intTree.treeSuccessor(intTree.search(value));
	cout << "\nEnter value, which predeccessor you want to know: ";
	cin >> value;
	cout << "\nThe predeccessor of value " << value << " is " << intTree.treePredeccessor(intTree.search(value));
	cout << "\nWhat element you want to delete?";
	cin >> value;
	intTree.nodeDelete(intTree.search(value));
	cout << "\nPreorder traversal:\n";
	intTree.preOrderTraversal();

	cout << "\nInorder traversal:\n";
	intTree.inOrderTraversal();

	cout << "\nPostorder traversal:\n";
	intTree.postOrderTraversal();
}