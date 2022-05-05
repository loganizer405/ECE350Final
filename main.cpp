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

  //trump card 
  Card trump = deck.drawCard();
  trumpSuit = trump.getSuit();
  cout << "Trump card:\n";
  trump.print();
  cout << endl << endl;
  
  //stack of current cards on the table
  Deck table(0);
  
  //winner 
  int winner = 0;

  //determine who goes first. player is player 1, computer is player 2
  int player = Deck::firstPlayer(hand1, hand2, trumpSuit);
  //  player = 1;//temporary for testing only
  cout << "First Player: ";
  if(player == 1)
    cout << "You!\n";
  else
    cout << "Computer\n";

  do{ //start
    //check for winner
    //    if(deck.getSize() == 0){
    if(hand1.getSize() == 0)
      winner = 1;
    if(hand2.getSize() == 0)
      winner = 2;

    Card firstAttack;
    if(player == 1) //choose card
      firstAttack = attack(table, hand1, 1);
    else //otherwise, computer goes.
      firstAttack = attack(table, hand2, 2);
    
    cout << "Attack:\n";
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
      if(player == 2) //if computer
	cout << "Computer failed to defend and picks up cards.\n";
      else{
	cout << "You failed to defend!! Pick up cards.\n";
	//	hand1.pickUp(table);
	//	player = 2;
	//	continue;
      }
      
      if(player == 1) //player
	hand1.pickUp(table);
      else
	hand2.pickUp(table);
      player = (player == 1) ? 2 : 1; //flip player
      continue; //repeat loop
    } 
    else{ //defense successful
      cout << "Defense:\n";
      firstDefense.print();
      cout << endl;
      table.addCard(firstDefense); //add to table
      player = (player == 1) ? 2 : 1; //flip player
    }
    //attacking continues. or, call off attack and draw up to six.
    if(player == 1){
      if(!hand1.checkValue(table)){
	cout << "You have no valid cards for an attack and pick up the cards.\n";
	hand1.pickUp(table);//pick up cards
	player = 2;
	continue; 
      }
      else{
	cout << "would you like to continue the attack? (y/n)\n";
	char c;
	cin >> c;
	if(c == 'y'){
	  player = 1;
	  continue; //go back to loop
	}
	else{ //not attacking. discard table and draw
	  table.clear();
	  if(!hand1.replenish(deck) || !hand2.replenish(deck))
	    cout << "No more cards in deck.\n";
	  player = 2; //computer gets next attack
	}
      }
    }
    else{ //computer. assume the computer ends the attack
      table.clear();
      if(!hand1.replenish(deck) || !hand2.replenish(deck))
	cout << "No more cards in deck.\n";
      player = 2;
    }

  } while (winner == 0);
  if(winner == 1)
    cout << "You won!!!!!!!\n";
  else
    cout << "The computer won :(\n";
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
    }
    //remove card from computer's hand
    hand.removeCard(c);
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
