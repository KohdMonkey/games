//
// Created by kohdmonkey on 6/26/18.
//

#ifndef CHINESEPOKER_HAND_H
#define CHINESEPOKER_HAND_H


#include "Card.h"
#include "helper.h"
#include <vector>

class Hand {
  vector<Card> bottom, middle, top;
  vector<Card> raw;
//  string bRank, mRank, tRank;  //flush, straight, fullhouse, etc....
  int bRank, mRank, tRank;


 public:
  void assignRow(vector<Card> r, int depth, int rank) {
    switch(depth) {
      case 0:
        bottom = r;
        bRank = rank;
      case 1:
        middle = r;
        mRank = rank;
      case 2:
        top = r;
        tRank = rank;
    }
  }

  bool operator == (const Hand &h2) {
    return (helper::compareRows(bottom, h2.bottom) &&
            helper::compareRows(middle, h2.middle) &&
            helper::compareRows(top, h2.top));
  }

  void assignRaw(vector<Card> hand) {
    raw = hand;
  }

  vector<Card> getBottom() { return bottom; }
  vector<Card> getMiddle() { return middle; }
  vector<Card> getTop() { return top; }
  vector<Card> getRaw() { return raw; }

  int getbRank() { return bRank; }
  int getmRank() { return mRank; }
  int gettRank() { return tRank; }


  static void printThreeCards(vector<Card> topRow) {
    if(topRow.size() == 0) {
      printf("error, row empty\n");
      return;
    }
    printf("%4s", "");
    for(Card c : topRow)
      c.print();
    printf("%4s\n", "");
  }

  static void printFiveCards(vector<Card> row) {
    if(row.size() == 0) {
      printf("error, row empty\n");
      return;
    }
    for(Card c : row)
      c.print();
    printf("\n");
  }

  void print() {
    printThreeCards(top);
    printFiveCards(middle);
    printFiveCards(bottom);
  }

};

#endif //CHINESEPOKER_HAND_H
