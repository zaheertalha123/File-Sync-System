#include "FileSystemTree.h"

using namespace std;

//Implementing Constructor
FileSystemTree::FileSystemTree()
{
	this->root = NULL;
	this->filesLoaded = 0;
	this->treeSize = 0;
}

//Implementing Setter
void FileSystemTree::setRoot(Node* root)
{
	this->root = root;
}

//Implementing Getter
unsigned int FileSystemTree::getNoFilesLoaded()
{
	return this->filesLoaded;
}
unsigned int FileSystemTree::getTreeSize()
{
	return this->treeSize;
}


//Implementing Methods
bool FileSystemTree::insert(FileSystem fs)
{
	bool isInserted = false;
	root = _insert(root, fs, isInserted);
	if (isInserted)
	{
		treeSize++;
		return true;
	}
	return false;
}
bool FileSystemTree::remove(FileSystem fs)
{
	bool isRemoved = false;
	root = _remove(root, fs, isRemoved);
	if (isRemoved)
	{
		treeSize--;
		return true;
	}
	return false;
}
int FileSystemTree::height()
{
	return _height(root);
}
bool FileSystemTree::search(FileSystem fs)
{
	if (!_search(root, fs))
		return false;
	return true;
}
Node* FileSystemTree::getSearchResults(FileSystem fs)
{
	return _search(root, fs);
}
void FileSystemTree::print()
{
	cout << "FileSystemTree Keys : " << endl;
	inOrderTraversal(root);
	cout << endl;
}
int FileSystemTree::balanceFactor()
{
	return getBalanceFactor(root);
}

