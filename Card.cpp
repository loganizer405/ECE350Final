#include <iostream>
#include "Card.h"

using namespace std;

int Card::getNumValue(){
  int card; //to store numerical value

  switch(val){ //use char representing value
  case 'A':
    card = 14;
    break;
  case 'K':
    card = 13;
    break;
  case 'Q':
    card = 12;
    break;
  case 'J':
    card = 11;
    break;
  case '0':
    card = 10;
    break;
  default: //for any other value, conver the char to int by subtracting 48 from the ASCII code
    card = (int)val - 48;
    break;
  }
  return card;
}

bool Card::setSuit(char s){
  
  switch(s){
  case 'H':
  case 'h':
    suit = 'H';
    break;
  case 'D':
  case 'd':
    suit = 'D';
    break;
  case 'C':
  case 'c':
    suit = 'C';
    break;
  case 'S':
  case 's':
    suit = 'S';
    break;
  default: //if invalid suit
    return false; 
  }
  return true; //if successful
}

bool Card::setVal(char value){
  //1 thru 9, normal. ten is represented with 0. face cards A, K, Q, J are 14, 13, 12, 11
  //check for value in bounds
  //...
  //...
  val = value;
  return true;
}

bool Card::setVal(int value){
  //1 thru 9, normal. ten is represented with 0. face cards A, K, Q, J are 14, 13, 12, 11
  if(value > 14 || value < 0) //out of range
    return false;
  switch(value){
  case 11:
    val = 'J';
    break;
  case 12:
    val = 'Q';
    break;
  case 13:
    val = 'K';
    break;
  case 14:
    val = 'A';
    break;
  default: //for other values, store integer as normal
    val = value;
  }
  return true;
}

void Card::print(){
  //  char suit = this->getSuit();
  //  char val = this->getValue();
  if(val == '0')
    cout << "10";
  else
    cout << val;
  
  cout << " of ";
  switch(suit){
  case 'H':
    cout << "hearts ";
    break;
  case 'D':
    cout << "diamonds ";
    break;
  case 'S':
    cout << "spades ";
    break;
  case 'C':
    cout << "clubs ";
    break;
  }
}
