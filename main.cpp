#include <iostream>
#include <vector>
//#include "Card.h" 
#include "Deck.h" //Card class is included from Deck.h

using namespace std;

char trumpSuit;

Card attack(Deck table, Deck &hand, int player);

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
  /*
  cout << "Hand 1:\n";
  hand1.print();
  cout << "\nHand 2:\n";
  hand2.print();
  */

  //trump card 
  Card trump = deck.drawCard();
  trumpSuit = trump.getSuit();
  cout << "Trump card:\n";
  trump.print();
  cout << endl << endl;
  
  //stack of current cards on the table
  Deck table(0);
  
  //determine who goes first
  int first = Deck::firstPlayer(hand1, hand2, trumpSuit);
  first = 1;//temporary for testing only
  cout << "First Player: ";
  if(first == 1)
    cout << "You!\n";
  else
    cout << "Computer\n";

  //start
  Card firstAttack;
  if(first == 2) //computer is player 2. if player 2 goes first, choose a non-trump card
    firstAttack = attack(table, hand2, 2);
  else //otherwise, player goes.
    firstAttack = attack(table, hand1, 1);

  cout << "First attack:\n";
  firstAttack.print();
  cout << endl;
  table.addCard(firstAttack); //add card to table

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
	  if(cards2[i].getNumValue() > max.getNumValue())
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
      for(int i = 0; i < table.getSize(); i++){
	hand2.addCard(table.getCards()[i]);
      }
      //remove cards from table
      table.clear();
    }
      
  }
 cout << "First Defense:\n";
 firstDefense.print();
 cout << endl;
 table.addCard(firstDefense); //add to table
 
 //next attack
 Card secondAttack;
 if(first == 1){ //player's turn
   if(!hand1.checkValue(table)){
     cout << "You have no valid cards for an attack.\n";
     //pick up cards
   }
   else{
     cout << "Would you like to attack again?(y/n)\n";
     char c;
     cin >> c;

     if(c == 'y'){ //attack. needs to be a value already on the table
       secondAttack = hand1.askCard(table);
     }
     else{ //not attacking
       //computer gets to attack
       //choose next card
       //secondAttack = hand2.drawCard();
       secondAttack = attack(table, hand2, 2);
     }
   }
 }
 cout << "Second attack:\n";
 secondAttack.print();
 cout << endl;
 table.addCard(secondAttack);
}

Card attack(Deck table, Deck &hand, int player){
  Card c;

  if(player == 1){ //player
    cout << "Choose a card for first attack.\n";
    if(table.getSize() == 0) //if there are no cards on the table, any card is valid. (first play)
      c = hand.askCard();
    else //there are cards on the table. must be a value already on the table
      c = hand.askCard(table);
  }
  else{ //computer
    vector<Card> cards = hand.getCards();
    if(table.getSize() == 0){
      //choose highest non-trump card
      Card max;
      for(int i = 0; i < (int)cards.size(); i++){
	if(cards[i].getSuit() != trumpSuit){ //found not trump
	  if(max.getSuit() == 'X') //if max is still undefined
	    max = cards[i];
	  else{
	    if(cards[i].getNumValue() > max.getNumValue())
	      max = cards[i];
	  }
	}
      }
      if(max.getSuit() != 'X'){ //if we have a valid card, return
	c = max;
      }
      else{ //no non-trump card. pick next card
	c = hand.drawCard();
      }
    }
    else{ //if there are cards on the table, it must be valid
      vector<Card> tableCards = table.getCards();
      Card max;
      for(int i = 0; i < (int)tableCards.size(); i++){
	for(int j = 0; j < (int)cards.size(); j++){
	  if(tableCards[i].getNumValue() == cards[j].getNumValue()){
	    if(max.getSuit() == 'X')
	      max = cards[j];
	    else{
	      if(cards[j].getNumValue() > max.getNumValue())
		max = cards[j];
	    }
	  }
	}
      }
      if(max.getSuit() != 'X')
	c = max;
      //      else //no valid cards
    }
  }
  return c;
}
