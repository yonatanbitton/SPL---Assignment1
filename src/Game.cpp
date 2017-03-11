/*
 * Game.cpp
 *
 *  Created on: Nov 20, 2016
 *      Author: bittoy
 */

#include "../include/Game.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


Game::Game(char* configurationFile):players(), winners(), deck(), initState(), verbal(1), turnsCounter(1), N(), finished(false){
	vector <string>* lines = readFile(configurationFile);
	verbal=atoi(lines->at(0).c_str());
	deck.initDeck(lines->at(2));
	int playerIndex=0;
	for (unsigned int i=3; i<lines->size(); i++){
	//	string curr = lines->at(i);
			createPlayer(lines->at(i), playerIndex);
			playerIndex++;
	}
	delete lines;
	N=deck.getNumberOfCards()/4-3;
}

vector <string>* Game::readFile(char* configurationFile) {
	fstream myFile;
	myFile.open(configurationFile);
	vector<string>* lines = new vector <string>();
	//for(unsigned int i=0;i<(*lines).size();i++)
	//	cout<<(*(*lines)[i])<< endl;
	string currentLine;
//	getline(myFile, currentLine);
//	cout << "Before the while , current line is " << currentLine << endl;

	while (getline(myFile, currentLine)){
		if ((!currentLine.size()==0) && (currentLine.at(0) !='#') && (currentLine.at(0) !=' ') ){
			lines->push_back(currentLine);
		}
	}
	return lines;
}


// Copy constructor
Game::Game (const Game& otherGame): players(), winners(), deck(), initState(), verbal(otherGame.getVerbal()), turnsCounter(otherGame.getTurnsCounter()), N(otherGame.getN()), finished(otherGame.getFinished()){
	for(unsigned int i=0; i<otherGame.getPlayers().size();i++){
		Player* newPlayer = otherGame.getPlayers()[i]->makePlayer();
	//	cout << "The " << i << " Player to push is " << newPlayer->toString() << endl;
		players.push_back(newPlayer);
	}
	deck=otherGame.deck; // Uses the copy assignment operator of Deck
	for(unsigned int i=0; i<otherGame.winners.size();i++){
			Player* newPlayer = otherGame.winners[i]->makePlayer(); // Uses the copy assignment operator of player
			cout << "The " << i << " Player to push is " << newPlayer->toString() << endl;
			winners.push_back(newPlayer);
	}
}

// Copy assignment operator
Game& Game::operator=(const Game& otherGame){
	//cout << "Im in the operator=" << endl;
	if (this==&otherGame){ // Maybe if (&*this==&otherGame) ?
		return *this;
	}
	//cout << "Im not myself" << endl;
	clean();
	//cout << "Im clean " << endl;
	this->verbal=otherGame.getVerbal();
	this->turnsCounter=otherGame.getTurnsCounter();
	this->N=otherGame.getN();
	this->deck=otherGame.deck; // Uses the copy assignment operator of Deck
	this->finished=otherGame.getFinished();
	//cout << "I have a lot of new fields. Verbal " << verbal << " Turns counter is " << turnsCounter << " N is " << N << " finished is " << finished << " and most imporently the deck is " << deck.toString() << endl;

	for(unsigned int i=0; i<otherGame.getPlayers().size();i++){
		Player* newPlayer = otherGame.getPlayers()[i]->makePlayer(); // Uses the copy assignment operator of player
		players.push_back(newPlayer);
		//cout << "Ive just pushed back the " << i << " Player ! " << newPlayer->toString() << endl;
	}
	for(unsigned int i=0; i<otherGame.winners.size();i++){
				Player* newPlayer = (otherGame.winners)[i]->makePlayer(); // Uses the copy assignment operator of player
				winners.push_back(newPlayer);
				//cout << " Is he a fucking winner ? " << newPlayer->toString() << endl;
	}
	return *this;
}

// Destructor
Game::~Game() {
	for (unsigned int i=0; i< players.size(); i++)
		delete (players.at(i));
	players.clear();
	for (unsigned int i=0; i< winners.size(); i++)
		delete (winners[i]);
	winners.clear();

}


void Game:: clean(){
	for(unsigned int i=0; i< players.size(); i++){
			Player* current=players[i];
			delete(current);
	}
	for(unsigned int i=0; i< winners.size(); i++){
			Player* current=winners[i];
			delete(current);
	}
}

