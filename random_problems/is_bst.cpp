#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;


typedef struct _TreeNode
{
	int data;
	struct _TreeNode *left;
	struct _TreeNode *right;


	_TreeNode ()
	{
		data = -1;
		left = NULL;
		right = NULL;
	}
} TreeNode;


static bool
findInsertionParent (string &loc, TreeNode *trav, TreeNode **node, bool *isRight)
{
	for (string::iterator iter=loc.begin(); iter != loc.end(); ++iter) {
		*node = trav;

		if (!trav)
			return false;

		if (*iter == 'R')
		{
			*isRight = true;
			trav = trav->right;
		} else {
			*isRight = false;
			trav = trav->left;
		}
	}

	return true;
}

static void
preOrderTav (TreeNode *node, ostream &os, string prefix)
{
	if (!node)
		return;

	stringstream ss;
	ss << node->data;

	if (prefix == "")
		os << node->data << ";\n";
	else
		os << prefix << "->" << ss.str()<< "\n";

	prefix = ss.str ();

	preOrderTav (node->left, os, prefix);
	preOrderTav (node->right, os, prefix);
}

// Let us assume the tree has positive values only
static bool
is_bst (TreeNode *node, int &prev)
{
	bool ret = true;
	if (!node)
		return true;
	
	ret = is_bst (node->left, prev);
	if (!ret)
		return ret;

	if (prev != -1 && node->data < prev)
		return false;
	prev = node->data;
	cout << prev << " ";
	
	ret = is_bst (node->right, prev);

	return ret;
}

int main (int argc, char *argv[])
{
	string loc;
	int value;
	TreeNode *root = new TreeNode();

	loc.reserve (100);
	while (true)
	{
		cin >> loc;
		cin >> value;

		if (loc == "root")
			root->data = value;
		else if (loc == "end")
			break;
		else 
		{
			TreeNode *insertAt = NULL;
			bool isRight = false, found = false;
			
			found = findInsertionParent (loc, root, &insertAt, &isRight);
			
			
			if (!found)
			{
				cout << "Malformed input data, location - " << loc << endl;
				return -1;
			}
			
			if (isRight) {
				insertAt->right = new TreeNode ();
				insertAt->right->data = value;	
			} else {
				insertAt->left = new TreeNode ();
				insertAt->left->data = value;	
			}
		}
	}

	// visualize the tree
	filebuf fb;
	fb.open ("out.txt", ios::out);
	ostream os (&fb);
	os << "digraph BST { \n";
	preOrderTav (root, os, "");
	os << "}\n";

	// check if its a bst
	int init = -1;
	bool bIsBst = is_bst (root, init);
	cout << endl;
	string answer = bIsBst ? "Yes" : "No";
	cout << "Is tree a BST ? " << answer << endl;

	// complexity analysis

}
