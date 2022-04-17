#pragma once
#ifndef AVL
#define AVL
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "printer.h"

using namespace std;

class avl
{
private:
	struct treeNode
	{
		int key;
		treeNode* right;
		treeNode* left;
		treeNode* twin;
		int numOfTwin;
		int height;
	};

	treeNode* root;

	int countSearch;
	int countDelete;
	int countInsert;

	void insert(treeNode*& p, int item, vector<string>& s);
	void print(treeNode* p, ofstream& f, int addSpaces);
	void search(treeNode* p, int item, bool& status);
	void del(treeNode*& p, int item, vector<string>& s);
	void deleteNode(treeNode*& p, vector<string>& s);
	void getPredecessor(treeNode* p, int& item);
	void destroy(treeNode*& p);
	int getHeight(treeNode* p);
	int getBalance(treeNode* p);
	void rotateRight(treeNode*& r);
	void rotateLeft(treeNode*& r);
	void rotateLeftRight(treeNode*& r);
	void rotateRightLeft(treeNode*& r);
	void doubleRotateRight(treeNode*& r);
	void doubleRotateLeft(treeNode*& r);
	void balancing(treeNode*& p, int balance, int& item, vector<string>& s, int& count);
	printer printerObj;

public:
	avl();
	void insertNode(int item, ofstream& f);
	void printTree(ofstream& f);
	void searchNode(int item, bool& status);
	void deleteItem(int item, ofstream& f);
	int findHeight();
	int getCountDeletes();
	int getCountInserts();
	int getCountSearches();
	~avl();
};

#endif

//constructor
avl::avl()
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
int avl::getCountDeletes()
{
	return countDelete;
}

/*
Desc: getter for count inserts
Pre-condition : none
Post-condition : returns count inserts
*/
int avl::getCountInserts()
{
	return countInsert;
}

/*
Desc: getter for count searches
Pre-condition : none
Post-condition : returns count searches
*/
int avl::getCountSearches()
{
	return countSearch;
}

/*
Desc: insert node function that calls internal insert function
Pre-condition : integer, ofstream
Post-condition : none
*/
void avl::insertNode(int item, ofstream& f)
{
	vector<string> rotate;
	vector<string>::iterator i;
	insert(root, item, rotate);
	countInsert++;
	if (rotate.size() > 0)
	{
		cout << "Insert Rotations: " << rotate.size() << " ";
		for (i = rotate.begin(); i < rotate.end(); i++)
		{
			f << *i << " ";
			cout << *i << " ";
		}
		f << endl;
		cout << endl;
	}
}

/*
Desc: inserts a node at a leaf point
Pre-condition : treeNode pointer, integer, string vector
Post-condition : none
*/
void avl::insert(treeNode*& p, int item, vector<string>& s)
{
	if (p == NULL)
	{
		p = new treeNode;
		p->key = item;
		p->twin = NULL;
		p->numOfTwin = 1;
		p->right = NULL;
		p->left = NULL;
		p->height = 1;
		return;
	}
	else if (item == p->key)
	{
		p->numOfTwin++;
		countInsert++;
		insert(p->twin, item, s);
		return;
	}
	else if (item < p->key)
	{
		countInsert++;
		insert(p->left, item, s);
	}
	else
	{
		countInsert++;
		insert(p->right, item, s);
	}

	p->height = max(getHeight(p->left), getHeight(p->right)) + 1;

	int balance = getBalance(p);

	if (balance < -1 || balance > 1)
	{

		balancing(p, balance, item, s, countInsert);
	}

}

/*
Desc: balances the tree given in proper avl format
Pre-condition : treeNode pointer, 3 integers, string vector
Post-condition : none
*/
void avl::balancing(treeNode*& p, int balance, int& item, vector<string>& s, int& count)
{
	if (balance > 1 && item < p->left->key)
	{
		if (root->left->left == p)
		{
			count++;
			doubleRotateLeft(p);
			s.push_back("LL");
		}
		else
		{
			count++;
			s.push_back("L");
			rotateLeft(p);
		}
	}

	if (balance < -1 && item > p->right->key)
	{
		if (root->right->right == p)
		{
			count++;
			s.push_back("RR");
			doubleRotateRight(p);
		}
		else
		{
			count++;
			s.push_back("R");
			rotateRight(p);
		}
	}

	if (balance > 1 && item > p->left->key)
	{
		count++;
		s.push_back("RL");
		rotateRightLeft(p);
	}

	if (balance < -1 && item < p->right->key)
	{
		count++;
		s.push_back("LR");
		rotateLeftRight(p);
	}
}

/*
Desc: rotates the tree for the left right case
Pre-condition : treeNode pointer
Post-condition : none
*/
void avl::rotateLeftRight(treeNode*& r)
{
	rotateLeft(r->right);
	rotateRight(r);
}

/*
Desc: rotates the tree for the right left case
Pre-condition : treeNode pointer
Post-condition : none
*/
void avl::rotateRightLeft(treeNode*& r)
{
	rotateRight(r->left);
	rotateLeft(r);
}

/*
Desc: rotates the tree for the right case
Pre-condition : treeNode pointer
Post-condition : none
*/
void avl::rotateRight(treeNode*& r)
{
	if (r == NULL || r->right == NULL)
	{
		return;
	}
	treeNode* temp = r->right;
	r->right = temp->left;
	temp->left = r;
	r->height = max(getHeight(r->right), getHeight(r->left)) + 1;
	temp->height = max(getHeight(temp->right), getHeight(temp->left)) + 1;
	r = temp;
}

