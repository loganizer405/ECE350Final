#include <iostream>
#include <random>
#include <algorithm>
#include "Deck.h"

using namespace std;

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
