#include <iostream>

using namespace std;

const int rowMax = 20;
const int colMax = 20;

static void
prepareInput (int (&a) [rowMax][colMax])
{
	for (int row = 0; row < rowMax; ++row)
	{
		for (int col = 0; col < colMax; ++col)
		{
			if (row >=10 && row <=15 && col >= 5 && col <= 10)
				a[row][col] = 2;
			else
				a[row][col] = 0;
		}
	}	
}

static void
print (int (&a)[rowMax][colMax])
{
	cout << endl;
	for (int row = 0; row < rowMax; ++row)	
	{
		for (int col = 0; col < colMax; ++col)
		{
			cout << a[row][col] << " ";	
		}
		cout << endl;
	}
}

static void
paintFill (int (&a)[rowMax][colMax], int row, int col, int newColor, int originalColor)
{
	if (row < 0 || col < 0)
		return;

	if (a[row][col] != originalColor)
		return;
	
	a[row][col] = newColor;

	// move left
	paintFill (a, row-1, col, newColor, originalColor);
	// move right
	paintFill (a, row+1, col, newColor, originalColor);
	// move up
	paintFill (a, row, col-1, newColor, originalColor);
	// move down
	paintFill (a, row, col+1, newColor, originalColor);
}

int
main ()
{
	int a[rowMax][colMax];
	int row = 11, col = 7;
	int targetColor = 9;

	prepareInput (a);
	print(a);

	// give some val between row - 10,15 and col 5,10 or a val outside the same
	paintFill (a, row, col, targetColor, a[row][col]);
	print(a);

	return 0;
}
