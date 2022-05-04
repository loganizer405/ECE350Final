#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

class Deck{
  //Deck class with A thru 6 only
public:
  Deck();
  Deck(vector<Card> cards);
  int getSize(){ return size; }
  Card drawCard();
  void addCard(Card c);
  vector<Card> getCards(){ return deck; };
  void shuffleCards();
  void print();
  Deck drawHand();
  static int firstPlayer(Deck hand1, Deck hand2, char suit);
private:
  vector<Card> deck;
  Card topCard;
  int size;
};

