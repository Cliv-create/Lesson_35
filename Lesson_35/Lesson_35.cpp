#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
using namespace std;

#define DEBUG_MODE

class Tree
{
public:
	struct Node // one element of the tree
	{
		int value; // useful data

		Node* parent = nullptr;
		Node* right = nullptr;
		Node* left = nullptr;

		void ShowNode() const
		{
			cout << value << ", ";
		}
	};

private:
	Node* root = nullptr;
	// int count;

public:
	bool IsEmpty() const
	{
		return root == nullptr;
	}

	Tree() {} // так как в классе есть явно объявленный конструктор копирования, приходится и конструктор без параметров явно делать :)

	~Tree()
	{
		Clear();
		cout << "AFTER TREE DESTRUCTION\n";
	}

private:
	void ShowTree(Node* element) const
	{
		if (element != 0)
		{
			ShowTree(element->left);
			element->ShowNode();
			ShowTree(element->right);
		}
	}

public:
	void ShowTree() const
	{
		cout << "\n";
		ShowTree(root);
		cout << "\n";
	}

private:
	Node* GetRoot() const
	{
		return root;
	}

	int GetCount(Node* element, int count) const
	{
		if (element != 0)
		{
			count = GetCount(element->left, count);
			count++;
			count = GetCount(element->right, count);
		}
		return count;
	}

public:
	int GetCount() const
	{
		int count = 0;
		count = GetCount(root, count);
		return count;
	}

private:
	void Clear(Node* element)
	{
		if (element != nullptr)
		{
			Clear(element->left);
			Clear(element->right);
			delete element;
			element = nullptr;
		}
	}

public:
	void Clear()
	{
		if (!IsEmpty())
		{
			Clear(root);
			root = nullptr;
		}
	}

	Node* FindNode(int value) const
	{
		if (IsEmpty())
			return nullptr;

		Node* f = root;
		while (true)
		{
			if (value < f->value)
			{
				if (f->left != nullptr)
					f = f->left;
				else
					break;
			}
			else if (value > f->value)
			{
				if (f->right != nullptr)
					f = f->right;
				else
					break;
			}
			else
				return f;
		}
		return nullptr;
	}

	void AddNode(int value)
	{
		if (FindNode(value))
			return;

		Node* n = new Node;
		n->value = value;
		Node* parent = nullptr;
		if (IsEmpty())
		{
			root = n;
			root->parent = parent;
		}
		else
		{
			Node* p = root;
			while (p != nullptr)
			{
				parent = p;
				if (n->value > p->value)
					p = p->right;
				else
					p = p->left;
			}
			if (n->value < parent->value)
				parent->left = n;
			else
				parent->right = n;
			n->parent = parent;
		}
	}

	Tree& operator = (const Tree& original)
	{
		if (!IsEmpty())
			Clear();

		AddNode(original.root->value);
		Copy(original.root);
		return *this;
	}

	Tree(const Tree& original)
	{
		AddNode(original.root->value);
		Copy(original.root);
	}

	void Copy(Node* element)
	{
		if (element->left != nullptr)
			AddNode(element->left->value);

		if (element->right != nullptr)
			AddNode(element->right->value);

		if (element->left != nullptr)
			Copy(element->left);

		if (element->right != nullptr)
			Copy(element->right);
	}

	void DeleteNode(int value)
	{
		Node* d = FindNode(value);
		if (d == nullptr)
			return;

		Node* parent = d->parent;
		if (d == root && GetCount() == 1)
		{
			Clear();
			return;
		}
		if (d->left == nullptr && d->right == nullptr)
		{
			if (parent->left == d)
				parent->left = nullptr;
			else
				parent->right = nullptr;
			delete d;
			return;
		}
		if (d->left == nullptr && d->right != nullptr)
		{
			if (parent->left == d)
			{
				parent->left = d->right;
			}
			else
			{
				parent->right = d->right;
			}
			d->right->parent = parent;
			delete d;
			return;
		}

		if (d->left != nullptr && d->right == nullptr)
		{
			if (parent->left == d)
			{
				parent->left = d->left;
			}
			else
			{
				parent->right = d->left;
			}
			d->left->parent = parent;
			delete d;
			return;
		}
		if (d->left != nullptr && d->right != nullptr)
		{
			Node* r = d->right;
			if (r->right == nullptr && r->left == nullptr)
			{
				d->value = r->value;
				d->right = nullptr;
				delete r;
			}
			else if (r->left != nullptr)
			{
				Node* p = r->left;
				while (p->left != nullptr)
					p = p->left;
				d->value = p->value;
				if (p->right == nullptr)
					p->parent->left = nullptr;
				else
					p->parent->left = p->right;
				delete p;
			}
			else
			{
				d->value = r->value;
				d->right = r->right;
				delete r;
			}
		}
	}

private:
	/*
	Node* GetRootNow() const {
		return root;
	}
	*/
	

