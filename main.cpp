#include <iostream>
#include <vector>
//#include "Card.h" 
#include "Deck.h" //Card class is included from Deck.h

using namespace std;

char trumpSuit;

Card attack(Deck table, Deck &hand, int player);
Card defend(Card attack, Deck &hand, int player);

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
  first = 2;//temporary for testing only
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
    firstDefense = defend(firstAttack, hand1, 1);
  }
  else{ //computer. choose card of same suit
    firstDefense = defend(firstAttack, hand2, 2);

    /*
    else{ //if a card has not been found, there are no valid plays. pick up cards
      for(int i = 0; i < table.getSize(); i++){
	hand2.addCard(table.getCards()[i]);
      }
      //remove cards from table
      table.clear();
    }
    */
  }
  if(firstDefense.getValue() == 'X'){
    cout << "failed to defend!!\n";
    //          cout << "\ndeck:\n";
    //          hand1.print();
  } 
  else{
    cout << "First Defense:\n";
    firstDefense.print();
    cout << endl;
    table.addCard(firstDefense); //add to table
  }
 
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
      //choose highest card
      c = hand.findHigh();
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

Card defend(Card attack, Deck &hand, int player){
  if(player == 1){ //if player, ask for card
    cout << "Choose a card to defend with!\n";
    return hand.askCard(attack, trumpSuit);
  }
  else{ //computer
    Card c;
    vector<Card> cards = hand.getCards();
    //first, try beating card with suit
    for(int i = 0; i < (int)cards.size(); i++){
      if(cards[i].getSuit() == attack.getSuit() && cards[i].getNumValue() > attack.getNumValue()){ //if same suit, and greater value
	//remove from deck and return.
	c = cards[i];
	hand.removeCard(c);
      }
    }
    //second, try playing trump, assuming the card given is not trump
    if(attack.getSuit() != trumpSuit){
      for(int i = 0; i < (int)cards.size(); i++){
	if(cards[i].getNumValue() > attack.getNumValue()){ //winning card. remove from deck and return.
	  c = cards[i];
	  hand.removeCard(c);
	}
      }
    }
    return c;

  }
}
