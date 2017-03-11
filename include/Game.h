#ifndef GAME_H_
#define GAME_H_

#include <iostream>

#include "Player.h"
#include "Deck.h"

using namespace std;

class Game {
private:
	vector<Player*> players;  //The list of the players
	vector<Player*> winners;
	Deck deck;                 //The deck of the game
	string initState;
	int verbal;
	int turnsCounter;
	int N;
	bool finished;
public:
	Game(char* configurationFile);
	Player& mostCards(int currentPlayer);
	Game();
	Game (const Game& otherGame);
	Game& operator=(const Game& otherGame);
	void init();
	void play();
	~Game();
	const vector<Player*>& getPlayers() const;
	vector<Player*>& getWinners();
	void createPlayer(string input, int numberOfPlayers);
	void printState();        //Print the state of the game as described in the assignment.
	void printWinner();       //Print the winner of the game as describe in the assignment.
    void printNumberOfTurns(); //Print the number of played turns at any given time.
//	bool checkForWinner();
	Deck& getGameDeck();
	string getInitState() const;
	int getVerbal() const;
	int getTurnsCounter() const;
	const bool getFinished() const;
	void setFinished();
	void clean();
	int getN() const;
	vector <string>* readFile(char* configurationFile);




};

#endif