//Implementing Recursive Methods
Node* FileSystemTree::_insert(Node* root, FileSystem fs, bool& isInserted)
{
	if (root == NULL)
	{
		isInserted = true;
		return new Node(fs);
	}
	else if (fs.getNameKey() < root->fs.getNameKey())
		root->left = _insert(root->left, fs, isInserted);
	else if (fs.getNameKey() > root->fs.getNameKey())
		root->right = _insert(root->right, fs, isInserted);
	else
	{
		Node* temp = new Node(fs);
		temp->left = root->left;
		temp->right = root->right;
		root->left = NULL;
		root->right = NULL;
		temp->next = root;
		root = temp;
		isInserted = true;
		return root;
	}
	int bfactor = getBalanceFactor(root);
	if (bfactor > 1 && fs.getNameKey() < root->left->fs.getNameKey())
	{
		//cout << "RR" << endl;
		return _rightRotate(root);
	}
	else if (bfactor < -1 && fs.getNameKey() > root->right->fs.getNameKey())
	{
		//cout << "LL" << endl;
		return _leftRotate(root);
	}
	else if (bfactor > 1 && fs.getNameKey() > root->left->fs.getNameKey())
	{
		//cout << "LR" << endl;
		root->left = _leftRotate(root->left);
		return _rightRotate(root);
	}
	else if (bfactor < -1 && fs.getNameKey() < root->right->fs.getNameKey())
	{
		//cout << "RL" << endl;
		root->right = _rightRotate(root->right);
		return _leftRotate(root);
	}
	return root;
}
Node* FileSystemTree::_remove(Node* root, FileSystem fs, bool& isRemoved)
{
	if (root == NULL)
	{
		isRemoved = false;
		return NULL;
	}
	else if (fs.getNameKey() < root->fs.getNameKey())
		root->left = _remove(root->left, fs, isRemoved);
	else if (fs.getNameKey() > root->fs.getNameKey())
		root->right = _remove(root->right, fs, isRemoved);
	else
	{
		Node* curr = root;
		if (root->left == NULL && root->right == NULL)
		{
			if ((curr->fs.getNameKey() == fs.getNameKey()) &&
				(curr->fs.getFullPath() == fs.getFullPath()))
			{
				cout << "Node Is Found And Left And Right Are NULL" << endl;
				root = curr->next;
				delete(curr);
				isRemoved = true;
				return root;
			}
		}
		else if (root->left != NULL && root->right != NULL)
		{
			if ((curr->fs.getNameKey() == fs.getNameKey()) &&
				(curr->fs.getFullPath() == fs.getFullPath()))
			{
				if (curr->next == NULL)
				{
					cout << "Node Is Found And Left And Right Are Not NULL" << endl;
					Node* temp = minimum(root->left);
					root->fs = temp->fs;
					root->right = _remove(root->left, temp->fs, isRemoved);
				}
				else
				{
					cout << "Node Is Found And List Is Not Empty!" << endl;
					root = curr->next;
					root->left = curr->left;
					root->right = curr->right;
					delete(curr);
					return root;
				}
			}
		}
		else
		{
			if ((curr->fs.getNameKey() == fs.getNameKey()) &&
				(curr->fs.getFullPath() == fs.getFullPath()))
			{
				if (curr->next != NULL)
				{
					cout << "Node Is Found And List Is Not Empty!" << endl;
					root = curr->next;
					root->left = curr->left;
					root->right = curr->right;
				}
				else
				{
					cout << "Node Is Found And Left or Right is NULL" << endl;
					if (curr->right == NULL)
						root = curr->left;
					if (curr->left == NULL)
						root = curr	->right;
				}
				delete(curr);
				isRemoved = true;
				return root;
			}
		}
		Node* prev = NULL;
		cout << "I Have Found The Name And Removing It From The List" << endl;
		while (curr != NULL)
		{
			if ((curr->fs.getNameKey() == fs.getNameKey()) &&
				(curr->fs.getFullPath() == fs.getFullPath()))
				break;
			prev = curr;
			curr = curr->next;
		}
		if (curr == NULL)
		{
			cout << "Node Not Found In The List" << endl;
			isRemoved = false;
			return root;
		}
		prev->next = curr->next;
		delete(curr);
		isRemoved = true;
		return root;
	}
	int bfactor = getBalanceFactor(root);
	if (bfactor == 2 && getBalanceFactor(root->left) >= 0)
	{
		//cout << "RR" << endl;
		return _rightRotate(root);
	}
	else if (bfactor == 2 && getBalanceFactor(root->left) == -1)
	{
		//cout << "LR" << endl;
		root->left = _leftRotate(root->left);
		return _rightRotate(root);
	}
	else if (bfactor == -2 && getBalanceFactor(root->right) <= 0)
	{
		//cout << "LL" << endl;
		return _leftRotate(root);
	}
	else if (bfactor == -2 && getBalanceFactor(root->right) == 1)
	{
		//cout << "RL" << endl;
		root->right = _rightRotate(root->right);
		return _leftRotate(root);
	}
	return root;
}
int FileSystemTree::_height(Node* root)
{
	if (root == NULL)
		return -1;
	else
	{
		int lHeight = _height(root->left);
		int RHeight = _height(root->right);
		if (lHeight > RHeight)
			return lHeight + 1;
		else
			return RHeight + 1;
	}
}
Node* FileSystemTree::_search(Node* root, FileSystem fs)
{
	if (root == NULL || root->fs.getNameKey() == fs.getNameKey())
		return root;
	else if (fs.getNameKey() < root->fs.getNameKey())
		return _search(root->left, fs);
	else
		return _search(root->right, fs);
}
Node* FileSystemTree::_leftRotate(Node* root)
{
	Node* y = root->right;
	Node* T2 = y->left;
	y->left = root;
	root->right = T2;
	return y;
}
Node* FileSystemTree::_rightRotate(Node* root)
{
	Node* x = root->left;
	Node* T2 = x->right;
	x->right = root;
	root->left = T2;
	return x;
}
Node* FileSystemTree::minimum(Node* root)
{
	while (root->left != NULL)
		root = root->left;
	return root;
}
Node* FileSystemTree::maximum(Node* root)
{
	while (root->right != NULL)
		root = root->right;
	return root;
}
void FileSystemTree::inOrderTraversal(Node* root)
{
	if (root == NULL)
		return;
	inOrderTraversal(root->left);
	Node* curr = root;
	while (curr != NULL)
	{
		cout << "---------------------------" << endl;
		curr->fs.printDetails();
		cout << "---------------------------" << endl;
		curr = curr->next;
	}
	inOrderTraversal(root->right);
}
int FileSystemTree::getBalanceFactor(Node* root)
{
	if (root == NULL)
		return -1;
	return _height(root->left) - _height(root->right);
}

//Implementing Other Methods
bool FileSystemTree::loadFileSystem()
{
	string startpath = "Z:\\SyncFileSystem\\SyncFileSystem\\Home";
	string path;
	queue<string> que;
	que.push(startpath);
	DIR* dir;
	dirent* ent;
	while (!que.empty())
	{
		path = que.front();
		que.pop();
		dir = opendir(path.c_str());
		if (dir == NULL)
			continue;
		while ((ent = readdir(dir)) != NULL)
		{
			if (((string)ent->d_name == ".") || ((string)ent->d_name == ".."))
				continue;
			insert(FileSystem(ent, path));
			filesLoaded++;
			if (ent->d_type == DT_DIR)
			{
				que.push(path + "\\" + ent->d_name);
			}
		}
	}
	return true;
}