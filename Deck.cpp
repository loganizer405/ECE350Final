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
