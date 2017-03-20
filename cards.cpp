/* *************************************
Alexandra Macedo 3/16/15

Implementation of the Hand, Card, and
Player classes.
************************************* */

#include "cards.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

/* *************************************************
Card class
************************************************* */

/*
Default constructor for the Card class.
It could give repeated cards. This is OK.
Most variations of Blackjack are played with
several decks of cards at the same time.
*/
Card::Card(){
	int r = 1 + rand() % 4;
	switch (r) {
	case 1: suit = OROS; break;
	case 2: suit = COPAS; break;
	case 3: suit = ESPADAS; break;
	case 4: suit = BASTOS; break;
	default: break;
	}

	r = 1 + rand() % 10;
	switch (r) {
	case  1: rank = AS; break;
	case  2: rank = DOS; break;
	case  3: rank = TRES; break;
	case  4: rank = CUATRO; break;
	case  5: rank = CINCO; break;
	case  6: rank = SEIS; break;
	case  7: rank = SIETE; break;
	case  8: rank = SOTA; break;
	case  9: rank = CABALLO; break;
	case 10: rank = REY; break;
	default: break;
	}
}

// Accessor: returns a string with the suit of the card in Spanish 
string Card::get_spanish_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "oros";
		break;
	case COPAS:
		suitName = "copas";
		break;
	case ESPADAS:
		suitName = "espadas";
		break;
	case BASTOS:
		suitName = "bastos";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in Spanish 
string Card::get_spanish_rank() const {
	string rankName;
	switch (rank) {
	case AS:
		rankName = "As";
		break;
	case DOS:
		rankName = "Dos";
		break;
	case TRES:
		rankName = "Tres";
		break;
	case CUATRO:
		rankName = "Cuatro";
		break;
	case CINCO:
		rankName = "Cinco";
		break;
	case SEIS:
		rankName = "Seis";
		break;
	case SIETE:
		rankName = "Siete";
		break;
	case SOTA:
		rankName = "Sota";
		break;
	case CABALLO:
		rankName = "Caballo";
		break;
	case REY:
		rankName = "Rey";
		break;
	default: break;
	}
	return rankName;
}



// Accessor: returns a string with the suit of the card in English 
// This is just a stub! Modify it to your liking.
string Card::get_english_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "golds";
		break;
	case COPAS:
		suitName = "cups";
		break;
	case ESPADAS:
		suitName = "swords";
		break;
	case BASTOS:
		suitName = "clubs";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in English 
// This is just a stub! Modify it to your liking.
string Card::get_english_rank() const {
	string rankName;
	switch (rank) {
	case AS:
		rankName = "Ace";
		break;
	case DOS:
		rankName = "2";
		break;
	case TRES:
		rankName = "3";
		break;
	case CUATRO:
		rankName = "4";
		break;
	case CINCO:
		rankName = "5";
		break;
	case SEIS:
		rankName = "6";
		break;
	case SIETE:
		rankName = "7";
		break;
	case SOTA:
		rankName = "Night";
		break;
	case CABALLO:
		rankName = "Horse";
		break;
	case REY:
		rankName = "King";
		break;
	default: break;
	}
	return rankName;
}



// Assigns a numerical value to card based on rank.
// AS=1, DOS=2, ..., SIETE=7, SOTA=10, CABALLO=11, REY=12
int Card::get_rank() const {
	return static_cast<int>(rank)+1;
}

// Comparison operator for cards
// Returns TRUE if card1 < card2
bool Card::operator < (Card card2) const {
	return rank < card2.rank;
}



/* *************************************************
Hand class
************************************************* */

//Constructor
// A vector of Cards
Hand::Hand(){
	vector<Card>hand(0);
}

//Adds a random card to a player's hand
void Hand::draw_card(){
	Card newCard;
	hand.push_back(newCard);
}

//Resets a player's hand to an empty vector
void Hand::reset_hand(){
	hand.resize(0);
}

//Displays the contents of a player's hand to the console
void Hand::printHand(){
	for (size_t i = 0; i < hand.size(); i++){
		cout << setw(5) << left << " ";
		cout << setw(20) << left<< hand[i].get_spanish_rank()
			 + " de " + hand[i].get_spanish_suit();
		cout << setw(20) << left << "(" + hand[i].get_english_rank()
			+ " of " + hand[i].get_english_suit() + ")" << endl;
	}
}

//Dsiplays the most recently drawn card
void Hand::printNewCard(){
	cout << setw(5) << left << " ";
	cout << setw(20) << left<<hand[hand.size() - 1].get_spanish_rank()
		+ " de " + hand[hand.size()-1].get_spanish_suit();
	cout << setw(20) << left << "(" + hand[hand.size()-1].get_english_rank()
		+ " of " + hand[hand.size()-1].get_english_suit() + ")" << endl;
}

//Displays the contents of a player's hand to an output file
void Hand::printHandToFile(ofstream& fout){
	for (size_t i = 0; i < hand.size(); i++){
		fout << setw(5) << left << " ";
		fout << setw(20) << left << hand[i].get_spanish_rank()
			+ " de " + hand[i].get_spanish_suit();
		fout << setw(20) << left << "(" + hand[i].get_english_rank()
			+ " of " + hand[i].get_english_suit() + ")" << endl;
	}
}

//Returns the sum of a player's hand
double Hand::sum(){
	double sum = 0.0;
	for (size_t i = 0; i < hand.size(); i++){
		value=hand[i].get_rank();
		if (value >= 1 && value <= 7){
			sum += value;
		}
		else if (value >=10&&value<=12){
			sum += .5;
		}
	}
	return sum;
}

/* *************************************************
Player class
************************************************* */

// Constructor. 
// Assigns initial amount of money
Player::Player(int m){
	money = m;
}

//Returns the current amount of money a player has
int Player::get_money() const{
	return money;
}

//Updates a player's total money based on bets
//won or lost
void Player::update_money(int bet){
	money += bet;
}