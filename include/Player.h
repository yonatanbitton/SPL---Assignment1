#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

#include "Hand.h"

using namespace std;

class Game;

class Player : public Hand {
private:
	const string name;
	int playerIndex;
public:
	Player(string playerName, int par_playerIndex);
	Player();
	Player (const Player& otherPlayer);
	Player& operator=(const Player& otherPlayer);
	string getName() const;   //Returns the name of the player
	Player& mostCards(int currentPlayer); // Returns the player with the most cards except from myself
	virtual void play(Game& g)=0;
  	virtual Player* makePlayer()=0;
	string toString();
	bool isWinner();
	int getPlayerIndex() const;   //Returns the playerIndex of the player

};

class PlayerType1 : public Player {  //For strategy 1
public:
	PlayerType1(string playerName, int playerIndex);
	PlayerType1 (const PlayerType1& otherPlayer);
	virtual void play(Game& g);
	PlayerType1& operator=(const PlayerType1& otherPlayer);
	virtual Player* makePlayer();



};

class PlayerType2 : public Player {  //For strategy 2
public:
	PlayerType2(string playerName, int playerIndex);
	PlayerType2 (const PlayerType2& otherPlayer);
	virtual void play(Game& g);
	PlayerType2& operator=(const PlayerType2& otherPlayer);
	virtual Player* makePlayer();

};


class PlayerType3 : public Player {  //For strategy 3
private:
	int opponentIndex;
public:
	PlayerType3(string playerName, int playerIndex, int opponentIndex);
	PlayerType3 (const PlayerType3& otherPlayer);
	virtual void play(Game& g);
	PlayerType3& operator=(const PlayerType3& otherPlayer);
	virtual Player* makePlayer();

};


class PlayerType4 : public Player {  //For strategy 4
private:
	int opponentIndex;
public:
	PlayerType4(string playerName, int playerIndex, int opponentIndex);
	PlayerType4 (const PlayerType4& otherPlayer);
	virtual void play(Game& g);
	PlayerType4& operator=(const PlayerType4& otherPlayer);
	virtual Player* makePlayer();

};

#endif
