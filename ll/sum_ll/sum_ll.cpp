#include <forward_list>
#include <iostream>

using namespace std;

int main ()
{
	forward_list<int> a = {3, 1, 5};
	forward_list<int> b = {5, 9, 2};
	forward_list<int> c;
	int carry = 0;

	// Assume both the lists are of same length.
	for (auto iter1 = a.begin(), iter2 = b.begin (); iter1 != a.end () && iter2 != b.end (); ++iter1, ++iter2)
	{
		int temp = *iter1 + *iter2 + carry;
		c.push_front (temp % 10);
		carry = temp / 10;
	}

	// Copy the carry to the result
	if (carry)
		c.push_front (carry);
	c.reverse ();

	// If the lists are of different length, the carry needs to be added to the next element of the longer list and rest of
	// the elements from the list has to be copied to the result.

	// print the result
	bool first = true;
	for (int &res : c) {
		if (first) {
			cout << res;
			first = false;
		} else
			cout << " -> " << res;
	}
	cout << endl;
	return 0;
}
