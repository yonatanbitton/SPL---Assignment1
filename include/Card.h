#ifndef CARD_H_
#define CARD_H_

#include <iostream>
using namespace std;

enum Shape {
	Club,
	Diamond,
	Heart,
	Spade
};

enum Figure {
	Jack,
	Queen,
	King,
	Ace
};

class Card {
private:
  Shape shape;
public:
  Card (Shape shape);
//  Card (const Card& otherCard);
//  Card& operator=(const Card& otherCard);
  virtual string toString() = 0; //Returns the string representation of the card "<value><shape>" exp: "12S" or "QD"
  virtual ~Card();
  virtual int getNumber() const =0;
  virtual Card* makeCard()=0;
  Shape getShape() const;
};

class FigureCard : public Card {
private:
	Figure figure;
	int value;
public:
	FigureCard(); // Defultive constructorE - member intialization list
	FigureCard (Shape shape , Figure figure);
        FigureCard(Card* otherFCard);
	virtual string toString() override; // MA OSIM IM ZE
	Figure getFigure()const;
	virtual ~FigureCard();
	virtual Card* makeCard();
	int getNumber() const;
};

class NumericCard : public Card {
private:
	int number;
public:
	NumericCard(); // LAMA TSARIH LE AHRIZ KAHA
	NumericCard  (Shape shape , int number);
        NumericCard(Card* otherNCard);
	virtual string toString() override; // MA OSIM IM ZE
	int getNumber() const;
	virtual Card* makeCard();
	virtual ~NumericCard();
};

#endif
