#include <iostream>
#include "Card.h"

using namespace std;

int main(){
  //test code for cards
  Card c('Q', 'S');
  c.setVal('9');
  c.setSuit('H');
  c.print();
  cout << endl;
}
