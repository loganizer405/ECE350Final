#include <iostream>

using namespace std;

class Card{
public:
  Card(){ val = 'X'; suit = 'X'; }; //default constructor, should not be called
  Card(char v, char s){ val = v; suit = s; }; //constructor
  char getSuit(){ return suit; };
  char getValue(){ return val; };
  int getNumValue();
  bool setSuit(char);
  bool setVal(char);
  bool setVal(int);
  void print();
private:
  char val, suit;
  
};
