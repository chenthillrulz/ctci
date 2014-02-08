#include <iostream>
#include <cmath>

using namespace std;

// passing array by refrence yields error, why ? ;)
static bool 
//canPlaceQueen (int tRow, int tCol, int (&qPos)[8])
canPlaceQueen (int tRow, int tCol, int *qPos)
{
	for (int row = 0; row < tRow; row++)
	{
		if (tCol == qPos[row])
			return false;

		int x = abs(row - tRow);
		int y = abs(tCol - qPos[row]);
		if (x == y)
			return false;
	}

	return true;
}

// passing array by refrence yields error, why ? ;)
static void
//print_positions (int (&qPos)[8])
print_positions (int *qPos)
{
	for (int row = 0; row < 8; row++)
		cout << row << "," << qPos[row] << "; ";
	cout << endl;
}

// we could also replace count with a container (forward list or list) to store the position arrays
static void
placeQueeen (int row, int qPos[8], int &count)
{
	if (row > 7)
	{
		print_positions (qPos);
		++count;
		return;
	}

	for (int col = 0; col < 8; ++col)
	{
		if (canPlaceQueen (row, col, qPos))
		{
			qPos[row] = col;
			placeQueeen (row+1, qPos, count);
		}
	}

	return;
}

int
main ()
{
	int qPos[8], row = 0, count = 0;

	for (int y=0; y <8; y++)
		qPos[y] = -1;

	cout << "Printing possible ways to place the queens " << endl;
	placeQueeen (0, qPos, count);

	cout << "Number of ways in which queens can be placed in each row is " << count << endl;
	return 0;
}
