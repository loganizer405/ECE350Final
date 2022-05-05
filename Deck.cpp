
#include <iostream>
#include <random>
#include <algorithm>
#include "Deck.h"

using namespace std;

Deck::Deck(){ //default initializer for 36 cards
  size = 36;
  //array to quickly iterate thru suits
  char suits[4] = {'H', 'D', 'S', 'C'};
  //Card to store current card before pushing to deck
  Card c; 
  //create deck. iterate for each suit
  for(int i = 0; i < 4; i++){
    c.setSuit(suits[i]);
    //generate numerical cards first
    for(int j = 6; j <= 14; j++){
      c.setVal(j);
      this->addCard(c);
    }
  }
}

Deck::Deck(vector<Card> cards){
  size = cards.size();
  for(int i = 0; i < size; i++){
    deck.push_back(cards[i]);
  }
}

Deck::Deck(int num){
  //empty deck
  size = num;
}

Card Deck::drawCard(){
  size--;
  Card c = deck.back();
  deck.pop_back();
  return c;
}

void Deck::addCard(Card c){
  deck.push_back(c);
  size++;
}

void Deck::removeCard(Card c){
  //  Card c = deck[n - 1];
  //find index
  for(int i = 0; i < size; i++){
    if(deck[i].getNumValue() == c.getNumValue() && deck[i].getSuit() == c.getSuit()){ //match
      deck.erase(deck.begin() + i); //remove from Deck and decrement
      size--;
      return;
    }
  }
}

void Deck::shuffleCards(){
  //using functions from Algorithm and Random libraries to shuffle vector
  //from https://www.delftstack.com/howto/cpp/shuffle-vector-cpp/
  random_device rd;
  default_random_engine rng(rd());
  shuffle(begin(deck), end(deck), rng);
}

void Deck::print(){
  for(int i = 0; i < (int)deck.size(); i++){
    deck[i].print();
    cout << endl;
  }
  cout << endl;
}

Deck Deck::drawHand(){
  //vector for the hand of cards
  vector<Card> hand;
  //draw six cards
  for(int i = 0; i < 6; i++){
    Card c = this->drawCard();
    hand.push_back(c);
  }
  //put vector into Deck class and return
  Deck deck(hand);
  return deck;
}

int Deck::firstPlayer(Deck hand1, Deck hand2, char suit){
  //find highest card in hand1
  vector<Card> cards1 = hand1.getCards();
  int min1 = -1;
  for(int i = 0; i < hand1.size; i++){
    if(cards1[i].getSuit() == suit){
      if(min1 == -1){ //if max is still undefined
	min1 = cards1[i].getNumValue();
      }
      else{ //there is already a card of that suit, so compare
	if(cards1[i].getNumValue() < min1)
	  min1 = cards1[i].getNumValue();
      }
    }
  }
  //find highest card in hand2
  vector<Card> cards2 = hand2.getCards();
  int min2 = -1;
  for(int i = 0; i < hand2.size; i++){
    if(cards2[i].getSuit() == suit){
      if(min2 == -1){ //if max is still undefined
	min2 = cards2[i].getNumValue();
      }
      else{ //there is already a card of that suit, so compare
	if(cards2[i].getNumValue() < min2)
	  min2 = cards2[i].getNumValue();
      }
    }
  }

  //return which deck has lower value
  if(min1 == -1){ //player 1 has no trump
    if(min2 == -1) //if neither has a trump card, give to player 1
      return 1;
    else //player 2 has a trump card
      return 2;
  }
  else{ //player 1 has trump
    if(min2 == -1) //player 2 has no trump
      return 1;
    else
      return (min1 < min2) ? 1 : 2;
  }
}

