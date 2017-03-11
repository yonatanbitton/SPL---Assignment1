

#include <iostream>
#include <string>
#include <sstream>

using namespace std;
#include "../include/Card.h"

	// Card
	Card::Card(Shape par_shape):shape(par_shape){}

//	Card (const Card& otherCard) :shape(otherCard.getShape()), {}
//	Card& operator=(const Card& otherCard);

  	string Card::toString(){
  		string shape_str;
  		switch (shape){
  			case Club : shape_str = "C"; break;
  			case Diamond : shape_str = "D"; break;
  			case Heart : shape_str="H"; break;
  			case Spade : shape_str="S"; break;
  		}
  		return shape_str;
  	} //Returns the string representation of the card "<value><shape>" exp: "12S" or "QD"

  	Card::~Card() {

  	}

    Shape Card::getShape() const{
    	return shape;
    }


  	// FigureCard
	FigureCard::FigureCard():Card(Club),  figure(Jack) , value(-4){} // Defultive constructorE - member intialization list
	FigureCard::FigureCard(Shape shape , Figure pFigure):Card(shape), figure(pFigure) ,value(0){
	int cardValue;
		switch(figure)
		{
			case Jack : cardValue = -4; break;
			case Queen : cardValue = -3; break;
			case King : cardValue=-2; break;
			case Ace : cardValue=-1; break;
		}
		this->value=cardValue;
	}
	string FigureCard::toString(){
		Figure f = figure;
		string figureString;
		string shapeString = Card::toString();
		switch(f)
		{
		case Jack : figureString="J"; break;
		case Queen : figureString="Q"; break;
		case King : figureString="K"; break;
		case Ace : figureString="A"; break;
		}
		return figureString+shapeString;
	}
	Figure FigureCard::getFigure()const{
		return figure;
	}
	FigureCard::~FigureCard(){}
	int FigureCard::getNumber() const{
		return value;
	}
	Card* FigureCard::makeCard(){
		Card* c = new FigureCard(*this);
		return c;
	}
	
	// NumericCard
	NumericCard::NumericCard(): Card(Club), number(2){}; // Defultive constructorE - member intialization list
	NumericCard::NumericCard( Shape shape , int pNumber):Card(shape),number(pNumber){
	}
	string NumericCard::toString(){
		string shapeString = Card::toString();
		std::ostringstream oss;
		oss<< number;
		return oss.str() + shapeString;
	}

	int NumericCard::getNumber() const{
		return number;
	}
	NumericCard::~NumericCard(){}

	Card* NumericCard::makeCard(){
			Card* c = new NumericCard(*this);
			return c;
		}
