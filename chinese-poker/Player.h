//
// Created by kohdmonkey on 6/23/18.
//

#ifndef CHINESEPOKER_PLAYER_H
#define CHINESEPOKER_PLAYER_H

#include "Card.h"
#include <vector>
#include <iostream>

using namespace std;

class Player {
  vector<Card> hand;

 public:

  //deal one card to the player
  void dealCard(Card card) {
    hand.push_back(card);
  }

  void clearHand() {
    //return cards back to deck
    hand.clear();
  }

  void print() {
    for(Card c : hand) {
      c.print();
    }
    cout << endl;
  }

  vector<Card> getHand() { return hand; }
};


#endif //CHINESEPOKER_PLAYER_H
