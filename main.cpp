#include <iostream>
#include <vector>
//#include "Card.h" 
#include "Deck.h" //Card class is included from Deck.h

using namespace std;

int main(){
  
  //test code for cards
  Card c('Q', 'S');
  c.setVal('9');
  c.setSuit('H');
  //  c.print();
  cout << endl;


  vector<Card> pile;
  pile.push_back(c);
  Card d('0', 'S');
  pile.push_back(d);
  Deck deck(pile);
  //Deck deck();

  deck.shuffleCards();
  deck.print();
  //  Card newCard = deck.drawCard();
  //  newCard.print();
  //  cout << endl;
}
