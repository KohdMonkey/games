//
// Created by kohdmonkey on 6/23/18.
//
#ifndef CHINESEPOKER_STRATEGY_H
#define CHINESEPOKER_STRATEGY_H

#include "Card.h"
#include "hand.h"
#include "helper.h"
#include <utility>
#include <array>
#include <list>

using namespace std;
using std::list;

typedef pair<vector<Card>, vector<Card>> cardMap;

class Strategy {


  bool autowin = false;

  int lastCardValue = 0;

  map<int, list<Hand>> topHands;

  map<string, vector<Card>> valMap;


 public:

  static int const FULLHOUSE = 8;
  static int const FLUSH = 7;
  static int const STRAIGHT = 5;
  static int const TRIPLE = 4;
  static int const TWOPAIR = 3;
  static int const PAIR = 1;
  static int const TRASH = 0;

  static bool const NEWLINE = true;

  void clearHands() {
    autowin = false;
    topHands.clear();
  }



  static list<vector<Card>>  getTriples(vector<Card> hand) {
    //make a copy
    sort(hand.begin(), hand.end(), helper::sortByValIncreasing);
    vector<Card> triple;
    list<vector<Card>> triples;


    int i = 0;
    while(hand.size() > 2 && i < hand.size() - 2) {
      //found a pair
      if(hand[i].getVal() == hand[i+1].getVal() && hand[i].getVal() == hand[i+2].getVal()) {
        triple.insert(triple.end(), hand.begin() + i, hand.begin() + i + 3);
        triples.push_back(triple);
        hand.erase(hand.begin() + i, hand.begin() + (i + 3));
        triple.clear();
      }else{
        i += 1;
      }
    }
    return triples;
  }



  static void printCombination(vector<Card> hand, int n, int r, list<vector<Card>> &allFlushes) {
    vector<Card> data;
    data.insert(data.end(), hand.begin(), hand.begin() + r);

    combinationUtil(hand, n, r, 0, data, 0, allFlushes);
  }


  static void combinationUtil(vector<Card> hand, int n, int r, int index,
                              vector<Card> data, int i, list<vector<Card>> &allFlushes) {
    if (index == r) {
      allFlushes.push_back(data);
      return;
    }

    if (i >= n)
      return;

    // current is included, put next at next location
    data[index] = hand[i];
    combinationUtil(hand, n, r, index+1, data, i+1, allFlushes);

    // current is excluded, replace it with next (Note that
    // i+1 is passed, but index is not changed)
    combinationUtil(hand, n, r, index, data, i+1, allFlushes);
  }



  static list<vector<Card>> getFlushes(vector<Card> hand) {
    sort(hand.begin(), hand.end(), helper::sortBySuit);

    list<vector<Card>> flushes = helper::findFlushes(hand);
    list<vector<Card>> allFlushes;
    for(vector<Card> flush : flushes) {
      if(flush.size() > 5)
        printCombination(flush, flush.size(), 5, allFlushes);
      else
        allFlushes.push_back(flush);
    }

    return allFlushes;
  }


  static list<vector<Card>> getFullHouses(vector<Card> hand) {
    vector<Card> tempHand, fullhouse;
    list<vector<Card>> fullhouses;



    //check for full house first
    list<vector<Card>> triples = getTriples(hand);
    if(triples.size() != 0) {
      for(vector<Card> triple : triples) {
        //make a copy
        tempHand = hand;


        //remove triple
        tempHand = helper::removeCards(tempHand, triple);
        list<vector<Card>> pairs = helper::getPairs(tempHand);
        if(pairs.size() != 0) {
          //we have a full house
          for(vector<Card> pair : pairs) {

            fullhouse.insert(fullhouse.end(), triple.begin(), triple.end());
            fullhouse.insert(fullhouse.end(), pair.begin(), pair.end());
            fullhouses.push_back(fullhouse);
            fullhouse.clear();


          }
        }//if there are pairs
      } //for all triples
    } //if there are triples
    return fullhouses;
  }//end getFullhouses


