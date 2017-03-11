/*
 * Deck.cpp
 *
 *  Created on: Nov 14, 2016
 *      Author: bittoy
 */

#include "../include/Deck.h"
#include "../include/Card.h"
#include <string>
#include <iostream>
#include <vector>

Deck::Deck():DeckVec(){
}

Deck::Deck(vector <Card*> par_vec):DeckVec(par_vec){}
int Deck::getNumberOfCards(){
	return DeckVec.size();
}

// Copy constructor
Deck::Deck (const Deck& otherDeck):DeckVec(){
	if (this==&otherDeck)
		return;
	clean();
	for(unsigned int i=0; i<otherDeck.getDeck().size();i++){
		Card* newCard=otherDeck.getDeck()[i]->makeCard();
		DeckVec.push_back(newCard);
	}
}

// Copy assignment operator
Deck& Deck::operator=(const Deck& otherDeck){
	if (this==&otherDeck){
		return *this;
	}
	clean();
	for(unsigned int i=0; i<(otherDeck.getDeck()).size();i++){
		Card* newCard=otherDeck.getDeck()[i]->makeCard();
		DeckVec.push_back(newCard);
	}
	return *this;
}

// Destructor
Deck::~Deck() {
	for (unsigned int i=0; i< DeckVec.size(); i++)
		delete (DeckVec.at(i));
	DeckVec.clear();
}



void Deck::clean(){
	for(unsigned int i=0; i< DeckVec.size(); i++){
		delete(DeckVec[i]);
	}
	DeckVec.clear();
}

vector <Card*> Deck::getDeck() const{
	return this->DeckVec;
}



Card* Deck::fetchCard(){
	if (DeckVec.size()>0){
		Card *tempCard=DeckVec.front()->makeCard();
		delete (DeckVec[0]);
		DeckVec.erase (DeckVec.begin());
//		cout<< "the current deck is: " << toString() << endl;
		return tempCard;
	}
	else return 0;
}

string Deck::toString(){
	string deck_str("");
	for (unsigned int i=0; i<DeckVec.size(); i++)
		deck_str.append(DeckVec[i]->toString()+" ");
	return deck_str;
}



void Deck::addCard(Card* card){
	DeckVec.push_back(card);
}

//This function recieves strings of value and shape, and returns a pointer to a new card that was created.
Card* Deck::initCard(string value_str, string shape_str){
	Shape shape;
	Figure figure;
	Card* card;
	if (shape_str.at(0)=='C') shape=Club;
	if (shape_str.at(0)=='D') shape=Diamond;
	if (shape_str.at(0)=='H') shape=Heart;
	if (shape_str.at(0)=='S') shape=Spade;
	int value_int=atoi(value_str.c_str());
	if (value_int==0){ // So I know it's a figure card
		if (value_str.at(0)=='J') figure=Jack;
		if (value_str.at(0)=='Q') figure=Queen;
		if (value_str.at(0)=='K') figure=King;
		if (value_str.at(0)=='A') figure=Ace;
		card=new FigureCard(shape, figure);
	}
	else {
		card=new NumericCard(shape,value_int);
	}
	return card;
}

void Deck::initDeck(string input){
	string s = input;
	string delimiter (" ");
	size_t pos = 0;
	std::string token;
	while (s.at(s.size()-1)==' '){
		 s=s.substr(0, s.size()-1);
	}
	while ((pos = s.find(delimiter)) != std::string::npos) {
	    token = s.substr(0, pos);
	    string value_str=token.substr(0,token.size()-1);
	    string shape_str=token.substr(token.size()-1,1);
	    Card* c1=initCard(value_str, shape_str);
	    Deck::addCard(c1);
	    // delete (c1);
	    s.erase(0, pos + delimiter.length());
	}
	if(!(s.empty())){
		string value_str=s.substr(0,s.size()-1);
		string shape_str=s.substr(s.size()-1,1);
		Card* c1=initCard(value_str, shape_str);
		Deck::addCard(c1);
                // delete (c1);
//		cout << s << std::endl;
	}
}

void Deck::drawKcards(int k, vector<Card*>& asking){ // This function takes K cards from myDeck, and moves it the the asking vector
//	for (unsigned j=0; j<asking.size(); j++)
//		cout << "The asking[j] for j=" << j << " is " << asking[j]->toString() << endl;
//	cout << k << " is the K " << endl;
	if (k>0){
		for(int i=0; i<k; i++){
			if (DeckVec.size() >0){
//				cout << "BEFORE " << toString() << endl;
				Card* card=fetchCard();
//				cout << "AFTER " << toString() << endl;
//				cout << "The fetchCard is " << card->toString() << endl;
				asking.push_back(card);
//				cout << asking.at(asking.size()-1)->toString() << " is the toString of the Card Just entered " << endl;
			}
			}
		}
//	for (unsigned j=0; j<asking.size(); j++)
//		cout << "The asking[j] for j=" << j << " is " << asking[j]->toString() << endl;
}

//void Hand::drawKcards(int k, Deck deck){
//	if(this->HandVec.size()>0){
//		if (k!=0){
//			for(unsigned int i=0; i<k; i++){
//				if(deck.size()>0){
//					Card* toInsert=deck.fetchCard();
//					this.addCard(*toInsert);
//				}
//			}
//		}
//	}
//
//}



//int main(int argc, char **argv){
//	string s="KC QH 3D AH JH 2C 3S KS AS JS 3C KH AD QC JD QS 3H KD AC JC 2D 2H 2S QD ";
//	Card *c1 = new FigureCard(Heart , Jack);
//	Card *c2=new NumericCard( Club , 8);
//	Card *c3=new FigureCard(Spade , Ace);
//	Card *def_c4=new FigureCard();
//	Card *def_c5=new NumericCard();
//	vector <Card*> v1;
//	// v1.push_back(c1);
//	// cout << "IN THE MAIN to String " << c1->toString() << endl;
//	//	v1.push_back(c2);
//	//	v1.push_back(c3);
//	//	v1.push_back(def_c4);
//	//	v1.push_back(def_c5);
//	Deck d1=Deck(v1);
//	d1.initDeck(s);
//return 0;
//}
//}
//
//int main()
//{
//Card *c1 = new FigureCard(Heart , Jack);
//Card *c2=new NumericCard( Club , 8);
//Card *c3=new FigureCard(Spade , Ace);
//Card *def_c4=new FigureCard();
//Card *def_c5=new NumericCard();
//
//
//std::vector<Card*> myvector;
//
// // set some values to my wonderfull vector
//myvector.push_back(c1);
//myvector.push_back(c2);
//myvector.push_back(c3);
//myvector.push_back(def_c4);
//myvector.push_back(def_c5);
// // erase the 1st element
//// myvector.erase (myvector.begin());
//cout << "myvector contains: ";
// for (unsigned i=0; i<myvector.size(); ++i)
//   std::cout << ' ' << myvector[i]->toString() << " ";
// std::cout << '\n';
//
// Deck d1=Deck(myvector);
//cout << d1.toString() << " " << endl;
//Card* tmpCard = d1.fetchCard();
//cout << "The first card is " << tmpCard->toString() << endl;
//cout << "And now ! " << d1.toString() << " " << endl;
//
//cout << "num of cards is:" << d1.getNumberOfCards() << " " << endl ;
//
//
//
//return 0;
//}
