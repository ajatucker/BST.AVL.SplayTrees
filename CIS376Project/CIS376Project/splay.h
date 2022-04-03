#pragma once
#ifndef SPLAY
#define SPLAY
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class splay
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

	void insert(treeNode*& p, int item, vector<string>& s);
	void print(treeNode* p, int addSpaces, ofstream& f);
	void search(treeNode*& p, int item, bool& status, vector<string>& s);
	void del(treeNode*& p, int item);
	void deleteNode(treeNode*& p);
	void getPredecessor(treeNode* p, int& item);
	void destroy(treeNode*& p);
	int height(treeNode* p, int& h);
	void zig(treeNode*& r);
	void zag(treeNode*& r);
	void zagZag(treeNode*& r);
	void zigZig(treeNode*& r);
	void zagZig(treeNode*& r);
	void zigZag(treeNode*& r);
	void splaying(treeNode*& p, int item, vector<string>& s, int& count);

public:
	splay();
	void insertNode(int item, ofstream& f);
	void printTree(ofstream& f);
	void searchNode(int item, bool& status, ofstream& f);
	void deleteItem(int item, ofstream& f);
	int findHeight();
	int getCountDeletes();
	int getCountInserts();
	int getCountSearches();
	~splay();
};

#endif

//constructor
splay::splay()
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
int splay::getCountDeletes()
{
	return countDelete;
}

/*
Desc: getter for count inserts
Pre-condition : none
Post-condition : returns count inserts
*/
int splay::getCountInserts()
{
	return countInsert;
}

/*
Desc: getter for count searches
Pre-condition : none
Post-condition : returns count searches
*/
int splay::getCountSearches()
{
	return countSearch;
}

/*
Desc: splaying function that splays given root to node
Pre-condition : treeNode pointer, 2 integers, string vector
Post-condition : none
*/
void splay::splaying(treeNode*& p, int item, vector<string>& s, int& count)
{
	if (p == NULL || p->key == item)
	{
		return;
	}

	if (item < p->key)
	{

		if (p->left == NULL)// || p->right == NULL)
		{
			return;
		}

		//if (p->left->key > item)
		//{
		if (p->left->left != NULL && p->left->left->key == item)//p->left->key > item
		{
			count++;
			s.push_back("zigzig");
			//cout << "zigzig" << endl;
			splaying(p->left->left, item, s, count); //p->left
			zigZig(p);
		}
		//}

		else if (p->left->right != NULL && item > p->left->key) //p->left->key
		{
			count++;
			s.push_back("zigzag");
			//cout << "zigzag" << endl;
			zigZag(p);
			//zag(p->left);
			//zig(p);
		}

		else if (root->left != NULL && root->left->key == item)//item < p->key && root->left->left == p)
		{
			count++;
			s.push_back("zig");
			//cout << "zig " << endl;
			zig(p);
		}

		else
		{
			return;
		}

	}
	else
	{
		if (p->right == NULL)
		{
			return;
		}

		if (p->right->left != NULL && item < p->right->key)
		{
			count++;
			s.push_back("zagzig");
			//cout << "zagzig" << endl;
			zagZig(p);
			//zig(p->right);
			//zag(p);
		}

		else if (p->right->right != NULL && p->right->right->key == item)//p->right->key < item)  
		{
			count++;
			s.push_back("zagzag");
			//cout << "zagzag" << endl;
			splaying(p->right->right, item, s, count);
			zagZag(p);
		}

		else if (root->right != NULL && root->right->key == item)//item > p->key && root->right->right == p) //p->right->key
		{
			count++;
			s.push_back("zag");
			//cout << "zag " << endl;
			zag(p);
		}

		else
		{
			return;
		}
	}
}

/*
Desc: insert node function that calls internal insert function
Pre-condition : integer, ofstream
Post-condition : none
*/
void splay::insertNode(int item, ofstream& f)
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
void splay::insert(treeNode*& p, int item, vector<string>& s)
{
	if (p == NULL)
	{
		p = new treeNode;
		p->key = item;
		p->twin = NULL;
		p->numOfTwin = 1;
		p->right = NULL;
		p->left = NULL;
		return;
	}
	else if (item == p->key)
	{
		p->numOfTwin++;
		//countInsert++;
		insert(p->twin, item, s);
		return;
	}
	else if (item < p->key)
	{
		//countInsert++;
		insert(p->left, item, s);
	}
	else
	{
		//countInsert++;
		insert(p->right, item, s);
	}

	splaying(p, item, s, countInsert);
}

/*
Desc: splays the function for the zag zig case
Pre-condition : treeNode pointer
Post-condition : none
*/
void splay::zagZig(treeNode*& r)
{
	zig(r->right);
	zag(r);
}

/*
Desc: splays the function for the zig zag case
Pre-condition : treeNode pointer
Post-condition : none
*/
void splay::zigZag(treeNode*& r)
{
	zag(r->left);
	zig(r);
}

