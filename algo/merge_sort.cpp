#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


void merge (int *a, int low, int mid, int high)
{
	int *aux = new int [high - low + 1];
	int leftS = low, rightS = mid+1;
	int index = 0;

	while (leftS <= mid && rightS <= high)
	{
		if (a[leftS] < a[rightS])
		{
			aux[index++] = a[leftS++];
		} else {
			aux[index++] = a[rightS++];
		}
	}

	if (leftS <= mid)
	{
		for (int i = leftS; i <= mid; i++)
			aux[index++] = a[i];
	}

	if (rightS <= high)
	{
		for (int i = rightS; i <= high; i++)	
			aux[index++] = a[i];
	}

	for (int i = low; i <= high; i++)
		a[i] = aux[i - low];

	delete [] aux;
}

void mergeSort (int *a, int low, int high)
{
	if (high <= low)
		return;
	
	int mid = (low + high)/2;
	mergeSort (a, low, mid);
	mergeSort (a, mid+1, high);

	merge (a, low, mid, high);
}

int main ()
{
	int *a = NULL;
	int len;

	cin >> len;

	a = new int [len];
	cout << "Total Input data - " << len << endl;
	for (int i = 0; i < len; i++)
	{
		cin >> a[i];
		cout << a [i] << " ";
	}
	cout << endl;

	mergeSort (a, 0, len-1);
	for (int i = 0; i < len; i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}
