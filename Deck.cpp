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
  int max1 = -1;
  for(int i = 0; i < hand1.size; i++){
    if(cards1[i].getSuit() == suit){
      if(max1 == -1){ //if max is still undefined
	max1 = cards1[i].getNumValue();
      }
      else{ //there is already a card of that suit, so compare
	if(cards1[i].getNumValue() > max1)
	  max1 = cards1[i].getNumValue();
      }
    }
  }
  //find highest card in hand2
  vector<Card> cards2 = hand2.getCards();
  int max2 = -1;
  for(int i = 0; i < hand2.size; i++){
    if(cards2[i].getSuit() == suit){
      if(max2 == -1){ //if max is still undefined
	max2 = cards2[i].getNumValue();
      }
      else{ //there is already a card of that suit, so compare
	if(cards2[i].getNumValue() > max2)
	  max2 = cards2[i].getNumValue();
      }
    }
  }

  //return which deck has higher value
  if(max1 >= max2) //if equal then just give player 1
    return 1;
  else
    return 2;
}