/*
Desc: rotates the tree for the left case
Pre-condition : treeNode pointer
Post-condition : none
*/
void avl::rotateLeft(treeNode*& r)
{
	if (r == NULL || r->left == NULL)
	{
		return;
	}
	treeNode* temp = r->left;
	r->left = temp->right;
	temp->right = r;
	r->height = max(getHeight(r->right), getHeight(r->left)) + 1;
	temp->height = max(getHeight(temp->right), getHeight(temp->left)) + 1;
	r = temp;
}

/*
Desc: rotates the tree for the double right case
Pre-condition : treeNode pointer
Post-condition : none
*/
void avl::doubleRotateRight(treeNode*& r)
{
	rotateLeft(r->right);
	rotateRight(r);
}

/*
Desc: rotates the tree for the double left case
Pre-condition : treeNode pointer
Post-condition : none
*/
void avl::doubleRotateLeft(treeNode*& r)
{
	rotateRight(r->left);
	rotateLeft(r);
}

/*
Desc: search function that calls internal search function
Pre-condition : integer, boolean
Post-condition : none
*/
void avl::searchNode(int item, bool& status)
{
	search(root, item, status);
	countSearch++;
}

/*
Desc: searches for a node
Pre-condition : treeNode pointer, integer, boolean
Post-condition : none
*/
void avl::search(treeNode* p, int item, bool& status)
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
void avl::deleteItem(int item, ofstream& f)
{
	vector<string> rotate;
	vector<string>::iterator i;
	del(root, item, rotate);
	countDelete++;
	if (rotate.size() > 0)
	{
		cout << "Delete Rotations: " << rotate.size() << " ";
		for (i = rotate.begin(); i < rotate.end(); i++)
		{
			f << *i << " ";
			cout << *i << " ";
		}
		f << endl;
		cout << endl;
	}
}

/*
Desc: searches for where to delete
Pre-condition : treeNode pointer, integer, string vector
Post-condition : none
*/
void avl::del(treeNode*& p, int item, vector<string>& s)
{
	if (p == NULL)
	{
		//cout << item << " does not exist in the tree" << endl;
		return;
	}
	else if (item < p->key)
	{
		countDelete++;
		del(p->left, item, s);
	}
	else if (item > p->key)
	{
		countDelete++;
		del(p->right, item, s);
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
		deleteNode(p, s);
		//return;
	}

	//return;
}

/*
Desc: deletes the node
Pre-condition : treeNode pointer, string vector
Post-condition : none
*/
void avl::deleteNode(treeNode*& p, vector<string>& s)
{
	int item;
	treeNode* temp;

	temp = p;

	if (p->left == NULL)
	{
		p = p->right;
		delete temp;
		//return;
	}
	else if (p->right == NULL)
	{
		p = p->left;
		delete temp;
		//return;
	}
	else
	{
		treeNode* temp = p;
		getPredecessor(temp, item); // p->right
		p->key = temp->key;
		p->twin = temp->twin;
		del(p->right, item, s);
	}

	if (p == NULL)
	{
		return;
	}

	p->height = max(getHeight(p->left), getHeight(p->right)) + 1;

	int balance = getBalance(p);

	if (balance < -1 || balance > 1)
	{
		balancing(p, balance, item, s, countDelete);
	}

	//return;
}

/*
Desc: finds the smallest in the tree given
Pre-condition : treeNode pointer, integer
Post-condition : none
*/
void avl::getPredecessor(treeNode* p, int& item)
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
void avl::printTree(ofstream& f)
{
	printerObj.printEverywhere(f, "---------------------------------------------------------------/n");
	print(root, f, 0);
	printerObj.printEverywhere(f, "---------------------------------------------------------------/n");
}

/*
Desc: prints
Pre-condition :treeNode pointer, ofstream, integer
Post-condition : none
*/
void avl::print(treeNode* p, ofstream& f, int addSpaces)
{
	if (root != NULL)
	{

		if (p->right != NULL)
		{
			print(p->right, f, addSpaces + 7);
		}

		for (int i = 0; i < addSpaces; i++)
		{
			printerObj.printEverywhere(f, " ");
		}
		if (p->twin != NULL && p->numOfTwin > 1)
		{
			string a = p->key + '(' + p->numOfTwin + ")/n";
			printerObj.printEverywhere(f, a);
		}
		else
		{
			string a = p->key + "/n";
			printerObj.printEverywhere(f, a);
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
int avl::findHeight()
{
	int ht = getHeight(root);
	return (ht - 1);
}

/*
Desc: finds the balance value for the balancing function
Pre-condition :treeNode pointer
Post-condition : integer
*/
int avl::getBalance(treeNode* p)
{
	if (p == NULL)
	{
		return 0;
	}

	int balance = 0;
	balance = getHeight(p->left) - getHeight(p->right);
	return balance;
}

/*
Desc: finds the height of the tree given
Pre-condition :treeNode pointer
Post-condition : integer
*/
int avl::getHeight(treeNode* p)
{
	if (p == NULL)
	{
		return 0;
	}
	return p->height;
}

/*
Desc: destroys the tree
Pre-condition :treeNode pointer
Post-condition : none
*/
void avl::destroy(treeNode*& p)
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
avl::~avl()
{
	destroy(root);
	root = NULL;
}