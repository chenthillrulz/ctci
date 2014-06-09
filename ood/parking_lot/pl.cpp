#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Just building the skeleton interfaces

class Vehicle
{
	private: 
		string number;
		bool isTwoWheeler;
	public:
		// We could create a subclass and return the isTwoWheeler as a property. Or instead of
		// boolean this also could be a enum denoting twoWheeler, cars, buses in different categories
		Vehicle (string &inumber, bool twoWheeler):number(inumber), isTwoWheeler(twoWheeler)
		{}

		string getNumber ()
		{
			return number;
		}

		bool getIsTwoWheeler ()
		{
			return isTwoWheeler;
		}
};

class ParkingSlot
{
	private:
		int id;
		bool isFree;
		Vehicle *vh;
		time_t parkingTime;
		int fee;
		int minFee;

	public:
		ParkingSlot (int uniqueId, int feePerHour, int minimumFee): id(uniqueId), isFree(true), fee(feePerHour), minFee (minimumFee)
		{}

		bool BookSlot (Vehicle *vh)
		{
			if (!isFree)
				return false;


			this->vh = vh;
			parkingTime = time(NULL);
			isFree = true;
			
			cout << "Booked the slot " << id << endl;
			return true;
		}

		void FreeSlot ()
		{
			isFree = true;
			// dont worry about vehicle and parkingtime
		}

		int getDuration ()
		{
			cout << "Got the duration";
		}

		int CalculateFee ()
		{
			cout << "Return the fee based on duration " << endl;
		}
};


class ParkingLot
{
	private:
		vector<ParkingSlot> carSlots;
		vector<ParkingSlot> bikeSlots;
	public:
		ParkingLot ()
		{
			cout << "Created the slots" << endl;
		}

		bool BookSlot (Vehicle *vh)
		{
			cout << "booking slot" << endl;
		}

		int GetParkingFree (Vehicle *vh)
		{
			cout << "Finding the slot.. " << endl;
		}

		bool PayAndFreeSlot (Vehicle *vh)
		{
			cout << "Found and free the slot.. " << endl;
		}
};

int 
main ()
{
}
