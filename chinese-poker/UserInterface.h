//
// Created by kohdmonkey on 6/27/18.
//

#ifndef CHINESEPOKER_USER_H
#define CHINESEPOKER_USER_H

#include <iomanip>
#include <sstream>
#include "Player.h"
#include "helper.h"
#include "strategy.h"
class UI {

 public:

  //https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
  inline bool isInteger(const std::string & s) {
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

    char * p ;
    strtol(s.c_str(), &p, 10) ;

    return (*p == 0) ;
  }

  void printHandWithIndex(vector<Card> hand) {
    for(Card c : hand) {
      cout << setw(7) << left << c.getCardString();
    }
    cout << endl;
    cout << string(65, '-') << endl;

    for(int i = 0; i < 13; i++)
      cout << setw(5) << i;

    cout << endl;
  }

  int evaluate5Cards(vector<Card> row) {
    list<vector<Card>> mylist = Strategy::getFullHouses(row);
    if(!mylist.empty())
      return Strategy::FULLHOUSE;

    mylist = Strategy::getFlushes(row);
    if(!mylist.empty())
      return Strategy::FLUSH;

    mylist = helper::getStraights(row);
    if(!mylist.empty())
      return Strategy::STRAIGHT;

    mylist = Strategy::getTriples(row);
    if(!mylist.empty())
      return Strategy::TRIPLE;

    mylist = helper::getPairs(row);
    if(mylist.size() == 2)
      return Strategy::TWOPAIR;
    else if(mylist.size() == 1)
      return Strategy::PAIR;

    //trash
    return Strategy::TRASH;
  }

  int evaluate3Cards(vector<Card> row) {
    list<vector<Card>> mylist = Strategy::getFullHouses(row);

    mylist = Strategy::getTriples(row);
    if(!mylist.empty())
      return Strategy::TRIPLE;

    mylist = helper::getPairs(row);
    if(!mylist.empty())
      return Strategy::PAIR;

    return Strategy::TRASH;
  }


  Hand arrangeHand(Player p1) {
    printf("\nReorganize cards based on the index, separate indices by space. Ex: 5 10 11 4 9 2\n");
    printf("when done, input the string 'DONE'. Left 5 cards will be bottom, followed by mid and then top\n\n");

    printf("Your hand: \n");
    vector<Card> cards = p1.getHand();
    printHandWithIndex(cards);

    string input;
    vector<string> indices;
    vector<Card> newhand;
    map<int, bool> seen;
    do {
      seen.clear();
      indices.clear();

      cout << "\nindices: ";
      getline(cin, input);

      if(input.length() > 30) {
        printf("input too long\n");
        continue;
      }

      istringstream iss(input);
      for(string s; iss >> s; )
        indices.push_back(s);

      for(string s : indices) {
        if(!isInteger(s) and s != "DONE") {
          cout << s << " is not an integer\n";
          continue;
        }

        int index = atoi(s.c_str());
        if(index < 0 || index > 12) {
          printf("index %d is out of range\n", index);
        }else {
          if(!seen[index]) {
            seen[index] = true;
            newhand.push_back(cards[index]);
          }
        }
      }

      //removing the cards from the old hand
      cards = helper::removeCards(cards, newhand);

      //insert the leftover cards from the old hand
      newhand.insert(newhand.end(), cards.begin(), cards.end());

      //reassign old hand
      cards = newhand;

      //clear the newhand
      newhand.clear();

      printf("\nnew hand: \n");
      printHandWithIndex(cards);

    }while(input != "DONE");

    Hand hand;
    int rank;
    vector<Card> row;

    //process bottom row
    row.insert(row.end(), cards.begin(), cards.begin() + 5);
    rank = evaluate5Cards(row);
    hand.assignRow(row, 0, rank);

    row.clear();
    row.insert(row.end(), cards.begin() + 5, cards.begin() + 10);
    rank = evaluate5Cards(row);
    hand.assignRow(row, 1, rank);

    row.clear();
    row.insert(row.end(), cards.begin() + 10, cards.begin() + 13);
    rank = evaluate5Cards(row);
    hand.assignRow(row, 2, rank);

    return hand;
  }



};


#endif //CHINESEPOKER_USER_H
