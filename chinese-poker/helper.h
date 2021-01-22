//
// Created by kohdmonkey on 6/25/18.
//

#ifndef CHINESEPOKER_HELPER_H
#define CHINESEPOKER_HELPER_H

#include "hand.h"
#include <list>

using std::list;

class helper {

 public:

  static bool sortByValIncreasing(Card c1, Card c2) { return c1.getVal() < c2.getVal(); }
  static bool sortBySuit (Card c1, Card c2) { return c1.getSuit().compare(c2.getSuit()) < 0; }
  static bool compareVals (Card c1, Card c2) { return c1.getVal() == c2.getVal(); }

  static void displayCards(vector<Card> cards, bool newline) {
    for(Card c : cards) {
      c.print();
    }
    if(newline)
      cout << endl;
  }

  static bool compareRows(vector<Card> row1, vector<Card> row2) {
    for(int i = 0; i < row1.size(); i++) {
      if(!(row1[i] == row2[i]))
        return false;
    }
    return true;
  }

  static list<vector<Card>> getPairs(vector<Card> hand) {
    //make a copy
    sort(hand.begin(), hand.end(), helper::sortByValIncreasing);
    vector<Card> pair;
    list<vector<Card>> pairs;



    int i = 0;
    while(i < hand.size() -1 and hand.size() != 0) {
      //found a pair
      if(hand[i].getVal() == hand[i+1].getVal()) {
        pair.push_back(hand[i]);
        pair.push_back(hand[i+1]);
        hand.erase(hand.begin() + i, hand.begin() + (i + 2));

        pairs.push_back(pair);
        pair.clear();

      }else{
        i += 1;
      }
    }
    return pairs;
  }

  //given a hand, reassign the ace value from 1 to 14, for large straights
  static void reassignAce(vector<Card> &hand) {

    while(hand[0].getVal() == 1) {
      Card c = hand[0];
      c.assignVal(14);
      hand.erase(hand.begin());
      hand.push_back(c);
    }
  }

  //given a sequence, remove the cards in the sequence from the hand
  static vector<Card> removeCards(vector<Card> hand, vector<Card> sequence) {
    for(Card c : sequence) {
      for(int i = 0; i <  hand.size(); i++) {
        if(hand[i] == c) {
          hand.erase(hand.begin() + i);
        }
      }
    }
    return hand;
  }


  //check whether a sequence is a straight
  static bool checkStraight(vector<Card> hand) {
    for(int i = 0; i < hand.size() - 1; i++) {
      if(hand[i].getVal() + 1 != hand[i+1].getVal())
        return false;
    }
    return true;
  }


  //one pair and three trash
  static vector<Card> onePairThreeTrash(vector<Card> &currentHand, vector<Card> pair, vector<Card> hand, vector<Card> &row) {
    row.insert(row.end(), pair.begin(), pair.end());

    vector<Card> leftover = removeCards(hand, pair);
    vector<Card> trash = pickLowTrash(leftover, 3);
    leftover = removeCards(leftover, trash);

    row.insert(row.end(), trash.begin(), trash.end());


    currentHand.insert(currentHand.end(), row.begin(), row.end());
    return leftover;
  }


  static vector<Card> pickTrash(vector<Card> hand, int numTrashCards) {
    list<vector<Card>> pairs = getPairs(hand);
    for(auto it : pairs) {
      hand = removeCards(hand, it);
    }

    sort(hand.begin(), hand.end(), sortByValIncreasing);

    vector<Card> trash;

    for(int i = 0; i < numTrashCards; i++) {
      int index = rand() % hand.size();

      if(index > 0)
        index--;

      trash.push_back(hand[index]);
      hand.erase(hand.begin() + index);
    }

    //sanity check
//    displayCards(trash, false);
//    displayCards(hand, true);

    return trash;
  }


  static vector<Card> pickLowTrash(vector<Card> hand, int numTrashCards) {
    list<vector<Card>> pairs = getPairs(hand);
    for(auto it : pairs) {
      //removing pairs
      hand = removeCards(hand, it);
    }

    sort(hand.begin(), hand.end(), sortByValIncreasing);
    reassignAce(hand);

    vector<Card> trash;

    for(int i = 0; i < numTrashCards; i++) {
      trash.push_back(hand[0]);
      hand.erase(hand.begin());
    }

    //sanity check
//    displayCards(trash, false);
//    displayCards(hand, true);

    return trash;
  }


  static vector<Card> pickHighTrash(vector<Card> hand, int numTrashCards) {
    list<vector<Card>> pairs = getPairs(hand);
    for(auto it : pairs) {
      hand = removeCards(hand, it);
    }

    sort(hand.begin(), hand.end(), sortByValIncreasing);

    vector<Card> trash;

    for(int i = numTrashCards; i > 0; i--) {
      trash.push_back(hand[hand.size() - 1]);\
      hand.erase(hand.end());
    }

    return trash;
  }//end pickHighTrash


