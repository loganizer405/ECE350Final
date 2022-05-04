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
  Card c = deck[n - 1];
  deck.erase(deck.begin() + n - 1);
  size--;
  return c;
}

Card Deck::askCard(Deck values){
  //must match value from deck
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
  bool valid = false;
  while(!valid){
    for(int i = 0; i < values.getSize(); i++){
      if(deck[n-1].getNumValue() == values.getCards()[i].getNumValue()){ //valid card
	valid = true;
	break; //break from for loop
      }
    }
    if(!valid){
      cout << "Must enter a card with a value on the table!\n" << "Choose a card:\n";
      cin >> n;
    }
  }
  Card c = deck[n - 1];
  deck.erase(deck.begin() + n - 1);
  size--;
  return c;
}