  /*
   * prevHandPoint is used to check for a bad hand, meaning that the previous row has a weaker hand than the current
   * */
  void makeHands(vector<Card> hand, vector<Card> currentHand, int depth, int point, int prevHandPoint, Hand arrangement) {
    vector<Card> currentHandCopy = currentHand;
    sort(hand.begin(), hand.end(), helper::sortByValIncreasing);

//    printf("\n\n");
//    printf("leftover hand: ");
//    helper::displayCards(hand, NEWLINE);
//
//    printf("current hand: ");
//    helper::displayCards(currentHand, NEWLINE);
    int currentPoint = 0;


    if(depth == 0 || depth == 1) {
      //try to place a full house
      list<vector<Card>> fullHouses = getFullHouses(hand);
      if(fullHouses.size() != 0) {
        //here is where we try to place a full house in the middle but a lower hand in the bottom, which is wrong
        if(prevHandPoint < FULLHOUSE)
          return;

        for(vector<Card> fullhouse : fullHouses) {

          //if bottom fullhouse is weaker than middle full house, reject
          if(prevHandPoint == FULLHOUSE and fullhouse[0].getVal() > lastCardValue){
            return;
          }

          currentHand = currentHandCopy;
          lastCardValue = fullhouse[0].getVal();
          if(lastCardValue == 1)
            lastCardValue = 14;

          vector<Card> leftover = helper::removeCards(hand, fullhouse);

          arrangement.assignRow(fullhouse, depth, FULLHOUSE);

          //recur with leftover hand
          currentHand.insert(currentHand.end(), fullhouse.begin(), fullhouse.end());
          makeHands(leftover, currentHand, depth + 1, point + FULLHOUSE, FULLHOUSE, arrangement);
        }
      }

      currentHand.clear();
      currentHand = currentHandCopy;

      //try flushes
      list<vector<Card>> flushes = getFlushes(hand);
      if(flushes.size() != 0) {

        //trying to place a flush in the middle with lower hand in the bottom
        if(prevHandPoint < FLUSH)
          return;

        for(vector<Card> flush : flushes) {
          currentHand = currentHandCopy;
          vector<Card> leftover = helper::removeCards(hand, flush);

          arrangement.assignRow(flush, depth, FLUSH);

          //recur with leftover hand
          currentHand.insert(currentHand.end(), flush.begin(), flush.end());
          makeHands(leftover, currentHand, depth + 1, point + FLUSH, FLUSH, arrangement);
        }
      }

      currentHand.clear();
      currentHand = currentHandCopy;

      //try straights
      list<vector<Card>> straights = helper::getStraights(hand);
      if(straights.size() != 0) {
        if(prevHandPoint < STRAIGHT)
          return;


        for(vector<Card> straight : straights) {
          currentHand = currentHandCopy;

          vector<Card> leftover = helper::removeCards(hand, straight);

          arrangement.assignRow(straight, depth, STRAIGHT);

          //recur with leftover hand
          currentHand.insert(currentHand.end(), straight.begin(), straight.end());
          makeHands(leftover, currentHand, depth + 1, point + STRAIGHT, STRAIGHT, arrangement);
        }
      }

      currentHand.clear();
      currentHand = currentHandCopy;

      //just a triple and all trash
      list<vector<Card>> triples = getTriples(hand);
      if(triples.size() != 0 && fullHouses.size() < 2) {
        if(prevHandPoint < TRIPLE){
          return;
        }


        currentPoint = TRIPLE;
        vector<Card> tempHand;
        for(vector<Card> triple : triples) {
          currentHand = currentHandCopy;
          vector<Card> leftover = helper::removeCards(hand, triple);
          tempHand.clear();

          //only one triple, assigning 2 trash cards
          vector<Card> trash = helper::pickTrash(leftover, 2);
          leftover = helper::removeCards(leftover, trash);

          tempHand.insert(tempHand.end(), triple.begin(), triple.end());
          tempHand.insert(tempHand.end(), trash.begin(), trash.end());

          arrangement.assignRow(tempHand, depth, TRIPLE);


          //recur with leftover hand
          currentHand.insert(currentHand.end(), tempHand.begin(), tempHand.end());
          makeHands(leftover, currentHand, depth + 1, point + TRIPLE, TRIPLE, arrangement);
        }
      }

      currentHand.clear();
      currentHand = currentHandCopy;


      //just a triple and all trash
      list<vector<Card>> pairs = helper::getPairs(hand);

      vector<Card> row;

      if(pairs.size() == 1) {
        row.clear();
        vector<Card> pair = pairs.front();

        vector<Card> leftover = helper::onePairThreeTrash(currentHand, pair, hand, row);
        arrangement.assignRow(row, depth, PAIR);

        makeHands(leftover, currentHand, depth + 1, point + PAIR, PAIR, arrangement);
      }else if(pairs.size() == 2) {
        row.clear();
        vector<Card> pair;

        if(pairs.front()[0].getVal() == 1) {
          pair = pairs.front();
          lastCardValue = 14;
        } else {
          pair = pairs.back();
          lastCardValue = pair[0].getVal();
        }

        vector<Card> leftover = helper::onePairThreeTrash(currentHand, pair, hand, row);

        arrangement.assignRow(row, depth, PAIR);

        makeHands(leftover, currentHand, depth + 1, point + PAIR, PAIR, arrangement);
      }


      if(depth == 1) {
        row.clear();

        if(pairs.size() == 0) {
          //all trash middle
          vector<Card> trash = helper::pickHighTrash(hand, 1);
          vector<Card> leftover = helper::removeCards(hand, trash);
          row.push_back(trash[0]);

          trash = helper::pickTrash(hand, 4);
          leftover = helper::removeCards(leftover, trash);

          //recur with leftover hand
          row.insert(row.end(), trash.begin(), trash.end());
          currentHand.insert(currentHand.end(), row.begin(), row.end());
          arrangement.assignRow(row, depth, TRASH);

          makeHands(leftover, currentHand, depth + 1, point, 0, arrangement);

        }else if(pairs.size() == 3) {
          //three pairs, two middle one top
          vector<Card> leftover = hand;

          //take the highest pair out to be on top
          if(pairs.front()[0].getVal() == 1)
            pairs.pop_front();

          //two low pairs mid, one pair top
          for(int i = 0; i < 2; i++) {
            vector<Card> pair = pairs.front();
            pairs.pop_front();

            leftover = helper::removeCards(leftover, pair);
            row.insert(row.end(), pair.begin(), pair.end());
          }

          vector<Card> trash = helper::pickTrash(leftover, 1);
          leftover = helper::removeCards(leftover, trash);

          row.insert(row.end(), trash.begin(), trash.end());
          arrangement.assignRow(row, depth, TWOPAIR);

          currentHand.insert(currentHand.end(), row.begin(), row.end());

          makeHands(leftover, currentHand, depth + 1, point + TWOPAIR, TWOPAIR, arrangement);
        }else if(pairs.size() == 4) {
//          printf("[DEBUG] 4 pairs after bottom row, returning");
          //two cases where this happen.
          // Either a triple and trash on the bottom, which means having 4 pairs makes no sense
          // Second is where we have only 1 pair on the bottom, which also makes no sense
          return;
        }
      }else{
        row.clear();
        //depth == 0
        if(pairs.size() == 3) {
          //three pairs, one bottom, one middle one top

          //take highest pair
          vector<Card> pair = pairs.back();
          row.insert(row.end(), pair.begin(), pair.end());

          vector<Card> leftover = helper::removeCards(hand, pair);
          vector<Card> trash = helper::pickTrash(leftover, 3);
          leftover = helper::removeCards(leftover, trash);

          row.insert(row.end(), trash.begin(), trash.end());
          arrangement.assignRow(row, depth, PAIR);

          currentHand.insert(currentHand.end(), row.begin(), row.end());
          makeHands(leftover, currentHand, depth + 1, point + PAIR, PAIR, arrangement);

        }else if(pairs.size() == 4) {
          //four pairs, two bottom, one middle one top
          vector<Card> leftover = hand;
          for(int i = 0; i < 2; i++) {
            vector<Card> pair = pairs.front();
            pairs.pop_front();

            leftover = helper::removeCards(leftover, pair);
            row.insert(row.end(), pair.begin(), pair.end());
          }

          vector<Card> trash = helper::pickTrash(leftover, 1);
          leftover = helper::removeCards(leftover, trash);

          row.insert(row.end(), trash.begin(), trash.end());
          arrangement.assignRow(row, depth, TWOPAIR);

          currentHand.insert(currentHand.end(), row.begin(), row.end());
          makeHands(leftover, currentHand, depth + 1, point + TWOPAIR, TWOPAIR, arrangement);

        }else if(pairs.size() == 5){
          //five pairs

          //take the highest pair out to be on top
          if(pairs.front()[0].getVal() == 1)
            pairs.pop_front();
          else
            pairs.pop_back();

          //one low one high
          vector<Card> pair = pairs.front();
          pairs.pop_front();
          vector<Card> leftover = helper::removeCards(hand, pair);
          row.insert(row.end(), pair.begin(), pair.end());

          //one low one high
          pair = pairs.back();
          pairs.pop_back();
          leftover = helper::removeCards(leftover, pair);
          row.insert(row.end(), pair.begin(), pair.end());

          vector<Card> trash = helper::pickTrash(leftover, 1);
          leftover = helper::removeCards(leftover, trash);

          row.insert(row.end(), trash.begin(), trash.end());
          arrangement.assignRow(row, depth, TWOPAIR);

          currentHand.insert(currentHand.end(), row.begin(), row.end());

          makeHands(leftover, currentHand, depth + 1, point + TWOPAIR, TWOPAIR, arrangement);
        }
      }

    } else {
      //weird recursion case
      if(hand.size() > 3)
        return;

      list<vector<Card>> pairs = helper::getPairs(hand);
      if(!pairs.empty()) {
        vector<Card> pair = pairs.front();
        if(prevHandPoint == PAIR and pair[0].getVal() > lastCardValue) {
          //invalid, strong pair on top
          return;
        }
        point += (PAIR + 1); //pair on top has extra weight

        //ace high on top, high chance of winning
        if(pair[0].getVal() == 1)
          point += 1;

        arrangement.assignRow(hand, depth, PAIR);
      }else{
        arrangement.assignRow(hand, depth, TRASH);
      }

      if(checkDuplicateHands(topHands[point], arrangement))
        return;

      currentHand.insert(currentHand.end(), hand.begin(), hand.end());
      arrangement.assignRaw(currentHand);



      topHands[point].push_back(arrangement);
    }
  }//end makeHands