  static std::list<vector<Card>> findIncreasingStraight(vector<Card> hand) {
    int pos, count;
    vector<Card> s;
    std::list<vector<Card>> straights;
    count = 0;
    for(int i = 0; i < hand.size(); i++) {
      if(hand[i].getVal() + 1 == hand[i+1].getVal()) {
        if(count == 0) {
          pos = i;
          count = 2;
        }else{
          count++;
        }
      }else{
        if(count >= 5) {
          s.insert(s.end(), hand.begin() + pos, hand.begin() + pos + count);
          straights.push_back(s);
          s.clear();
        }
        count = 0;
      }
    }

    return straights;
  }//end findIncreasingStraight



  static void removeDuplicateStraights(std::list<vector<Card>> &straights, std::list<vector<Card>> highstraights) {
    for(vector<Card> l : highstraights) {
      list<vector<Card>>::iterator it;
      for(it = straights.begin(); it != straights.end(); ) {
        if(l[0].getVal() == (*it)[0].getVal() and
            l[4].getVal() == (*it)[4].getVal())
          it = straights.erase(it);
        else
          it++;
      }
    }

    straights.splice(straights.end(), highstraights);
  }


  //given some straights, enumerate all possible combinations
  static list<vector<Card>> enumerateStraights(list<vector<Card>> straights) {
    list<vector<Card>> allstraights;
    vector<Card> s;
    for(vector<Card> straight : straights) {
      if(straight.size() > 5) {
        int numStraights = straight.size() - 5;
        for(int i = 0; i <= numStraights; i++) {
          s.insert(s.end(), straight.begin() + i, straight.begin() + 5 + i);
          allstraights.push_back(s);
          s.clear();
        }
      }else{
        allstraights.push_back(straight);
      }
    }
    return allstraights;
  }


  static list<vector<Card>> getStraights(vector<Card> hand) {

    sort(hand.begin(), hand.end(), helper::sortByValIncreasing);
    vector<Card> straight;

    vector<Card> removedDups = hand;
    removedDups.erase(unique(removedDups.begin(), removedDups.end(), helper::compareVals), removedDups.end());

    list<vector<Card>> straights;
    list<vector<Card>> allstraights;

    if(removedDups.size() >= 5) {
      straights = findIncreasingStraight(removedDups);

      helper::reassignAce(removedDups);
      list<vector<Card>> highstraight = findIncreasingStraight(removedDups);

      removeDuplicateStraights(straights, highstraight);


      allstraights = enumerateStraights(straights);
    }

    return allstraights;
  }//end getStraights


  //given a hand sorted by suit, find all the flushes
  static list<vector<Card>> findFlushes(vector<Card> hand) {
    int pos, count;
    vector<Card> s;
    std::list<vector<Card>> flushes;

    count = 0;
    string currentsuit = hand[0].getSuit();
    for(int i = 1; i < hand.size(); i++) {
      if(hand[i].getSuit() == currentsuit) {
        if(count == 0) {
          pos = i - 1;
          count = 2;
        }else{
          count++;
        }
      }else{
        if(count >= 5) {
          s.insert(s.end(), hand.begin() + pos, hand.begin() + pos + count);
          flushes.push_back(s);
          s.clear();
        }
        count = 0;
        currentsuit = hand[i].getSuit();
      }
    }

    //flush at the end
    if(count >= 5) {
      s.insert(s.end(), hand.begin() + pos, hand.begin() + pos + count);
      flushes.push_back(s);
    }

    return flushes;
  }//end findFlushes




  static bool autowin6Pairs(vector<Card> hand, string &winType) {
    list<vector<Card>> pairs = getPairs(hand);
    if(pairs.size() == 6) {
      winType = "6 pairs";
      return true;
    }
    return false;
  }


  static bool autowin4ofaKind(vector<Card> hand, string &winType) {
    map<int, int> cardcount;
    for(Card c : hand) {
      int cardVal = c.getVal();
      cardcount[cardVal]++;
      if(cardcount[cardVal] == 4) {
        winType = "4 of a kind";
        return true;
      }
    }

    return false;
  }


  static bool autowinstraightflush(vector<Card> hand, string &winType) {
    list<vector<Card>> flushes = findFlushes(hand);

    for(vector<Card> flush : flushes) {
      list<vector<Card>> straights = getStraights(flush);
      if(straights.size() > 0){
        winType = "straight flush";
        return true;
      }

    }
    return false;
  }


  static bool isautowin(vector<Card> hand, string &winType) {
    return autowin6Pairs(hand, winType) || autowin4ofaKind(hand, winType) || autowinstraightflush(hand, winType);
  }



};







#endif //CHINESEPOKER_HELPER_H
