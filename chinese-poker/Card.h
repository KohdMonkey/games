#ifndef CHINESEPOKER_CARD_H
#define CHINESEPOKER_CARD_H

#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

//map the suit to unicode so that they can be printed
map<string, string> suitMap = {
    {"H", "\u2665"},
    {"S", "\u2660"},
    {"C", "\u2663"},
    {"D", "\u2666"}
};

class Card {
  string suit;
  int val;

  map<int, string> valMap = {
      {1, "A"},
      {11, "J"},
      {12, "Q"},
      {13, "K"},
      {14, "A"}
  };

 public:
  Card(int v, string s) : val(v), suit(s){};

  Card(const Card &c2) {
    val = c2.val;
    suit = c2.suit;
  }

  void print() {
    string toprint = "";

    toprint += getValStr();
    toprint += suitMap[suit];


    cout << " " + toprint << " ";
  }

  void assignVal(int v) { val = v; }

  string getSuit() { return suit; }

  string getValStr() {
    if(val == 1 || val > 10) {
      return valMap[val];
    }else {
      return to_string(val);
    }
  }

  int getVal() { return val; }

  string getCardString() { return getValStr() + suitMap[suit]; }


  bool operator == (const Card &c2) {
    if((val == 1 and c2.val == 14) or (val == 14 and c2.val == 1))
      return suit == c2.suit;
    else
      return (val == c2.val ) && (suit == c2.suit);
  }

  bool operator > (const Card &c2) {
    return val > c2.val;
  }

  bool operator < (const Card &c2) {
    return val < c2.val;
  }

  Card& operator=( const Card& other ) {
    val = other.val;
    suit = other.suit;
    return *this;
  }

};

#endif