	bool DegeneracyCheck(Node* root) const {

		// while (true) if data->right = nullptr break;
		// Then GetCount.
		// DegeneracyCheck() method
		// ---
		// TreeRebalance() method
		// Then run modified version of ShowTree, with each iteration adding a count to the vector.
		// Mix up the vector.
		// Add vectors element to the new tree one by one
		// Run Clear() for root of the tree
		// Set Tree* temp_root = root;
		Node* current = root;
		int right_elements_count = 0;
		while (true) {
			if (current != nullptr) {
				current = current->right;
				right_elements_count++;
			}
			else {
				break;
			}
		}
		cout << "RIGHT ELEMENT COUNT COMPLETED\n";
		cout << "Count: " << right_elements_count << "\n";
		int tree_elements_count = GetCount();
		if ((tree_elements_count / right_elements_count * 100) >= 45) {
			return true;
		}
		else return false;
	}

	void CopyToVector(const Node* element, vector<int> &destination) {
		if (element->left != nullptr)
			destination.push_back(element->left->value);

		if (element->right != nullptr)
			destination.push_back(element->right->value);

		if (element->left != nullptr)
			CopyToVector(element->left, destination);

		if (element->right != nullptr)
			CopyToVector(element->right, destination);
	}

public:
	int RebalanceTree() {
		// elements_count - setting vector's starting capacity value

		// Return 0: Everything is fine
		// Return 1: Tree was successfully rebalanced
		// Return -1: Error has occured (throw will be used)
		// If Tree is not degenerated, then return 0;
		if (DegeneracyCheck(this->root) == false) {
			return 0;
		}
		// If it is, continue with code
		#if defined(DEBUG_MODE)
			cout << "AFTER CHECK\n";
		#endif
		
		unsigned int original_elements_count = this->GetCount();
		vector<int> temp(original_elements_count); // Creating temporary array

		#if defined(DEBUG_MODE)
			cout << "AFTER ARRAY CREATION\n";
		#endif
		

		CopyToVector(this->root, temp); // Adding Tree nodes to array

		#if defined(DEBUG_MODE)
			cout << "AFTER COPYTOVECTOR\n";
		#endif
		

		// TEMP
		this->ShowTree();

		random_device rd;
		mt19937 g(rd());

		shuffle(temp.begin(), temp.end(), g); // Shuffling vector

		// TEMP
		#if defined(DEBUG_MODE)
			copy(temp.begin(), temp.end(), std::ostream_iterator<int>(std::cout, " "));
		cout << "\n";
		#endif
		
		
		// Tree temp_tree(*this);

		Tree temp_tree;

		#if defined(DEBUG_MODE)
			cout << "AFTER TEMPTREE CREATION\n";
		#endif
		

		for (unsigned int i = 0; i < original_elements_count; i++)
		{
			temp_tree.AddNode(temp[i]);
		}

		#if defined(DEBUG_MODE)
			cout << "AFTER ADDED SHUFFLE\n";
		#endif
		

		this->Clear();

		#if defined(DEBUG_MODE)
			cout << "AFTER CLEAR METHOD\n";
		#endif
		

		this->root = temp_tree.GetRoot();

		#if defined(DEBUG_MODE)
			cout << "AFTER NEW ROOT IS SET\n";
		#endif
		

		return 1;
	}
};

int main()
{
	setlocale(0, "UKR");

	#if defined(DEBUG_MODE)
		cout << "DEBUG MODE ON\n";
	#endif
	

	/*
	const int SIZE = 25;
	int ar[SIZE] = { // в начале и в конце массива - сотки
		100, 50, 25, 10, 5,
		15, 35, 27, 40, 75,
		60, 90, 300, 200, 150,
		250, 500, 400, 350, 370,
		700, 800, 750, 900, 100
	};

	Tree bt;
	for (int i = 0; i < SIZE; i++)
		bt.AddNode(ar[i]);
	bt.ShowTree();

	cout << "\n" << bt.GetCount() << "\n";
	// 24 элемента, потому что вторая сотка не добавилась

	Tree bt2 = bt;

	bt2.ShowTree();

	Tree bt3;
	for (int i = 0; i < 10; i++)
		bt3.AddNode(rand() % 100);
	bt3.ShowTree();

	bt3 = bt2;
	cout << "\n" << bt3.GetCount() << "\n";

	Tree::Node* f = bt.FindNode(750);
	if (f)
		cout << "\nзначение 750 найдено!\n";

	bt.DeleteNode(750);
	bt.ShowTree();

	bt.DeleteNode(700);
	bt.ShowTree();

	bt.DeleteNode(500);
	bt.ShowTree();

	bt.DeleteNode(25);
	bt.ShowTree();
	*/

	/*
	Tree bttemp;
	for (int i = 0; i < 10; i++)
	{
		bttemp.AddNode(i);
	}
	bttemp.ShowTree();
	bttemp.Clear();
	bttemp.AddNode(100000);
	bttemp.ShowTree();
	*/
	

	
	Tree bt4;
	for (int i = 0; i < 60; i++)
	{
		bt4.AddNode(i);
	}
	bt4.ShowTree();
	bt4.RebalanceTree();
	cout << "AFTER REBALANCE\n";
	
}