Card Deck::askCard(){
  //print options
  cout << "Your Hand:\n";
  for(int i = 0; i < size; i++){
    cout << i + 1 << ". ";
    deck[i].print();
    cout << endl;
  }
  //get option
  cout << "Choose a card:\n";
  int n = 0;
  cin >> n;
  while(n <= 0 || n > size){
    cout << "Invalid choice!\nChoose a card:\n";
    cin >> n;
  }
  //remove card and return
  Card c = deck[n - 1];
  this->removeCard(c);
  return c;
}

Card Deck::askCard(Deck table){
  vector<Card> tableCards = table.getCards();
  if(tableCards.size() == 0){
    return askCard();
  }
  //ask for card that has the same value as one on the table
  //print options
  cout << "Your Hand:\n";
  for(int i = 0; i < size; i++){
    cout << i + 1 << ". ";
    deck[i].print();
    cout << endl;
  }
  //get option
  cout << "Choose a card:\n";
  Card c;
  int n = 0;
  bool valid = false;
  while(!valid){
    cin >> n;
    while(n <= 0 || n > size){
      cout << "Invalid choice!\nChoose a card:\n";
      cin >> n;
    }
    c = deck[n - 1];
    for(int i = 0; i < (int)tableCards.size(); i++){
      if(c.getNumValue() == tableCards[i].getNumValue()) //if valid value
	valid = true;
    }
    if(!valid) //if invalid, prompt again
      cout << "Card must be a value on the table!\nChoose a card:\n";
  }
  //successfully got card. remove and return
  this->removeCard(c);
  return c;
}

Card Deck::askCard(Card card, char trump){
  Card c;
  //first, check if there are no winning cards
  bool win = false;
  for(int i = 0; i < size; i++){
    if(deck[i].getSuit() == trump && card.getSuit() != trump) //trump wins
      win = true;
    if(deck[i].getSuit() == card.getSuit() && deck[i].getNumValue() > card.getNumValue()) //higher card wins
      win = true;
  }
  if(!win) //if no winning cards, return empty card
    return c;
  //print options
  cout << "Your Hand:\n";
  for(int i = 0; i < size; i++){
    cout << i + 1 << ". ";
    deck[i].print();
    cout << endl;
  }
  //get option
  cout << "Choose a card:\n";
  int n = 0;
  bool valid = false;
  while(!valid){
    cin >> n;
    while(n <= 0 || n > size){
      cout << "Invalid choice!\nChoose a card:\n";
      cin >> n;
    }
    c = deck[n - 1]; //select card
    //check to see if it beats the card
    if(c.getSuit() == trump && card.getSuit() != trump) //trump wins
      valid = true;
    if(c.getSuit() == card.getSuit() && c.getNumValue() > card.getNumValue()) //higher card wins
      valid = true;
    if(!valid){ //if invalid, prompt again
      cout << "Card must beat the ";
      card.print();
      cout << "!\nChoose a card:\n";
    }
  }
  //successfully got card. remove and return
  this->removeCard(c);
  return c;
}

bool Deck::checkValue(Deck values){
  //must match value from deck
  bool valid = false;
  for(int i = 0; i < size; i++){
    for(int j = 0; j < values.getSize(); j++){
      if(deck[i].getNumValue() == values.getCards()[j].getNumValue()){ //valid card
	valid = true;
      }
    }
  }
  return valid;
}

void Deck::clear(){
  deck.clear();
  size = 0;
}

Card Deck::findHigh(char suit){
  Card max;
  for(int i = 0; i < size; i++){
    if(deck[i].getSuit() == suit){ //found
      //if max is undefined, or new card is greater than, reassign.
      if(max.getSuit() == 'X' || deck[i].getNumValue() > max.getNumValue())
	max = deck[i];
    }
  }
  return max;
}

Card Deck::findHigh(){
  Card max;
  for(int i = 0; i < size; i++){
    //if max is undefined, or new card is greater than, reassign.
    if(max.getSuit() == 'X' || deck[i].getNumValue() > max.getNumValue())
      max = deck[i];
  }
  return max;
}
