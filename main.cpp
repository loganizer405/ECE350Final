#include <iostream>
#include <vector>
//#include "Card.h" 
#include "Deck.h" //Card class is included from Deck.h

using namespace std;

int main(){
  //two hands of six cards
  //from main deck of 36 cards
  Deck deck;
  //shuffle cards twice for good measure
  deck.shuffleCards();
  deck.shuffleCards();
  //deck.print();

  //draw six cards for each hand
  Deck hand1 = deck.drawHand();
  Deck hand2 = deck.drawHand();
  cout << "Hand 1:\n";
  hand1.print();
  cout << "\nHand 2:\n";
  hand2.print();

  //trump card 
  Card trump = deck.drawCard();
  char trumpSuit = trump.getSuit();
  cout << "Trump card:\n";
  trump.print();
  cout << endl;

  //determine who goes first
  int first = Deck::firstPlayer(hand1, hand2, trumpSuit);
  cout << "First player: " << first << endl;

  //start
  Card firstAttack;
  if(first == 2){ //computer is player 2. if player 2 goes first, choose a non-trump card
    firstAttack = hand1.drawCard();
  }
  else{ //otherwise, ask for card
    firstAttack = hand2.askCard();
  }
  cout << "First attack:\n";
  firstAttack.print();
  cout << endl;
}
