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
  
  //determine who goes first. player is player 1, computer is player 2
  int player = Deck::firstPlayer(hand1, hand2, trumpSuit);
  player = 1;//temporary for testing only
  cout << "First Player: ";
  if(player == 1)
    cout << "You!\n";
  else
    cout << "Computer\n";

  //start
  Card firstAttack;
  if(player == 2) //choose card
    firstAttack = attack(table, hand1, 1);
  else //otherwise, computer goes.
    firstAttack = attack(table, hand2, 2);

  cout << "First attack:\n";
  firstAttack.print();
  cout << endl;
  table.addCard(firstAttack); //add card to table
  player = (player == 1) ? 2 : 1; //flip player

  //first defense
  Card firstDefense;
  if(player == 1) //if player, ask for card
    firstDefense = defend(firstAttack, hand1, 1);
  else //computer. choose card of same suit
    firstDefense = defend(firstAttack, hand2, 2);
  
  if(firstDefense.getValue() == 'X'){ //no valid cards. pick up
    cout << "failed to defend!!\n";

    if(player == 1) //player
      hand1.pickUp(table);
    else
      hand2.pickUp(table);
  } 
  else{ //defense successful
    cout << "First Defense:\n";
    firstDefense.print();
    cout << endl;
    table.addCard(firstDefense); //add to table
    player = (player == 1) ? 2 : 1; //flip player
  }
  //attacking continues. or, call off attack and draw up to six.
  if(player == 2){
    cout << "would you like to continue the attack?\n";
    hand1.replenish(deck);
    cout << "new hand: \n";
    hand1.print();
    //draw hands to six
    // for(int i = hand1.getSize() - 1; i < 6; i++)
    //      hand1.addCard(deck.drawCard());
    //    for(int i = hand2.getSize() - 1; i < 6; i++)
    //      hand2.addCard(deck.drawCard());
  }

 
 //next attack
 Card secondAttack;
 if(player == 1){ //player's turn
   if(!hand1.checkValue(table)){
     cout << "You have no valid cards for an attack.\n";
     hand1.pickUp(table);//pick up cards
   }
   else{
     cout << "Would you like to attack again?(y/n)\n";
     char c;
     cin >> c;

     if(c == 'y') //attack
       secondAttack = attack(table, hand1, 1);

     else //not attacking. computer gets to attack
       secondAttack = attack(table, hand2, 2);
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
    cout << "Choose a card for attack.\n";
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
