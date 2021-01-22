#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstring>


#include "Card.h"
#include "hand.h"
#include "Player.h"
#include "strategy.h"
#include "UserInterface.h"
#include "regressionTest.h"

using namespace std;

#define Shuffle(cards) random_shuffle(cards.begin(), cards.end())

Strategy strategy;
regressionTest regression;
UI ui;


vector<Card> createDeck() {
  string suits[] = {"S", "C", "D", "H"};
  int vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

  vector<Card> cards;

  for(string s : suits) {
    for(int v : vals) {
      Card c(v, s);
      cards.push_back(c);
    }
  }

  return cards;
}

void dealCards(vector<Card> &deck, Player &p1) {
  for(int i = 0; i < 13; i++) {
    p1.dealCard(deck.back());
    deck.pop_back();
  }
}


void returnCards(vector<Card> &deck, Player &p1) {
  vector<Card> hand = p1.getHand();
  deck.insert(deck.end(), hand.begin(), hand.end());
  p1.clearHand();
}

bool validateDeck(vector<Card> deck) {
  map<int, int> valMap;
  for(Card c : deck) {
     if(valMap.find(c.getVal()) == valMap.end()) {
       valMap[c.getVal()] = 1;
     }else{
       valMap[c.getVal()]++;
     }
  }

  sort(deck.begin(), deck.end(), helper::sortByValIncreasing);
//  helper::displayCards(deck, true);

  for(auto const& card : valMap) {
    if(card.second != 4)
      return false;
  }

  return true;
}

string compareRow(vector<Card> botRow, int botRank, vector<Card> playerRow, int playerRank) {
  helper::reassignAce(botRow);
  helper::reassignAce(playerRow);

  sort(botRow.begin(), botRow.end(), helper::sortByValIncreasing);
  sort(playerRow.begin(), playerRow.end(), helper::sortByValIncreasing);

  if(botRank > playerRank) {
    return "bot";
  }else if(botRank < playerRank) {
    return "player";
  }else{
    //equal
    if(botRow.size() == 5) {
      //comparing 5 cards
      if(botRank == Strategy::FLUSH || botRank == Strategy::STRAIGHT) {
        //compare card by card
        for(int i = 4; i >= 0; i--) {
          if(botRow[i] > playerRow[i]){
            return "bot";
          }else if(botRow[i] < playerRow[i]) {
            return "player";
          }
        }
        return "tie";
      }else if(botRank == Strategy::FULLHOUSE) {
        int playerTrippleVal = Strategy::getTriples(playerRow).front()[0].getVal();
        int botTriple = Strategy::getTriples(botRow).front()[0].getVal();
        if(botTriple > playerTrippleVal)
          return "bot";
        else
          return "player";
      }else if(botRank == Strategy::TWOPAIR || botRank == Strategy::PAIR) {
        list<vector<Card>> playerPairs = helper::getPairs(playerRow);
        list<vector<Card>> botPairs = helper::getPairs(botRow);

        list<vector<Card>>::reverse_iterator botItr, playerItr;

        for(botItr = botPairs.rbegin(), playerItr = playerPairs.rbegin(); botItr != botPairs.rend(); ) {
          if((*botItr)[0] > (*playerItr)[0])
            return "bot";
          else if((*botItr)[0] < (*playerItr)[0])
            return "player";

          //removing the pairs
          playerRow = helper::removeCards(playerRow, *playerItr);
          botRow = helper::removeCards(botRow, *botItr);

          botItr++;
          playerItr++;
        }

        //compare last card
        if(botRow[0] > playerRow[0])
          return "bot";
        else if(botRow[0] < playerRow[0])
          return "player";
        else
          return "tie";
      }else {
        //comparing all trash
        for(int i = 4; i >= 0; i--) {
          if(botRow[i] > playerRow[i])
            return "bot";
          else if(botRow[i] < playerRow[i])
            return "player";
        }
        return "tie";
      }
    }else{
      //comparing 3 cards
      if(botRank == Strategy::PAIR) {
         if(botRow[0] > playerRow[0])
           return "bot";
         else if(botRow[0] < playerRow[0])
           return "player";
         else{
           if(botRow[2] > playerRow[2])
             return "bot";
           else if(botRow[2] < playerRow[2])
             return "player";
           else
             return "tie";
         }
      }else{
        for(int i = 2; i >= 0; i--) {
          if(botRow[i] > playerRow[i])
            return "bot";
          else if(botRow[i] < playerRow[i])
            return "player";
        }
        return "tie";
      }
    }

  }
} //end compareRows

