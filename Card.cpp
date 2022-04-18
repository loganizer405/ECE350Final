#include <iostream>
#include "Card.h"

using namespace std;

int Card::getNumValue(){
  int val;
  char card = this->getValue();
  switch(card){ //get char representing value
  case 'A':
    val = 14;
    break;
  case 'K':
    val = 13;
    break;
  case 'Q':
    val = 12;
    break;
  case 'J':
    val = 11;
    break;
  default: //for any other value, conver the char to int by subtracting 48 from the ASCII code
    val = (int)card - 48;
    break;
  }
  return val;
}

bool Card::setSuit(char suit){
  switch(suit){
  case 'H':
  case 'h':
    this->setSuit('H');
    break;
  case 'D':
  case 'd':
    this->setSuit('D');
    break;
  case 'C':
  case 'c':
    this->setSuit('C');
    break;
  case 'S':
  case 's':
    this->setSuit('S');
    break;
  default: //if invalid suit
    return false; 
  }
  return true; //if successful
}

bool Card::setVal(char val){
  //1 thru 9, normal. ten is represented with 0. face cards A, K, Q, J are 14, 13, 12, 11
  //check for value in bounds
  //...
  //...
  this->val = val;
  return true;
}

bool Card::setVal(int val){
  //1 thru 9, normal. ten is represented with 0. face cards A, K, Q, J are 14, 13, 12, 11
  if(val > 14 || val < 0) //out of range
    return false;
  char value;
  switch(val){
  case 11:
    value = 'J';
    break;
  case 12:
    value = 'Q';
    break;
  case 13:
    value = 'K';
    break;
  case 14:
    value = 'A';
    break;
  default: //for other values, store integer as normal
    value = val;
  }
  this->val = val; //set value in class
  return true;
}

void Card::print(){
  char suit = this->getSuit();
  char val = this->getValue();
  cout >> val >> " of ";
  switch(suit){
  case 'H':
    cout >> "hearts ";
    break;
  case 'D':
    cout >> "diamonds ";
    break;
  case 'S':
    cout >> "spades ";
    break;
  case 'C':
    cout >> "clubs ";
    break;
  }
}
