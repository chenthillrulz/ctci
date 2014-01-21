#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <typeinfo>

using namespace std;

// Interfaces
class ICard
{
	public:
		virtual int getValue () const = 0;
		virtual ~ICard (){}
};

class ICardDeck 
{
	public:
		virtual bool init () = 0;
		virtual bool shuffle () = 0;
		virtual shared_ptr <ICard> getCard () = 0;
		virtual ~ICardDeck (){}
};

class IPlayer
{
	public:
		virtual bool init () = 0;
		virtual void pickCard (ICardDeck &) = 0;
		virtual int totalValue () = 0;
		virtual bool isBusted () = 0;
		virtual ~IPlayer () {}
};

class IGame
{
	public:
		virtual bool init () = 0;
		// Consider there only one player and dealer for starters
		// virtual bool addPlayer (IPlayer &player) = 0;
		virtual bool addDeck (shared_ptr <ICardDeck> sptrDdeck) = 0;
		virtual bool play () = 0;
		virtual void displayResult () = 0;
		virtual ~IGame () {}
};

// BlackJack implementation
class BJCard : public ICard
{
	protected:
		int val;
		string name;
	public:
		enum FaceCards {
			King,
			Queen,
			Jack,
			Last
		};

		BJCard ():val(-1) {}
		BJCard (int iValue, string sName):val(iValue),name(sName) 
		{}

		BJCard (const BJCard &copy)
		{
			val = copy.val;
			name = copy.name;
		}

		BJCard & operator= (const BJCard toCopy)
		{
			val = toCopy.val;
			name = toCopy.name;
			
			return *this;
		}

		void setVal (int iValue) 
		{
			val = iValue;
		}

		void setName (string &sName)
		{
			name = sName;
		}

		int getValue () const 
		{
			return val;
		}
		
		static string getFaceName (FaceCards fc) 
		{
			switch (fc) {
				case King:
					return "king";
				case Queen:
					return "queen";
				case Jack:
					return "jack";
				default:
					return "";
			}
		}
		
		~BJCard () {}

};

class AceCard: public BJCard
{
	public:
		AceCard (const string &flower) 
		{
			name = flower + " Ace";
		}

		AceCard (const AceCard &copy)
		{
			val = copy.val;
			name = copy.name;
		}

		AceCard & operator= (const AceCard toCopy)
		{
			val = toCopy.val;
			name = toCopy.name;
			
			return *this;
		}

		int getValue () const
		{
			return 1;	
		}

		int getMaxValue ()
		{
			return 11;
		}
		~AceCard () {}
};

class BJCardDeck : public ICardDeck
{
	private:
		vector<shared_ptr <ICard> > deck;

		string getFlower (int i) 
		{
			switch (i) {
				case 0:
					return "Clubs";
				case 1:
					return "Diamonds";
				case 2:
					return "Hearts";
				case 3:	
					return "Spades";
				default:
					return "";
			}	
		}
	public:
		BJCardDeck ()
		{deck.reserve (52);}

		bool init () 
		{
			// four flowers
			for (int i = 0; i < 4; i++) {
				string flower = getFlower (i);	

				// A to 10
				for (int j = 1; j < 11; j++) {
					if (j == 1) 
					{
						shared_ptr<ICard> ptrCard(new AceCard (flower));
						deck.push_back (ptrCard);
					} else 
					{
						string name = flower + " " + to_string (j);
						
						shared_ptr<ICard> ptrCard(new BJCard (j, name)); 
						deck.push_back (ptrCard);
					}

				}
				
				// Face cards
				for (int i = BJCard::FaceCards::King; i < BJCard::FaceCards::Last; i++) {
					string name = flower + " " + BJCard::getFaceName (static_cast<BJCard::FaceCards> (i));
					// All face cards have value 10	
					shared_ptr<BJCard> ptrCard(new BJCard (10, name));
					deck.push_back (ptrCard);
				}
			}

			cout << "Deck initialized with " << deck.size () << " cards" << endl;
		}