/*
Desc: splays the function for the zag case
Pre-condition : treeNode pointer
Post-condition : none
*/
void splay::zag(treeNode*& r)
{
	if (r == NULL || r->right == NULL)
	{
		return;
	}
	treeNode* temp = r->right;
	r->right = temp->left;
	temp->left = r;
	r = temp;
}

/*
Desc: splays the function for the zig zig case
Pre-condition : treeNode pointer
Post-condition : none
*/
void splay::zig(treeNode*& r)
{
	if (r == NULL || r->left == NULL)
	{
		return;
	}
	treeNode* temp = r->left;
	r->left = temp->right;
	temp->right = r;
	r = temp;
}

/*
Desc: splays the function for the zagzag zig case
Pre-condition : treeNode pointer
Post-condition : none
*/
void splay::zagZag(treeNode*& r)
{
	zag(r);
	zag(r);
}

/*
Desc: splays the function for the zigzig case
Pre-condition : treeNode pointer
Post-condition : none
*/
void splay::zigZig(treeNode*& r)
{
	zig(r);
	zig(r);
}

/*
Desc: search function that calls internal search function
Pre-condition : integer, boolean, ofstream
Post-condition : none
*/
void splay::searchNode(int item, bool& status, ofstream& f)
{
	vector<string> rotate;
	vector<string>::iterator i;
	search(root, item, status, rotate);
	countSearch++;
	if (rotate.size() > 0)
	{
		cout << "Search Rotations: " << rotate.size() << " ";
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
Desc: searches for a node by splaying
Pre-condition : treeNode pointer, integer, boolean, string vector
Post-condition : none
*/
void splay::search(treeNode*& p, int item, bool& status, vector<string>& s)
{
	if (p == NULL)
	{
		status = false;
		return;
	}
	else if (item < p->key)
	{
		//countSearch++;
		search(p->left, item, status, s);
	}
	else if (item > p->key)
	{
		//countSearch++;
		search(p->right, item, status, s);
	}
	else
	{
		item = p->key;
		status = true;
		return;
	}

	splaying(p, item, s, countSearch);
}

/*
Desc: splays item to root, delete function that calls internal search for delete function
Pre-condition :integer
Post-condition : none
*/
void splay::deleteItem(int item, ofstream& f)
{
	vector<string> rotate;
	vector<string>::iterator i;
	splaying(root, item, rotate, countDelete);
	del(root, item);
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
Pre-condition : treeNode pointer, integer
Post-condition : none
*/
void splay::del(treeNode*& p, int item)
{
	if (p == NULL)
	{
		//cout << item << " does not exist in the tree" << endl;
		return;
	}
	else if (item < p->key)
	{
		//countDelete++;
		del(p->left, item);
	}
	else if (item > p->key)
	{
		//countDelete++;
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
		//countDelete++;
		deleteNode(p);
	}

}

/*
Desc: deletes the node
Pre-condition : treeNode pointer
Post-condition : none
*/
void splay::deleteNode(treeNode*& p)
{
	int item;
	treeNode* temp;

	temp = p;
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

}

/*
Desc: finds the smallest in the tree given
Pre-condition : treeNode pointer, integer
Post-condition : none
*/
void splay::getPredecessor(treeNode* p, int& item)
{
	while (p != NULL && p->left != NULL)
	{
		//countDelete++;
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
void splay::printTree(ofstream& f)
{
	cout << "---------------------------------------------------------------" << endl;
	f << "---------------------------------------------------------------" << endl;
	print(root, 0, f);
	cout << "---------------------------------------------------------------" << endl;
	f << "---------------------------------------------------------------" << endl;
}

/*
Desc: prints
Pre-condition :treeNode pointer, ofstream, integer
Post-condition : none
*/
void splay::print(treeNode* p, int addSpaces, ofstream& f)
{
	if (root != NULL)
	{

		if (p->right != NULL)
		{
			print(p->right, addSpaces + 7, f);
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
			print(p->left, addSpaces + 7, f);
		}

	}
}

/*
Desc: calls internal height function to find the height of the tree
Pre-condition :none
Post-condition :integer
*/
int splay::findHeight()
{
	int ht = 0;
	height(root, ht);
	return ht;
}

/*
Desc: finds the height of the tree given
Pre-condition :treeNode pointer, integer
Post-condition : integer
*/
int splay::height(treeNode* p, int& h)
{
	if (p == NULL)
	{
		return 0;
	}

	h = max(height(p->left, h), height(p->right, h)) + 1;

	return (h - 1);
}

/*
Desc: destroys the tree
Pre-condition :treeNode pointer
Post-condition : none
*/
void splay::destroy(treeNode*& p)
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
splay::~splay()
{
	destroy(root);
	root = NULL;
}