void checkWin(string winner, string row, int &point) {
  if(winner == "tie")
    cout << "tie" << row << " row\n";
  else {
    if(winner == "bot") {
      point += 1;
    }else if(winner == "player") {
      point -= 1;
    }
    cout << winner << " wins " << row << " row\n";
  }
}

void compareHands(Hand bot, Hand player) {
  printf("\n\nBot hand: \n");
  bot.print();

  printf("\n\nYour hand: \n");
  player.print();
  printf("\n");

  int point = 0;
  string winner;
  winner = compareRow(bot.getBottom(), bot.getbRank(), player.getBottom(), player.getbRank());
  checkWin(winner, "bottom", point);

  winner = compareRow(bot.getMiddle(), bot.getmRank(), player.getMiddle(), player.getmRank());
  checkWin(winner, "middle", point);

  winner = compareRow(bot.getTop(), bot.gettRank(), player.getTop(), player.gettRank());
  checkWin(winner, "top", point);

  printf("\n");
  if(point > 0) {
    printf("Bot wins\n");
  }else if(point < 0) {
    printf("player wins\n");
  }else {
    printf("tie game\n");
  }
}





int main() {
  srand(time(0));

  vector<Card> deck = createDeck();
  Shuffle(deck);
//
  Player p1, bot;
  dealCards(deck, p1);
  dealCards(deck, bot);

  bool autowin;
  autowin = strategy.checkAutowin(p1.getHand());
  if(autowin) {
    printf("You win automatically: ");
    helper::displayCards(p1.getHand(), true);
  }

  autowin = strategy.checkAutowin(bot.getHand());
  if(autowin) {
    printf("bot win automatically: ");
    helper::displayCards(bot.getHand(), true);
  }

  vector<Card> currentHand;
  Hand tempHand, botHand;
  if(!autowin) {
    strategy.makeHands(bot.getHand(), currentHand, 0, 0, 10, tempHand);
    botHand = strategy.processTopHands();
  }

  Hand userHand = ui.arrangeHand(p1);
  compareHands(botHand, userHand);


//  bool autowin = strategy.checkAutowin(p1.getHand());


//  vector<Card> currentHand;
//  Hand hand;
//  bool autowin = false;
//  for(int i = 0; i < 1000; i++) {
//    Shuffle(deck);
//    dealCards(deck, p1);
//    printf("bot hand: ");
//    helper::displayCards(p1.getHand(), true);
//    autowin = strategy.checkAutowin(p1.getHand());
//    if(!autowin) {
//      currentHand.clear();
//      strategy.makeHands(p1.getHand(), currentHand, 0, 0, 10, hand);
//      strategy.processTopHands();
//      strategy.clearHands();
//    }
//
//    returnCards(deck, p1);
//    if(!validateDeck(deck)) {
//      printf("[ERROR] cards returned do not match original deck");
//      break;
//    }
//    printf("\n\n");
//  }
//  Hand hand;
//
//  Shuffle(deck);
////  dealCards(deck, p1);
//  regression.badHand9(p1);
//  helper::displayCards(p1.getHand(), true);
//  bool autowin = strategy.checkAutowin(p1.getHand());
//  if(!autowin) {
//    currentHand.clear();
//    strategy.makeHands(p1.getHand(), currentHand, 0, 0, 10, hand);
//    strategy.processTopHands();
//    strategy.clearHands();
//  }


  return 0;
}