#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

class Deck{
  //Deck class with A thru 6 only
public:
  Deck(); //default constructor, creates deck of 36
  Deck(vector<Card> cards); //constructor with given cards
  Deck(int num); //constructor for empty deck
  int getSize(){ return size; } //return size of deck
  Card drawCard(); //draw card from pile
  void addCard(Card c); //add card to pile
  void removeCard(Card c); //remove card from pile
  vector<Card> getCards(){ return deck; }; //returns vector of Cards
  void shuffleCards(); //shuffles randomly
  void print();
  Deck drawHand(); //draws a hand of six cards
  static int firstPlayer(Deck hand1, Deck hand2, char suit); //determined first player based on lowest trump card
  Card askCard(); //asks for any card
  Card askCard(Deck table); //asks for card that matches any value on the table
  Card askCard(Card card, char trump); //asks for card that beats the card
  bool checkValue(Deck values); //checks for valid card matching any value in the Deck argument 
  void clear(); //empty deck
  Card findHigh(char suit); //finds highest card of given suit
  Card findHigh(); //finds highest card
  void pickUp(Deck &table); //places cards from table argument into caller Deck
  bool replenish(Deck &deck); //replenish up to six cards. returns false if there are not enough cards
private:
  vector<Card> deck;
  Card topCard;
  int size;
};

