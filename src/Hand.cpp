/*
 * Hand.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: bittoy
 */

#include <iostream>
using namespace std;
#include <string> 
#include <algorithm>
#include "../include/Hand.h"


Hand::Hand():HandVec(){}


// Copy constructor
Hand::Hand (const Hand& otherHand):HandVec(){
	if (this==&otherHand)
		return;
	clean();
	for(unsigned int i=0; i<otherHand.getHand().size();i++){
		Card* newCard=otherHand.getHand()[i]->makeCard();
		HandVec.push_back(newCard);
	}
}

// Copy assignment operator
Hand& Hand::operator=(const Hand& otherHand){
	if (this==&otherHand){
		return *this;
	}
	clean();
	for(unsigned int i=0; i<(otherHand.getHand()).size();i++){
		Card* newCard=otherHand.getHand()[i]->makeCard();
		HandVec.push_back(newCard);
	}
	return *this;
}

// Destructor
Hand::~Hand() {
	for (unsigned int i=0; i< HandVec.size(); i++)
		delete (HandVec.at(i));
	HandVec.clear();
}

void Hand::clean(){
	for(unsigned int i=0; i< HandVec.size(); i++){
		delete(HandVec[i]);
	}
	HandVec.clear();
}


	// This function searches for the given card, and returns it's index on the vector. If not found, return -1
	bool Hand::searchCard(Card &card){
		for (unsigned i=0; i<HandVec.size(); i++){
			if (HandVec[i]->getShape()==card.getShape() && HandVec[i]->getNumber()==card.getNumber()) return true;
		}
		return false;
	}


	bool Hand::addCard(Card &card){
		int i=Hand::searchCard(card);
		if (i==0) {
			Card* newCard=card.makeCard();
			HandVec.push_back(newCard);
			// cout << "We pushed into the handVec the Card " << newCard->toString() << endl;
			checkReviia(*newCard);
			return true;
		}
		else return false;
	}


	void Hand::checkReviia(Card& newCard){
		int countCheck=0;
		for (unsigned int i=0; i<HandVec.size();i++){
			if (HandVec[i]->getNumber()==newCard.getNumber() && HandVec[i]->getShape()!=newCard.getShape())
				countCheck++;
		}
		if(countCheck==3){
			for (unsigned int j=0; j<HandVec.size();j++){
						if (HandVec[j]->getNumber()==newCard.getNumber() && HandVec[j]->getShape()!=newCard.getShape()){
//							cout<< "The card to remove is: "<<HandVec[j]->toString()<<endl;
							removeCard(*HandVec[j]);
							j--;
						}
					}
			removeCard(newCard);
		}
	}

	bool Hand::removeCard(Card& card){
		//
		if (searchCard(card)) {
			for (unsigned k=0; k<HandVec.size(); k++){
				if (HandVec[k]->toString().compare(card.toString())==0) {
					delete(HandVec[k]); // The only place that calls removeCard is Player:PlayerTypes, where there is no deletion!
					HandVec.erase (HandVec.begin()+k);
					break;
				}
			}
			return true;
		}
		else return false;
	}

	int Hand::getNumberOfCards(){ // Get the number of cards in hand
		return HandVec.size();
	}
	string Hand::toString(){ // Return a list of the cards, separated by space, in one line, in a sorted order, ex: "2S 5D 10H"
		mySort();
		string deck_str="";
		for (unsigned int i=0; i<HandVec.size(); i++)
			deck_str = deck_str+HandVec[i]->toString() + " ";
		return deck_str;
	}

	bool myComperator(Card *c1, Card *c2){
		if (c1->getNumber()==c2->getNumber()) {
			string shape1=c1->toString();
			string shape2=c2->toString();
			char char1=shape1.at(shape1.size()-1);
			char char2=shape2.at(shape1.size()-1);
			if (char1 < char2) return true;
			else return false;

		}
		else if ((c1->getNumber()<0 && c2->getNumber()<0) || (c1->getNumber()>0 && c2->getNumber()>0)) return c1->getNumber()<c2->getNumber();
		else if (c1->getNumber()<0 && c2->getNumber()>0) return false;
		else if (c1->getNumber()>0 && c2->getNumber()<0) return true;
		return false;
	}


	void Hand::mySort(){
		std::sort(HandVec.begin(), HandVec.end(), myComperator);
	}

	int Hand::MostCommonValue(int N){
		vector <int> B (N+3,0); //the range is 2..n+ 4 figures
		for(unsigned int i=0; i<HandVec.size();i++){
			int currentNumber=HandVec[i]->getNumber();
			if (currentNumber==-4) currentNumber=N+1;
			if (currentNumber==-3) currentNumber=N+2;
			if (currentNumber==-2) currentNumber=N+3;
			if (currentNumber==-1) currentNumber=N+4;
			B[currentNumber-2]++;
		}
		int index=0;
		int num=0;
		for (unsigned int j=0; j<B.size(); j++){
			if (B[j]>=num){
				num=B[j];
				index=j;
			}
		}
		if (index<=N-2) {
			return index+2;
		}
		else {
			int newIndex=index+2;
			if (newIndex-N==1) return -4;
			if (newIndex-N==2) return -3;
			if (newIndex-N==3) return -2;
			if (newIndex-N==4) return -1;

		return newIndex;
	}
	}


	int Hand::LeastCommonValue(int N){
		vector <int> B (N+3,0); //the range is 2..n+ 4 figures
		for(unsigned int i=0; i<HandVec.size();i++){
			int currentNumber=HandVec[i]->getNumber();
				if (currentNumber==-4) currentNumber=N+1;
				if (currentNumber==-3) currentNumber=N+2;
				if (currentNumber==-2) currentNumber=N+3;
				if (currentNumber==-1) currentNumber=N+4;
			B[currentNumber-2]++;

		}
		int index=0;
		int num=N+5;
		for (unsigned int j=0; j<B.size(); j++){
//			cout << "j is " << j << endl;
			if (B[j]<num && B[j]>0){
				num=B[j];
				index=j;
			}

		}
		if (index<=N-2) {
			return index+2;
		}
		else {
			int newIndex=index+2;
			if (newIndex-N==1) return -4;
			if (newIndex-N==2) return -3;
			if (newIndex-N==3) return -2;
			if (newIndex-N==4) return -1;
		return newIndex;
	}
	}



	int Hand::HighestValueAtHand(int N) {
		int MAX=0;
		for (unsigned int i=0; i<HandVec.size(); i++){
			int currentNum=HandVec[i]->getNumber();
			if (currentNum>0){
				if (currentNum>MAX)
					MAX=currentNum;
			}
			else if (currentNum<0){
				switch(currentNum){
					case -4: currentNum=N+1; break;
					case -3: currentNum=N+2; break;
					case -2: currentNum=N+3; break;
					case -1: currentNum=N+4; break;
				}
				if (currentNum>MAX)
				MAX=currentNum;
			}
		}
		if (MAX<=N)
			return MAX;
		else {
			if (MAX==N+1) MAX=-4;
			if (MAX==N+2) MAX=-3;
			if (MAX==N+3) MAX=-2;
			if (MAX==N+4) MAX=-1;
		}
		return MAX;
	}


	int Hand::LowestValueAtHand(int N) {
		int MIN=N+5;
		for (unsigned int i=0; i<HandVec.size(); i++){
			int currentNum=HandVec[i]->getNumber();
			if (currentNum>0){
				if (currentNum<MIN)
					MIN=currentNum;
			}
			else if (currentNum<0){
				switch(currentNum){
					case -4: currentNum=N+1; break;
					case -3: currentNum=N+2; break;
					case -2: currentNum=N+3; break;
					case -1: currentNum=N+4; break;
				}
				if (currentNum<MIN)
				MIN=currentNum;
			}
		}
		if (MIN<=N)
					return MIN;
				else {
					if (MIN==N+1) MIN=-4;
					if (MIN==N+2) MIN=-3;
					if (MIN==N+3) MIN=-2;
					if (MIN==N+4) MIN=-1;
				}
				return MIN;
	}

	const vector<Card*>& Hand::getHand() const{
		return HandVec;
	}


