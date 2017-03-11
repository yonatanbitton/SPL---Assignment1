#ifndef DECK_H_
#define DECK_H_

#include <iostream>
#include "Card.h"
#include <vector>


using namespace std;

class Deck {
private:
	// Declare here the collection of "Card *" of the deck
	vector <Card*> DeckVec;
public:
	Deck();
	Deck(vector <Card*> par_vec);
	Deck (const Deck& otherDeck);
	Deck& operator=(const Deck& otherDeck);
	void clean();
	Card* fetchCard();   //Returns the top card of the deck and remove it from the deck
	string toString(); // Return the cards in top-to-bottom order in a single line, cards are separated by a space ex: "12S QD AS 3H"
	int getNumberOfCards();// Get the number of cards in the deck
	virtual ~Deck();
	void addCard(Card* card);
	Card* initCard(string value, string shape);
	void initDeck(string input);
	void drawKcards(int k, vector<Card*>& asking);
	vector <Card*> getDeck() const;

};

#endif
