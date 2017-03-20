/*Alexandra Macedo 3/16/15
This program simulates a game of siete y medio where
a player plays against a dealer built into the program.
The player starts with 100 pesos and places a bet.
The Hand and Card class functions are called to generate
cards at random to add to a vector of cards to make up
the hands of the dealer and player. The contents and current
score of the players hand are displayed and the player is
asked whether or not they would like to draw another card
based on the score (repeated until they decline). After the
player is done hitting, the dealer automatically draws cards
until the total score of its hand is 5.5 or above. At this point,
a winner is declared depending on the scores of the two and the
player and dealer exchange money based on who wins. The hands
of the player and dealer are cleared for a new game. Multiple games
continue to be played until the player loses all of its money
(has 0 pesos) or the dealer loses a total of 900 pesos (-900 pesos).
A winner is declared overall. Additionally, contents of the player's
and dealer's hands, their scores, and the player's current amount
of money are displayed for each round in a text file created.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "cards.h"
using namespace std;

int main(){

	//An output file is created to store contents of each game
	ofstream fout;
	fout.open("gamelog.txt");

	//The player starts with 100 pesos and the dealer at 0
	int playerMoney = 100;
	int dealerMoney = 0;
	int bet = 0;
	int game = 1;

	//The player and dealer are constructed, as well as their empty hands
	Player player(playerMoney);
	Player dealer(dealerMoney);
	Hand playerHand;
	Hand dealerHand;

	/*New games are played until the player loses all money or the
	dealer loses 900 pesos*/
	while (player.get_money() > 0 && dealer.get_money() > -900){
		cout << "You have " << player.get_money() << ". Enter bet: ";
		cin >> bet;

		fout << "-----------------------------------------------\n\n";
		fout << "Game number: " << game << endl;
		fout << "Money left: $" << player.get_money() << endl;
		fout << "Bet: " << bet << endl << endl;

		while (player.get_money() < bet){
			cout << "Your don't have enough money for your bet!\n";
			cout << "Please enter a smaller bet: ";
			cin >> bet;
		}

		//player adds a card to its hand and its hand and score are displayed
		playerHand.draw_card();
		cout << "Your cards: \n";
		playerHand.printHand();
		cout << "Your total is: " << playerHand.sum();

		//player draws cards until they decline
		string response = "Y";
		while (playerHand.sum() <= 7.5 && (
			response == "Y" || response == "y" || response == "Yes" || response == "yes")){
			cout << " Do you want another card? (y/n) ";
			cin >> response;

			while (response != "Y" && response != "y" && response != "Yes" && response != "yes"
				&& response != "N" && response != "n" && response != "No" && response != "no"){
				cout << "Try again! Do you want another card? (y/n)";
				cin >> response;
			}

			if (response == "Y" || response == "y" || response == "Yes" || response == "yes"){
				playerHand.draw_card();
				cout << "New card: \n";
				playerHand.printNewCard();

				cout << "Your cards: \n";
				playerHand.printHand();
				cout << "Your total is: " << playerHand.sum();
			}
		}
		cout << endl;

		//displays player's hand and score to the output log file
		fout << "Your cards:\n";
		playerHand.printHandToFile(fout);
		fout << "Your total: " << playerHand.sum() << endl << endl;

		//the dealer takes a turn as long as the player didn't bust
		if (playerHand.sum() <= 7.5){
			dealerHand.draw_card();
			cout << "Dealer's cards: \n";
			dealerHand.printHand();
			cout << "The dealer's total is: " << dealerHand.sum()<< endl;

			//dealer draws cards until the score of the hand is 5.5 or more
			while (dealerHand.sum() < 5.5){
				dealerHand.draw_card();
				cout << "New card: \n";
				dealerHand.printNewCard();

				cout << "Dealer's cards: \n";
				dealerHand.printHand();
				cout << "Dealer's total is: " << dealerHand.sum()<< endl;
			}

			//dealer's hand and score are displayed to the output log file
			fout << "Dealer's cards:\n";
			dealerHand.printHandToFile(fout);
			fout << "Dealer's total: " << dealerHand.sum() << endl << endl;
		}

		//if player bust, no cards displayed for the dealer
		else{
			fout << "Dealer's cards:\n";
			fout << "Player bust. Dealer did not Draw.\n";
			fout << "Dealer's total: 0\n\n";
		}

		//determination of winner and exchange of money

		if (playerHand.sum() > 7.5){
			cout << "You lose " << bet;
			player.update_money(-bet);
			dealer.update_money(bet);
		}

		else if (dealerHand.sum() > 7.5){
			cout << "You win " << bet;
			player.update_money(bet);
			dealer.update_money(-bet);
		}

		else if (playerHand.sum() > dealerHand.sum()){
			cout << "You win " << bet;
			player.update_money(bet);
			dealer.update_money(-bet);
		}

		else if (playerHand.sum() < dealerHand.sum()){
			cout << "You lose " << bet;
			player.update_money(-bet);
			dealer.update_money(bet);
		}

		else if (playerHand.sum() == dealerHand.sum()){
			cout << "Push! You get your bet back.";
		}

		cout << endl<<endl;

		//player and dealer's hands are reset to empty vectors
		playerHand.reset_hand();
		dealerHand.reset_hand();

		game++;
	}

	fout << "-----------------------------------------------";

	//displays whether the player won or lost

	if (player.get_money() <= 0){
		cout << "Game over! You have 0. You lose.";
	}
	else if (dealer.get_money() <= 900){
		cout << "Game over! The dealer lost too much money. You win!";
	}

	cout << endl;
	fout.close();

	return 0;
}