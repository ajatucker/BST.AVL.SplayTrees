#pragma once
#ifndef BST
#define BST
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class bst
{
private:
	struct treeNode
	{
		int key;
		treeNode* right;
		treeNode* left;
		treeNode* twin;
		int numOfTwin;
	};

	treeNode* root;
	int countSearch;
	int countDelete;
	int countInsert;

	void insert(treeNode*& p, int item);
	void print(treeNode* p, ofstream& f, int addSpaces);
	void search(treeNode* p, int item, bool& status);
	void del(treeNode*& p, int item);
	void deleteNode(treeNode*& p);
	void getPredecessor(treeNode* p, int& item);
	void destroy(treeNode*& p);
	int height(treeNode* p, int& h);

public:
	bst();
	void insertNode(int item);
	void printTree(ofstream& f);
	void searchNode(int item, bool& status);
	void deleteItem(int item);
	int findHeight();
	int getCountDeletes();
	int getCountInserts();
	int getCountSearches();
	~bst();
};

#endif

//constructor
bst::bst()
{
	root = NULL;
	countSearch = 0;
	countDelete = 0;
	countInsert = 0;
}

/*
Desc: getter for count deletes
Pre-condition : none
Post-condition : returns count delete
*/
int bst::getCountDeletes()
{
	return countDelete;
}

/*
Desc: getter for count inserts
Pre-condition : none
Post-condition : returns count inserts
*/
int bst::getCountInserts()
{
	return countInsert;
}

/*
Desc: getter for count searches
Pre-condition : none
Post-condition : returns count searches
*/
int bst::getCountSearches()
{
	return countSearch;
}

/*
Desc: insert node function that calls internal insert function
Pre-condition : integer
Post-condition : none
*/
void bst::insertNode(int item)
{
	insert(root, item);
	countInsert++;
}

/*
Desc: inserts a node at a leaf point
Pre-condition : treeNode pointer, integer
Post-condition : none
*/
void bst::insert(treeNode*& p, int item)
{
	if (p == NULL)
	{
		p = new treeNode;
		p->key = item;
		p->numOfTwin = 1;
		p->twin = NULL;
		p->right = NULL;
		p->left = NULL;
		return;
	}
	else if (item == p->key)
	{
		//p->twin = new treeNode;
		p->numOfTwin++;
		countInsert++;
		insert(p->twin, item);
		return;
	}
	else if (item < p->key)
	{
		countInsert++;
		insert(p->left, item);
	}
	else
	{
		countInsert++;
		insert(p->right, item);
	}
}

/*
Desc: search function that calls internal search function
Pre-condition : integer, boolean
Post-condition : none
*/
void bst::searchNode(int item, bool& status)
{
	search(root, item, status);
	countSearch++;
}

/*
Desc: searches for a node
Pre-condition : treeNode pointer, integer, boolean
Post-condition : none
*/
void bst::search(treeNode* p, int item, bool& status)
{
	if (p == NULL)
	{
		status = false;
	}
	else if (item < p->key)
	{
		countSearch++;
		search(p->left, item, status);
	}
	else if (item > p->key)
	{
		countSearch++;
		search(p->right, item, status);
	}
	else
	{
		item = p->key;
		status = true;
	}
}

/*
Desc: delete function that calls internal search for delete function
Pre-condition :integer
Post-condition : none
*/
void bst::deleteItem(int item)
{
	del(root, item);
	countDelete++;
}

/*
Desc: searches for where to delete
Pre-condition : treeNode pointer, integer
Post-condition : none
*/
void bst::del(treeNode*& p, int item)
{
	if (p == NULL)
	{
		//cout << item << " does not exist in the tree" << endl;
		return;
	}
	else if (item < p->key)
	{
		countDelete++;
		del(p->left, item);
	}
	else if (item > p->key)
	{
		countDelete++;
		del(p->right, item);
	}
	else if (item == p->key && p->numOfTwin > 1)
	{
		p->numOfTwin--;
		//treeNode* prev = p;
		//treeNode* temp = p->twin;
		//while (temp != NULL)
		//{
		//	prev = temp;
		//	temp = p->twin;
		//}
		//prev->twin = temp->twin;
		//delete temp;
	}
	else
	{
		deleteNode(p);
		//return;
	}

}

/*
Desc: deletes the node
Pre-condition : treeNode pointer
Post-condition : none
*/
void bst::deleteNode(treeNode*& p)
{
	int item;
	treeNode* temp;

	temp = p;

	//if (p->twin !=  NULL)
	//{
	//	p->numOfTwin--;
		//while (p->twin != NULL)
		//{
		//	temp = p->twin;
		//}
		//delete temp;
	//}

	if (p->left == NULL)
	{
		p = p->right;
		delete temp;
	}
	else if (p->right == NULL)
	{
		p = p->left;
		delete temp;
	}
	else
	{
		treeNode* temp = p;
		getPredecessor(temp, item); // p->right
		p->key = temp->key;
		p->twin = temp->twin;
		del(p->right, item);
	}

	return;
	//temp = NULL;
}

/*
Desc: finds the smallest in the tree given
Pre-condition : treeNode pointer, integer
Post-condition : none
*/
void bst::getPredecessor(treeNode* p, int& item)
{
	while (p != NULL && p->left != NULL)
	{
		countDelete++;
		p = p->left;
		//item = p->key;
	}
	item = p->key;
}

/*
Desc: calls internal print function
Pre-condition :ofstream
Post-condition : none
*/
void bst::printTree(ofstream& f)
{
	cout << "---------------------------------------------------------------" << endl;
	f << "---------------------------------------------------------------" << endl;
	print(root, f, 0);
	f << "---------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------" << endl;
}

/*
Desc: prints
Pre-condition :treeNode pointer, ofstream, integer
Post-condition : none
*/
void bst::print(treeNode* p, ofstream& f, int addSpaces)
{
	if (root != NULL)
	{

		if (p->right != NULL)
		{
			print(p->right, f, addSpaces + 7);
		}

		for (int i = 0; i < addSpaces; i++)
		{
			f << " ";
			cout << " ";
		}
		if (p->twin != NULL && p->numOfTwin > 1)
		{
			f << p->key << "(" << p->numOfTwin << ")" << endl;
			cout << p->key << "(" << p->numOfTwin << ")" << endl;
		}
		else
		{
			f << p->key << endl;
			cout << p->key << endl;
		}

		if (p->left != NULL)
		{
			print(p->left, f, addSpaces + 7);
		}

	}
}

/*
Desc: calls internal height function to find the height of the tree
Pre-condition :none
Post-condition :integer
*/
int bst::findHeight()
{
	int ht = 0;
	height(root, ht);
	return (ht - 1);
}

/*
Desc: finds the height of the tree given
Pre-condition :treeNode pointer, integer
Post-condition : integer
*/
int bst::height(treeNode* p, int& h)
{
	if (p == NULL)
	{
		return 0;
	}

	h = max(height(p->left, h), height(p->right, h)) + 1;

	return h;
}

/*
Desc: destroys the tree
Pre-condition :treeNode pointer
Post-condition : none
*/
void bst::destroy(treeNode*& p)
{
	if (p != NULL)
	{
		destroy(p->left);
		destroy(p->right);
		p = p->twin;
		delete p;
	}
}

//destructor
bst::~bst()
{
	destroy(root);
	root = NULL;
}