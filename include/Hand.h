#ifndef HAND_H_
#define HAND_H_

#include <iostream>

#include "Card.h"
#include <vector>


using namespace std;

class Hand {
private:
	vector <Card*> HandVec;
public:
	Hand();
	Hand (const Hand& otherHand);
	Hand& operator=(const Hand& otherHand);
	virtual ~Hand();
	bool addCard(Card &card);
	bool removeCard(Card &card);
	int getNumberOfCards(); // Get the number of cards in hand
	string toString(); // Return a list of the cards, separated by space, in one line, in a sorted order, ex: "2S 5D 10H"
	void mySort();
	void clean();
	bool searchCard(Card &card);
	int MostCommonValue(int N);
	int LeastCommonValue(int N);
	int HighestValueAtHand(int N);
	int LowestValueAtHand(int N);
	const vector<Card*>& getHand() const;
	void checkReviia(Card& newCard);

};

#endif
