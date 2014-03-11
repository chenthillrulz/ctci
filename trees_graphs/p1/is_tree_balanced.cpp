#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

template <typename T>
class BinaryTree;

// In future I can add a parent pointer for optimization without affecting the users of BinarySearchTree
template <typename T>
class Node 
{
	private: 
		T data;
		T key;

		Node *left;
		Node *right;
		
		Node ():left(NULL), right (NULL), data(0), key(0)
		{
		}
		
		Node (T ckey, T cdata):left(NULL), right (NULL), data(cdata), key(ckey)
		{
		}

		Node (Node &cnode)
		{
			data = cnode.data;
			key = cnode.key;
		}
		
		bool isLeaf ()
		{
			if (left == NULL && right == NULL)
				return true;
			else 
				return false;
		}

		friend class BinaryTree<T>; // class BinaryTree can now access data directly
};

template <typename T>
class BinaryTree
{
	private:
		Node<T> *root;

		Node<T> * find_suitable_parent (Node<T> *parent, T key);
		Node<T> * find_node (Node<T> *node, Node<T> **parent, T key);
		Node<T> * find_inorder_successor_node (Node<T> *node, Node<T> **parent);
		bool remove_leaf (Node<T> *node, Node<T> *parent);
		bool remove_node_with_one_child (Node<T> *node);
		void in_order_traverse (Node<T> *node, ostream &out);
		int isBalancedInternal (Node<T> *node);

	public:
		BinaryTree ():root(NULL)
		{
		}

		bool get_data (T key, T *data);
		void insert (T key, T data);
		bool remove (T key);
		~BinaryTree ();

		bool isBalanced ()
		{
			if (isBalancedInternal (root) == -1)
				return false;
			else return true;
		}

		template <class U>
		friend ostream & operator<< (ostream &, BinaryTree<U> *tree);
};

template <typename T>
Node<T> * BinaryTree<T>::find_suitable_parent (Node<T> *parent, T key)
{
	if (key < parent->key)
	{
		if (parent->left == NULL)
			return parent;
		else
			return find_suitable_parent (parent->left, key);
	}
	
	if (key >= parent->key)
	{
		if (parent->right == NULL)
			return parent;
		else
			return find_suitable_parent (parent->right, key);
	}
}

template <typename T>
void BinaryTree<T>::insert (T key, T data)
{
	if (root == NULL)
	{
		root = new Node<T> (key, data);
		return;
	}

	Node<T> *parent = find_suitable_parent (root, key);
	if (key >= parent->key)
		parent->right = new Node<T> (key, data);
	else
		parent->left = new Node<T> (key, data);
}

template <typename T>
Node<T> * BinaryTree<T>::find_node (Node<T> *node, Node<T> **parent, T key)
{
	if (node->key == key)
		return node;
	else if (node->isLeaf ())
		return NULL;

	*parent = node;
	if (node->left && key < node->key)
		return find_node (node->left, parent, key);

	if (node->right && key >= node->key)
		return find_node (node->right, parent, key);

	return NULL;
}

template <typename T>
Node<T> * BinaryTree<T>::find_inorder_successor_node (Node<T> *node, Node<T> **parent)
{
	if (node->left == NULL)
		return node;

	*parent = node;
	return find_inorder_successor_node (node->left, parent);
}

template <typename T>
bool BinaryTree<T>::remove_leaf (Node<T> *node, Node<T> *parent)
{
	// In case node is a leaf node
	if (node->isLeaf ())
	{
		// its a root node
		if (parent == NULL) 
		{
			root = NULL;
			delete node;
		} else 
		{
			if (parent->left == node)
				parent->left = NULL;
			else
				parent->right = NULL;

			delete node;
		}

		return true;
	}

	return false;
}

template <typename T>
bool BinaryTree<T>::remove_node_with_one_child (Node<T> *node)
{
	// In case node has only one child, replace it with the child
	if (node->left == NULL || node->right == NULL)
	{
		Node<T> *repl;

		if (node->left == NULL)
			repl = node->right;
		else
			repl = node->left;
		
		node->key = repl->key;
		node->data = repl->data;
		
		node->left = repl->left;
		node->right = repl->right;

		delete repl;
		
		return true;
	}

	return false;
}

// Ideally we would want to return the node being deleted for the users to handle 
// data, key destruction
template <typename T>
bool BinaryTree<T>::remove (T key)
{
	Node<T> *parent = NULL;
	Node<T> *node = find_node (root, &parent, key);

	if (node == NULL)
		return false; // or maybe throw an exception

	if (remove_leaf (node, parent))
		return true;
	
	if (remove_node_with_one_child (node))
		return true;

	// In case node has two children, find the inorder successor node and replace it with
	// with the current node. delete the inorder successor node	
	{
		parent = node;
		
		// finds the left most node of node->right
		Node<T> *in_order_suc = find_inorder_successor_node (node->right, &parent); 
		
		node->key = in_order_suc->key;
		node->data = in_order_suc->data;

		if (in_order_suc->isLeaf ())
			remove_leaf (in_order_suc, parent);
		else
			remove_node_with_one_child (in_order_suc);
	}

	return true;
}

template <typename T>
bool BinaryTree<T>::get_data (T key, T *data)
{
	Node<T> *parent = NULL;
	Node<T> *node = find_node (root, &parent, key);

	if (node)
	{
		*data = node->data;
		return true;
	}

	return false;
}

template <typename T>
BinaryTree<T>::~BinaryTree ()
{
	
}

template <typename T>
void BinaryTree<T>::in_order_traverse (Node<T> *node, ostream &out)
{
	if (node && node->left)
		in_order_traverse (node->left, out);
	out << node->key << " ";
	if (node && node->right)
		in_order_traverse (node->right, out);
}

//
template <typename T>
ostream & operator<< (ostream &out, BinaryTree<T> *tree)
{
	out << "Printing Binary Tree InOrder \n";
	tree->in_order_traverse (tree->root, out);
	out << "\n\n";
}

template <typename T>
int BinaryTree<T>::isBalancedInternal (Node<T> *node)
{
	if (node == NULL)
		return 0;

	int leftHeight = 0;
	if (node->left)
		leftHeight = isBalancedInternal (node->left);

	if (leftHeight == -1)
		return -1;

	int rightHeight = 0;
	if (node->right)
		rightHeight = isBalancedInternal (node->right);

	if (rightHeight == -1)
		return -1;

	if (abs (leftHeight - rightHeight) > 1)
		return -1;
	else
		return fmax (leftHeight, rightHeight) + 1;
}

int main ()
{
	BinaryTree<int> *tree = new BinaryTree<int> ();

	tree->insert (2, 799);
	tree->insert (1, 799);
	tree->insert (3, 799);
	tree->insert (4, 799);
//	tree->insert (5, 799); //Uncomment me
	
	//Tree with data inserted
	cout << tree;

	cout << "is balanced ? " << tree->isBalanced () << endl;
}