void Game::init(){
	for(unsigned int i=0; i<players.size();i++){
	//	cout << "The " << i << " player is " << players[i]->getName() << endl;
		for(unsigned int j=0; j<7;j++){
                        Card * c = deck.fetchCard();
			players[i]->addCard(*c);
                        delete (c);
		}
	}
	string tmpInit;
	tmpInit= "Deck: " + deck.toString() + "\n";
	for (unsigned int i=0; i<players.size(); i++) {
		tmpInit=tmpInit+players[i]->toString() + "\n";
	}
	initState=tmpInit;
}

Player& Game:: mostCards(int currentPlayer){
	int numCards=0;
	Player* pReturn;
	for(unsigned int i=0; i<players.size(); i++){
		if (i!=(unsigned)currentPlayer){
			int currentCards= players[i]->getNumberOfCards();
			if (currentCards>=numCards){
				numCards=currentCards;
				pReturn=players[i];
			}
		}
	}
	return *pReturn;
}
void Game::play(){
	while(finished==false){
		for(unsigned int i=0; i<players.size()&& (finished==false) ;i++){
			if (verbal==1) cout << "Turn " << turnsCounter << endl;
			if (verbal==1) printState();
			players[i]->play(*this);
			cout << endl;
			if(finished==true) break;
			turnsCounter++;
		}
	}
}

const vector<Player*>& Game::getPlayers() const{
	return players;
}

vector<Player*>& Game::getWinners(){
	 return winners;
}

int Game::getVerbal() const{
	return verbal;
}

const bool Game::getFinished() const{
	return finished;
}

void Game::setFinished() {
	finished=true;
}

int Game::getTurnsCounter() const{
	return turnsCounter;
}


string Game::getInitState() const{
	return initState;
}

void Game::createPlayer(string input, int playerIndex){
	string s = input;
	string delimiter = " ";
	string playerName;
	int playerStrategy;
	while (s.at(s.size()-1)==' '){
		 s=s.substr(0, s.size()-1);
	}
	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != string::npos) {
	    token = s.substr(0, pos);
	    playerName=token;
	    s.erase(0, pos + delimiter.length());
	}
	playerStrategy=atoi(s.c_str());
	Player* p;
	switch(playerStrategy){
	case 1: /*cout<<"P1 " << playerName << endl*/; p = new PlayerType1(playerName, playerIndex); break;
	case 2: /*cout<<"P2 " << playerName << endl*/; p = new PlayerType2(playerName, playerIndex); break;
	case 3: /*cout<<"P3 " << playerName << endl*/; p = new PlayerType3(playerName, playerIndex, 0); break;
	case 4: /*cout<<"P4 " << playerName << endl;*/ p = new PlayerType4(playerName, playerIndex, 0); break;
	}
	players.push_back(p);
}


void Game::printState(){
	cout<<"Deck: " << deck.toString() <<endl;
	for(unsigned int i=0; i<players.size();i++){
		cout << players[i]->toString() << endl;
	}
}
//
//bool Game::checkForWinner(){
//	bool ans=false;
//	for(unsigned int i=0; i<players.size();i++){
//		if (players[i]->isWinner())
//			return true;
//	}
//	return ans;
//}

Deck& Game::getGameDeck(){
	return deck;
}

int Game::getN() const{
	return N;cout << "CheckED" << endl;

}

void Game::printNumberOfTurns(){
	cout<< turnsCounter <<endl;
}



void Game::printWinner(){
	if (winners.size()==1){ // Means that there is only 1 winner
		cout << "***** The winner is: " << winners.front()->getName() << " *****" << endl;
		cout << "Number of turns: " ; 
		//cout << "----------" << endl;
		//cout << "Initial State:" << endl;
		//cout << initState << endl;
		//cout << "Final State:" << endl;
		//cout << "Deck: " << deck.toString() << endl;
		//for (unsigned int i=0; i<players.size(); i++)
		//	cout << players[i]->toString();
	}
	else if (winners.size()==2){ // Means that there are two winners
			cout << "***** The winner are: " << winners.front()->getName() << " and " << winners.at(1)->getName() << " *****" << endl;
			cout << "Number of turns: " << endl;
			//cout << "----------" << endl;
			//cout << "Initial State:" << endl;
			//cout << initState << endl;
			//cout << "Final State:" << endl;
			//cout << "Deck: " << deck.toString() << endl;
			//for (unsigned int i=0; i<players.size(); i++)
			//	cout << players[i]->toString();
	}
}

//
//int main(int argc, char **argv) {
//cout << "CheckED" << endl;
//char* con= argv[1];
//Game game = Game(con);
//cout << "CheckED" << endl;
//
//return 0;
//}
