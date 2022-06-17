#include "Tree.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int height(node* p)
{
	return p ? p->height : 0;
}
int bFactor(node* p)
{
	return height(p->right) - height(p->left);
}
void updateHeight(node* p)
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}
node* rotateRight(node* p)
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	updateHeight(p);
	updateHeight(q);
	return q;
}
node* rotateLeft(node* q)
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	updateHeight(q);
	updateHeight(p);
	return p;
}
node* balance(node* p)
{
	updateHeight(p);
	if (bFactor(p) == 2)
	{
		if (bFactor(p->right) < 0)
			p->right = rotateRight(p->right);
		return rotateLeft(p);
	}
	if (bFactor(p) == -2)
	{
		if (bFactor(p->left) > 0)
			p->left = rotateLeft(p->left);
		return rotateRight(p);
	}
	return p;
}
node* find(node* p, int key)
{
	if (p == nullptr)
		return nullptr;
	if (p->key == key)
		return p;
	else if (p->key > key)
		return find(p->left, key);
	return find(p->right, key);
}
node* insert(node* p, node* new_node)
{
	if (!p) 
		return new_node;
	if (new_node->key < p->key)
		p->left = insert(p->left, new_node);
	else
		p->right = insert(p->right, new_node);
	return balance(p);
}

void Tree::addNode(int key, std::string info)
{
	if (root == nullptr)
		root = new node(key, info);
	else
		root = insert(root, new node(key, info));
	updateHeight(root);
}
void Tree::show()
{
	if (root == nullptr)
	{
		std::cout << "Дерево пустое\n";
		return;
	}
	std::vector<node*> v;
	node* curr_node = root;
	int max_height = curr_node->height;
	v.resize((1 << max_height));
	v[0] = root;
	int otstup = 1 << max_height;
	for(int i = 0; i < (1<<(max_height-1)) - 1; i ++)
	{
		if (v[i] != nullptr)
		{
			v[2 * i + 1] = v[i]->left;
			v[2 * i + 2] = v[i]->right;
		}
	}
	for(int j = 0; j < max_height; j++)
	{
		for(int i = 0; i < 1<<j; i++)
		{
			if(j==0)
				std::cout << "\033[33m"; // yellow
			else if (i % 2 == 0)
				std::cout << "\033[32m"; // green
			else
				std::cout << "\033[31m"; // red

			if(v[(1 << j) - 1 + i]!=nullptr)
				std::cout << std::setw(otstup) << v[(1<<j) - 1 + i]->key << std::setw(otstup)<< ' ';
			else
				std::cout << std::setw(otstup) << '-' << std::setw(otstup) << ' ';
		}
		std::cout << std::endl;
		otstup /= 2;
		std::cout << "\033[0m";
	}
}

node* Tree::findByKey(int key)
{
	return find(root, key);
}
void printLeftRootRight_rec(node* n)
{
	if (n == nullptr)
		return;
	printLeftRootRight_rec(n->left);
	std::cout << n->info << ' ';
	printLeftRootRight_rec(n->right);
}
void Tree::printLeftRootRight()
{
	printLeftRootRight_rec(root);
}

void printRootLeftRight_rec(node* n)
{
	if (n == nullptr)
		return;
	std::cout << n->info << ' ';
	printLeftRootRight_rec(n->left);
	printLeftRootRight_rec(n->right);
}
void Tree::printRootLeftRight()
{
	printRootLeftRight_rec(root);
}



void printLeftRightRoot_rec(node* n)
{
	if (n == nullptr)
		return;
	printLeftRootRight_rec(n->left);
	printLeftRootRight_rec(n->right);
	std::cout << n->info << ' ';
}
void Tree::printLeftRightRoot()
{
	printLeftRootRight_rec(root);
}

node* findmin(node* p)
{
	return p->left ? findmin(p->left) : p;
}
node* removemin(node* p)
{
	if (p->left == nullptr)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}
node* remove(node* p, int k)
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}
void Tree::removeByKey(int key)
{
	remove(root, key);
}
void clear_rec(node* p)
{
	if (p == nullptr)
		return;
	clear_rec(p->left);
	clear_rec(p->right);
	delete p;
}
void Tree::clear()
{
	clear_rec(root);
	root = nullptr;
}