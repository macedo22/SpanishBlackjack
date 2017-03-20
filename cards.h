/* *************************************
Alexandra Macedo 3/16/15

Interface for a card, hand, and player
class to implement to simulate card games.
************************************* */

#include <string>
#include <vector>
#include <fstream>

#ifndef CARDS_H
#define CARDS_H

using namespace std;

enum suit_t { OROS, COPAS, ESPADAS, BASTOS };

/*
The values for this type start at 0 and increase by one
afterwards until they get to SIETE.
The rank reported by the function Card::get_rank() below is
the value listed here plus one.
E.g:
The rank of AS is reported as    static_cast<int>(AS) + 1   = 0 + 1 =  1
The rank of SOTA is reported as  static_cast<int>(SOTA) + 1 = 9 + 1 = 10
*/
enum rank_t { AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA = 9, CABALLO = 10, REY = 11 };

/***************************************
Interface for a card class. Constructs
cards with sutis and ranks at random and
includes accessors to report them.
***************************************/

class Card {
public:
	// Constructor assigns random rank & suit to card.
	Card();

	// Accessors 
	string get_spanish_suit() const;
	string get_spanish_rank() const;

	/*
	These are the only functions you'll need to code
	for this class. See the implementations of the two
	functions above to get an idea of how to proceed.
	*/
	string get_english_suit() const;
	string get_english_rank() const;

	// Converts card rank to number.
	// The possible returns are: 1, 2, 3, 4, 5, 6, 7, 10, 11 and 12
	int get_rank() const;

	// Compare rank of two cards. E.g: Eight<Jack is true.
	// Assume Ace is always 1. 
	// Useful if you want to sort the cards.
	bool operator < (Card card2) const;

private:
	suit_t suit;
	rank_t rank;
};

/***************************************
Interface for a hand class. Constructs
a hand composed of a vector of cards,
resets a hand, and displays a hand to the
console and output file as well as a
newly drawn card to the console.
***************************************/

class Hand {
public:
	//Constructor
	// A vector of Cards
	Hand();

	//Accessors

	//Adds a random card to a player's hand
	void draw_card();

	//Resets a player's hand to an empty vector
	void reset_hand();

	//Displays the contents of a player's hand to the console
	void printHand();

	//Dsiplays the most recently drawn card
	void printNewCard();

	//Displays the contents of a player's hand to an output file
	void printHandToFile(ofstream& fout);

	//Returns the sum of a player's hand
	double sum();

private:
	vector < Card >hand ;
	double value;
};

/***************************************
Interface for a player class. Constructs
a player with a starting amount of money.
Includes fucntions to access the current
money or update it based on bets made.
***************************************/


class Player {
public:
	// Constructor. 
	// Assigns initial amount of money
	Player(int m);

	//Accessor
	//Returns the current amount of money a player has
	int get_money() const;

	//Mutator
	//Updates a player's total money based on bets
	//won or lost
	void update_money(int bet);

private:
	int money;
};

#endif