  bool checkDuplicateHands(list<Hand> hands, Hand currentHand) {
    for(Hand h : hands) {
      if(h == currentHand)
        return true;
    }
  }


  bool isBadFullhouse(Hand hand) {
    if(hand.getbRank() == FULLHOUSE) {
      int fullHousePairVal = hand.getBottom()[4].getVal();

      if(fullHousePairVal == 1)
         fullHousePairVal = 14;

      if(hand.getmRank() == PAIR || hand.getmRank() == TWOPAIR) {
        //if fullhouse bottom and pair in middle
        vector<Card> middle = hand.getMiddle();
        helper::reassignAce(middle);

        list<vector<Card>> pairs = helper::getPairs(middle);
        for(vector<Card> pair : pairs) {
          if(pair[0].getVal() < fullHousePairVal) {
            return true;
          }
        }
      }else if(hand.getmRank() == FULLHOUSE) {
        //two fullhouses, higher fullhouse on the bottom
        int middleTriple = hand.getMiddle()[0].getVal();
        if(middleTriple == 1)
          return true;
      }

      if(hand.gettRank() == PAIR) {
        //if middle is a flush, then having a pair on top is ok
        if(hand.getmRank() == FLUSH)
          return false;

        vector<Card> top = hand.getTop();
        helper::reassignAce(top);
        list<vector<Card>> pairs = helper::getPairs(top);

        if(pairs.size() > 0 and pairs.front()[0].getVal() < fullHousePairVal)
          return true;
      }
    }
    return false;
  }//end isBadFullHouse


  bool isBadStraights(Hand hand) {
    //two straights, stronger one in the middle instead of bottom, wrong hand
    if(hand.getbRank() == STRAIGHT and hand.getmRank() == STRAIGHT) {
      return hand.getMiddle()[4].getVal() > hand.getBottom()[4].getVal();
    }
    return false;
  }



  Hand processTopHands() {

    int highestPoint = topHands.rbegin()->first;
    list<Hand> hands = topHands[highestPoint];

    list<Hand>::iterator i = hands.begin();

    while(i != hands.end()){
      if(isBadFullhouse(*i) or isBadStraights(*i)) {
        hands.erase(i++);
      }else{
        ++i;
      }
    }

    int randHandIndex = rand() % hands.size();

    i = hands.begin();
    int index = 0;
    while(index != randHandIndex) {
      i++;
      index++;
    }
//    printf("highest hand: \n");
//    i->print();
    return *i;

  }//end processTopHands


  static bool checkAutowin(vector<Card> hand) {
    string winType;
    if(helper::isautowin(hand, winType)) {
      cout << "AUTOWIN: " << winType << endl;
      return true;
    }
    return false;
  }

};



#endif