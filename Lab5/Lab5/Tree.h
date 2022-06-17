#pragma once
#include <string>
struct node
{
public:
	int key;
	std::string info;
	int height;
	node* left;
	node* right;
	node(int k, std::string inf) { key = k; left = right = nullptr; height = 1; info = inf; }
};
class Tree
{
public:
	node* root = nullptr;
	void addNode(int key, std::string info);
	void show();
	node* findByKey(int key);
	void printLeftRootRight();
	void printRootLeftRight();
	void printLeftRightRoot();
	void removeByKey(int key);
	void clear();
	~Tree()
	{
		clear();
	}
};