		bool shuffle ()
		{
			for (int i = 0; i < 52; i++) {
				int sw = rand () % 51;
				swap (deck[i], deck [sw]);
			}
			cout << "Card Deck shuffled " << endl;
		}

		shared_ptr<ICard> getCard ()
		{
			if (!deck.empty ())
			{
				auto pCard =  deck.back ();
				deck.pop_back ();

				return pCard;
			}
			return NULL;
		}
		
		~BJCardDeck () {}

		friend ostream & operator<< (ostream &, BJCardDeck &deck);
};

ostream & operator<< (ostream &out, BJCardDeck &cdeck)
{
	out << "Iterating through the card deck \n";
	for (auto i : cdeck.deck)
	{
		out << i->getValue () << " ";
		//out << typeid(i).name () << " \n";
	}
	out << endl;

	return out;
}

class BJPlayer : public IPlayer
{
	private:
		vector < shared_ptr<ICard> > cards;
		string name;
	public:
		BJPlayer (string sName):name (sName) {}

		bool init ()
		{
		}

		void pickCard (ICardDeck &deck)
		{
			auto card = deck.getCard ();
			cards.push_back (card);

			cout << name << " Picked up the card " << card->getValue () << endl;
		}

		int totalValue ()
		{
			int total = 0;
			int numAces = 0;

			for (auto i : cards) {
				if (dynamic_pointer_cast<AceCard>(i))
					numAces++;

				total += i->getValue ();
			}

			if (numAces == 1 && total <= 11)
				total += 10; // Ace value becomes 11, since 1 is already counted, just added 10
			// Ideally we should have used the AceCard->getMaxValue function for this purpose

			return total;
		}

		// Could be optimized by caching the totalValue and invalidating it
		// when a player picks up a card
		bool isBusted ()
		{
			if (totalValue () > 21)
				return true;
			else 
				return false;
		}
};

// Consider there is only one player and a dealer in the game
class BJGame : public IGame
{
		private:
			vector < shared_ptr<ICardDeck > > sptrDecks;
			const int rounds = 26;
			BJPlayer dealer, player;
		public:
		
		BJGame ():dealer ("Dealer"), player ("chen") {}
			
		bool init ()
		{
			dealer.init ();
			player.init ();
		}
		
		// Consider there only one player and dealer for starters
		// virtual bool addPlayer (IPlayer &player) = 0;
		bool addDeck (shared_ptr<ICardDeck> sptrDeck) 
		{
			sptrDecks.push_back (sptrDeck);

			return true;
		}
		bool play ()
		{
			if (sptrDecks.empty ())
				return false;

			for (int i = 0; i < rounds; i++) 
			{
				cout << "\nRound " << i+1 << endl;
				if (player.totalValue () == 21 || dealer.totalValue () == 21)
					return true;

				if (dealer.isBusted () || player.isBusted ())
					return true;
				
				// Picks only from first deck, we could increase the players
				// and allow picking up from different decks
				dealer.pickCard (*(sptrDecks[0]));
				player.pickCard (*(sptrDecks[0]));
			}

			return false;
		}
		
		void displayResult ()
		{
			int playerTotal = player.totalValue ();
			int dealerTotal = dealer.totalValue ();

			if ((playerTotal == 21 && dealerTotal == 21) || 
					(playerTotal > 21 && dealerTotal > 21))
				cout << "Match ends in a draw" << endl;

			if (playerTotal <= 21)
				cout << "Player wins!! " << endl;
			else
				cout << "Dealer wins :( " << endl;

			cout << "Player's Total - " << playerTotal << endl;
			cout << "Dealer's Total - " << dealerTotal << endl;
		}

};

int
main ()
{
	shared_ptr<BJCardDeck> bcDeck = shared_ptr <BJCardDeck> (new BJCardDeck ());

	srand(time(NULL));
	
	bcDeck->init ();
	bcDeck->shuffle ();
	cout << *bcDeck;

	auto game = shared_ptr<IGame> (new BJGame ());
	game->addDeck (bcDeck);
	game->init ();
	game->play ();
	game->displayResult ();

	cout << endl;

	return 0;	
}
