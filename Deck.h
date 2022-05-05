#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

class Deck{
  //Deck class with A thru 6 only
public:
  Deck();
  Deck(vector<Card> cards);
  Deck(int num);
  int getSize(){ return size; }
  Card drawCard();
  void addCard(Card c);
  void removeCard(Card c);
  vector<Card> getCards(){ return deck; };
  void shuffleCards();
  void print();
  Deck drawHand();
  static int firstPlayer(Deck hand1, Deck hand2, char suit);
  Card askCard();
  Card askCard(Deck table);
  bool checkValue(Deck values);
  void clear();
  Card findHigh(char suit);
  Card findHigh();
private:
  vector<Card> deck;
  Card topCard;
  int size;
};

