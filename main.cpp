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
  cout << endl << endl;;

  //determine who goes first
  int first = Deck::firstPlayer(hand1, hand2, trumpSuit);
  cout << "First player: " << first << endl;

  //start
  Card firstAttack;
  if(first == 2){ //computer is player 2. if player 2 goes first, choose a non-trump card
    firstAttack = hand2.drawCard();
  }
  else{ //otherwise, ask for card
    firstAttack = hand1.askCard();
  }
  cout << "First attack:\n";
  firstAttack.print();
  cout << endl;

  //first defense
  Card firstDefense;
  if(first == 2){ //first player was computer. ask user for card
    cout << "Choose a card to defend!\n";
    firstDefense = hand1.askCard();
  }
  else{ //computer. choose card of same suit
    vector<Card> cards2 = hand2.getCards();
    Card max;
    for(int i = 0; i < hand2.getSize(); i++){
      if(cards2[i].getSuit() == firstAttack.getSuit()){
	if(max.getSuit() == 'X') //if max is still undefined
	  max = cards2[i];
	else{ //there is already a card of that suit, so compare
	  if(cards2[i].getNumValue() < max.getNumValue())
	    max = cards2[i];
	}
      }
    }
    if(max.getSuit() == 'X'){ //if a card has not been found
      //choose trump card
      for(int i = 0; i < hand2.getSize(); i++){
	if(cards2[i].getSuit() == trumpSuit){ //found trump
	  firstDefense = cards2[i];
	  break;
	}
      }
    }
    else if(max.getSuit() != 'X') //if the card was already found
      firstDefense = max;
    else{ //if a card has not been found, there are no valid plays. pick up cards

    }
  }
 cout << "First Defense:\n";
 firstDefense.print();
 cout << endl;
 //next attack
 Card secondAttack;
 if(first == 1){ //player's turn
   cout << "Would you like to attack again?(y/n)\n";
   char c;
   cin >> c;
   if(c == 'y'){
     cout << "Choose a card to attack with:\n";
     secondAttack = hand1.askCard();
   }
   else{ //not attacking
     //computer gets to attack
     //choose next card
     secondAttack = hand2.drawCard();
     
   }
 }
 cout << "Second attack:\n";
 secondAttack.print();
 cout << endl;
}
