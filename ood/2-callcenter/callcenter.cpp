#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <list>
#include <memory>

using namespace std;

class Call 
{
	public:
		enum CallStatus {
			New,
			Responded,
			Escalated	
		};

		Call (string &sName):name (sName), status(New)
		{
		}

		void setStatus (CallStatus stat)
		{
			status = stat;
		}

		CallStatus getStatus () const
		{
			return status;
		}

		string getStatusString (CallStatus status)
		{
			switch (status)
			{
				case New:
					return string ("New");
				case Responded:
					return string ("Responded");
				case Escalated:
					return string ("Escalated");
				default:
					return string ("");
			}
		}

	private:
		string name;
		CallStatus status;
};

class Employee
{
	public:
		enum Status
		{
			Free,
			Busy,
			Resting
		};

		Employee (string &sName):name(sName)
		{
		}

		virtual void takeCall (Call &call) = 0;
	
		// Never override non-virtual functions	
		void setStatus (Status stat)
		{
			stat = status;	
		}
		
		Status getStatus  () const
		{
			return status;
		}

	protected:
		string name;

	private:
		Status status;
		// In future i could have a CallStat to note the statistics per employee
		// to monitor the performance
};

class Respondent: public Employee
{
	public:
		Respondent (string &sName):Employee(sName) {}

		void takeCall (Call &call)
		{
			cout << "Respondent: " << name << " is responding to the call" << endl;

			if (rand () % 2)
				call.setStatus (Call::Escalated);
			else
				call.setStatus (Call::Responded);
			
			cout << "Call is " << call.getStatusString (call.getStatus()) << endl;
		}
};

class Manager: public Employee
{
	public:
		Manager (string &sName):Employee(sName) {}

		void takeCall (Call &call)
		{
			cout << "Manager: " << name << "is responding to the call" << endl;

			if (rand () % 2)
				call.setStatus (Call::Escalated);
			else
				call.setStatus (Call::Responded);
			
			cout << "Call is " << call.getStatusString (call.getStatus()) << endl;
		}

};

class Director: public Employee
{
	public:
		Director (string &sName):Employee(sName) {}

		void takeCall (Call &call)
		{
			cout << "Director: " << name << "is responding to the call" << endl;

			call.setStatus (Call::Responded);
			cout << "Call is " << call.getStatusString (call.getStatus()) << endl;
		}
};

class CallConnector
{
	public:
		CallConnector () 
		{
		}
		
		void init ()
		{
			/* Create Respondents */
			for (int i =0 ; i < 100; i++)
			{
				string name = "Respondent" + to_string (i);
				shared_ptr<Employee> sPtr (new Respondent (name));
				respondents.push_back (sPtr);
			}

			/* Create Managers */
			for (int i = 0; i < 20; i++)
			{
				string name = "Manager" + to_string (i);
				shared_ptr<Employee> sPtr = make_shared<Manager>(name);
				managers.push_back (sPtr);
			}

			/* Create Directors */
			for (int i = 0; i < 2; i++)
			{
				string name = "Director" + to_string (i);
				shared_ptr<Employee> sPtr = make_shared<Director>(name);
				directors.push_back (sPtr);
			}
		}

		void dispatchCall (Call &call)
		{
			shared_ptr<Employee> emp = pickFreeEmployee (respondents);
			if (emp != nullptr)
				emp->takeCall (call);
			else
				return;// Log error or wait

			if(call.getStatus () == Call::Responded)
				return;
			// assert Call not in New status

			emp = pickFreeEmployee (managers);
			if (emp != nullptr)
				emp->takeCall (call);
			else
				return;// Log error or wait
			
			if(call.getStatus () == Call::Responded)
				return;

			emp = pickFreeEmployee (directors);
			if (emp != nullptr)
				emp->takeCall (call);
			else
				return;// Log error or wait

			return;
		}

	private:
		
		shared_ptr<Employee> pickFreeEmployee  (list<shared_ptr<Employee>> employee_list)
		{
			for (auto i : employee_list)
			{
				if (i->getStatus () == Employee::Free)
					return i;
			}

			return nullptr;
		}

		// Note: If there is a org hierarchy such as a set of employees will have a single manager,
		// Respondent class can keep a reference to a manager and manager->Director, creating a tree like structure
		// and this class would then just have a list of respondents
		list<shared_ptr <Employee> > respondents;
		list<shared_ptr <Employee> > managers;
		list<shared_ptr <Employee> > directors;
};

int
main (int argc, char *argv[])
{
	srand (time(NULL));

	CallConnector con;
	string caller = "chen";
	Call cal(caller);

	con.init ();
	con.dispatchCall (cal);

	return 0;
}
