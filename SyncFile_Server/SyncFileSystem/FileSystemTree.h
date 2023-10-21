#ifndef FILESYSTEMTREE
#define FILESYSTEMTREE
#include <queue>
#include "FileSystem.h"

using namespace std;

struct Node
{
	FileSystem fs;
	Node* next;
	Node* left;
	Node* right;
	Node() : fs(FileSystem()), left(NULL), right(NULL), next(NULL)
	{}
	Node(FileSystem fs) : fs(fs), left(NULL), right(NULL), next(NULL)
	{}
};

class FileSystemTree
{
private:
	Node* root;
	unsigned int treeSize;
	unsigned int filesLoaded;
	//Recursive Method
	Node* _insert(Node* root, FileSystem fs, bool& isInserted);
	Node* _remove(Node* root, FileSystem fs, bool& isRemoved);
	int _height(Node* root);
	Node* _search(Node* root, FileSystem fs);
	Node* _leftRotate(Node* root);
	Node* _rightRotate(Node* root);
	Node* minimum(Node* root);
	Node* maximum(Node* root);
	void inOrderTraversal(Node* root);
	int getBalanceFactor(Node* root);
public:
	//Default Constructor
	FileSystemTree();
	//Setter
	void setRoot(Node* root);
	//Getter
	unsigned int getNoFilesLoaded();
	unsigned int getTreeSize();
	//Methods
	bool insert(FileSystem fs);
	bool remove(FileSystem fs);
	int height();
	bool search(FileSystem fs);
	Node* getSearchResults(FileSystem fs);
	void print();
	int balanceFactor();
	//Other Methods
	bool loadFileSystem();
};

#endif