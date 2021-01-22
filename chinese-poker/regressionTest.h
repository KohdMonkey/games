//
// Created by kohdmonkey on 6/25/18.
//

#ifndef CHINESEPOKER_REGRESSIONTEST_H
#define CHINESEPOKER_REGRESSIONTEST_H
#include "Player.h"

//deal hands for common cases such as full house, and check whether the arrangement is as expected
//weird cases that caused errors

class regressionTest{
 public:
  void badHand1(Player &p1){
    p1.dealCard(Card(2, "C"));
    p1.dealCard(Card(12, "H"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(5, "S"));
    p1.dealCard(Card(10, "S"));
    p1.dealCard(Card(1, "C"));
    p1.dealCard(Card(11, "H"));
    p1.dealCard(Card(4, "D"));
    p1.dealCard(Card(8, "S"));
    p1.dealCard(Card(2, "H"));
    p1.dealCard(Card(13, "D"));
    p1.dealCard(Card(3, "H"));
    p1.dealCard(Card(5, "D"));
  }

  void badHand2(Player &p1){
    p1.dealCard(Card(6, "H"));
    p1.dealCard(Card(8, "C"));
    p1.dealCard(Card(6, "S"));
    p1.dealCard(Card(2, "D"));
    p1.dealCard(Card(11, "D"));
    p1.dealCard(Card(5, "C"));
    p1.dealCard(Card(11, "S"));
    p1.dealCard(Card(12, "S"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(1, "C"));
    p1.dealCard(Card(8, "D"));
    p1.dealCard(Card(3, "S"));
    p1.dealCard(Card(11, "C"));
  }

  //errors
  void badHand3(Player &p1){
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(8, "D"));
    p1.dealCard(Card(12, "D"));
    p1.dealCard(Card(11, "S"));
    p1.dealCard(Card(13, "H"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(5, "H"));
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(7, "H"));
    p1.dealCard(Card(8, "C"));
    p1.dealCard(Card(3, "D"));
    p1.dealCard(Card(2, "D"));
    p1.dealCard(Card(9, "D"));
  }

  void badHand4(Player &p1){
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(7, "S"));
    p1.dealCard(Card(8, "C"));
    p1.dealCard(Card(2, "H"));
    p1.dealCard(Card(3, "C"));
    p1.dealCard(Card(9, "S"));
    p1.dealCard(Card(4, "H"));
    p1.dealCard(Card(5, "S"));
    p1.dealCard(Card(2, "D"));
    p1.dealCard(Card(5, "D"));
    p1.dealCard(Card(3, "S"));
    p1.dealCard(Card(9, "D"));
    p1.dealCard(Card(11, "H"));
  }

  void badHand5(Player &p1){
    p1.dealCard(Card(8, "C"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(12, "S"));
    p1.dealCard(Card(7, "D"));
    p1.dealCard(Card(12, "H"));
    p1.dealCard(Card(6, "C"));
    p1.dealCard(Card(3, "C"));
    p1.dealCard(Card(2, "H"));
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(12, "D"));
    p1.dealCard(Card(1, "C"));
    p1.dealCard(Card(11, "C"));
    p1.dealCard(Card(9, "S"));
  }

  void badHand6(Player &p1){
    p1.dealCard(Card(4, "C"));
    p1.dealCard(Card(7, "S"));
    p1.dealCard(Card(13, "D"));
    p1.dealCard(Card(1, "C"));
    p1.dealCard(Card(8, "C"));
    p1.dealCard(Card(4, "D"));
    p1.dealCard(Card(8, "D"));
    p1.dealCard(Card(5, "S"));
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(3, "D"));
    p1.dealCard(Card(3, "S"));
    p1.dealCard(Card(4, "H"));
    p1.dealCard(Card(7, "D"));
  }

  void badHand7(Player &p1){
    p1.dealCard(Card(2, "C"));
    p1.dealCard(Card(7, "C"));
    p1.dealCard(Card(8, "C"));
    p1.dealCard(Card(2, "H"));
    p1.dealCard(Card(1, "C"));
    p1.dealCard(Card(5, "S"));
    p1.dealCard(Card(2, "S"));
    p1.dealCard(Card(8, "S"));
    p1.dealCard(Card(8, "D"));
    p1.dealCard(Card(4, "C"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(11, "C"));
    p1.dealCard(Card(11, "H"));
  }

  void badHand8(Player &p1){
    p1.dealCard(Card(12, "H"));
    p1.dealCard(Card(10, "H"));
    p1.dealCard(Card(3, "D"));
    p1.dealCard(Card(3, "C"));
    p1.dealCard(Card(6, "S"));
    p1.dealCard(Card(7, "D"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(7, "H"));
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(5, "H"));
    p1.dealCard(Card(5, "S"));
    p1.dealCard(Card(13, "S"));
    p1.dealCard(Card(13, "D"));
  }

  void badHand9(Player &p1){
    p1.dealCard(Card(4, "H"));
    p1.dealCard(Card(3, "D"));
    p1.dealCard(Card(7, "H"));
    p1.dealCard(Card(10, "H"));
    p1.dealCard(Card(6, "H"));
    p1.dealCard(Card(5, "C"));
    p1.dealCard(Card(11, "C"));
    p1.dealCard(Card(8, "H"));
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(1, "H"));
    p1.dealCard(Card(13, "D"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(8, "D"));
  }

  void twotripletwopairs(Player &p1){
    p1.dealCard(Card(3, "D"));
    p1.dealCard(Card(9, "H"));
    p1.dealCard(Card(1, "S"));
    p1.dealCard(Card(7, "H"));
    p1.dealCard(Card(1, "H"));
    p1.dealCard(Card(13, "C"));
    p1.dealCard(Card(3, "S"));
    p1.dealCard(Card(11, "S"));
    p1.dealCard(Card(13, "S"));
    p1.dealCard(Card(1, "C"));
    p1.dealCard(Card(2, "S"));
    p1.dealCard(Card(2, "H"));
    p1.dealCard(Card(13, "D"));
  }

  void fourtriples(Player &p1){
    p1.dealCard(Card(1, "H"));
    p1.dealCard(Card(3, "H"));
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(10, "D"));
    p1.dealCard(Card(10, "H"));
    p1.dealCard(Card(7, "D"));
    p1.dealCard(Card(1, "S"));
    p1.dealCard(Card(7, "S"));
    p1.dealCard(Card(7, "H"));
    p1.dealCard(Card(3, "C"));
    p1.dealCard(Card(3, "D"));
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(4, "S"));
  }

  void fourofakind(Player &p1){
    p1.dealCard(Card(8, "C"));
    p1.dealCard(Card(8, "S"));
    p1.dealCard(Card(8, "H"));
    p1.dealCard(Card(8, "D"));
    p1.dealCard(Card(12, "H"));
    p1.dealCard(Card(6, "C"));
    p1.dealCard(Card(3, "C"));
    p1.dealCard(Card(2, "H"));
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(12, "D"));
    p1.dealCard(Card(1, "C"));
    p1.dealCard(Card(11, "C"));
    p1.dealCard(Card(9, "S"));
  }

  void straightflush(Player &p1){
    p1.dealCard(Card(8, "C"));
    p1.dealCard(Card(9, "C"));
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(11, "C"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(6, "C"));
    p1.dealCard(Card(3, "C"));
    p1.dealCard(Card(2, "H"));
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(12, "D"));
    p1.dealCard(Card(1, "C"));
    p1.dealCard(Card(11, "S"));
    p1.dealCard(Card(9, "S"));
  }

  void sixpairs(Player &p1){
    p1.dealCard(Card(8, "C"));
    p1.dealCard(Card(8, "S"));
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(10, "S"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(12, "S"));
    p1.dealCard(Card(3, "C"));
    p1.dealCard(Card(3, "H"));
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(1, "S"));
    p1.dealCard(Card(11, "C"));
    p1.dealCard(Card(11, "S"));
    p1.dealCard(Card(9, "S"));
  }


  void badFullHouse(Player &p1){
    p1.dealCard(Card(1, "H"));
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(11, "S"));
    p1.dealCard(Card(6, "H"));
    p1.dealCard(Card(9, "C"));
    p1.dealCard(Card(10, "D"));
    p1.dealCard(Card(3, "D"));
    p1.dealCard(Card(8, "S"));
    p1.dealCard(Card(1, "S"));
    p1.dealCard(Card(11, "H"));
    p1.dealCard(Card(5, "S"));
    p1.dealCard(Card(11, "D"));
    p1.dealCard(Card(13, "D"));
  }

  void fullHouseFlush(Player &p1){
    p1.dealCard(Card(2, "S"));
    p1.dealCard(Card(13, "H"));
    p1.dealCard(Card(2, "H"));
    p1.dealCard(Card(10, "H"));
    p1.dealCard(Card(7, "H"));
    p1.dealCard(Card(5, "C"));
    p1.dealCard(Card(11, "H"));
    p1.dealCard(Card(13, "S"));
    p1.dealCard(Card(13, "C"));
    p1.dealCard(Card(3, "S"));
    p1.dealCard(Card(1, "H"));
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(7, "D"));
  }

  void fullHousePairtop(Player &p1){
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(12, "S"));
    p1.dealCard(Card(2, "C"));
    p1.dealCard(Card(7, "H"));
    p1.dealCard(Card(10, "S"));
    p1.dealCard(Card(3, "D"));
    p1.dealCard(Card(2, "D"));
    p1.dealCard(Card(6, "S"));
    p1.dealCard(Card(12, "D"));
    p1.dealCard(Card(5, "S"));
    p1.dealCard(Card(12, "H"));
    p1.dealCard(Card(4, "S"));
    p1.dealCard(Card(11, "D"));
  }

  void triplefourpairs(Player &p1){
    p1.dealCard(Card(5, "H"));
    p1.dealCard(Card(6, "C"));
    p1.dealCard(Card(6, "H"));
    p1.dealCard(Card(7, "C"));
    p1.dealCard(Card(7, "S"));
    p1.dealCard(Card(7, "D"));
    p1.dealCard(Card(10, "H"));
    p1.dealCard(Card(10, "S"));
    p1.dealCard(Card(11, "D"));
    p1.dealCard(Card(12, "S"));
    p1.dealCard(Card(12, "H"));
    p1.dealCard(Card(13, "S"));
    p1.dealCard(Card(13, "D"));
  }

  void twopairsalltrash(Player &p1){
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(2, "D"));
    p1.dealCard(Card(3, "S"));
    p1.dealCard(Card(4, "S"));
    p1.dealCard(Card(4, "H"));
    p1.dealCard(Card(6, "C"));
    p1.dealCard(Card(6, "D"));
    p1.dealCard(Card(7, "S"));
    p1.dealCard(Card(8, "H"));
    p1.dealCard(Card(9, "S"));
    p1.dealCard(Card(11, "H"));
    p1.dealCard(Card(12, "H"));
    p1.dealCard(Card(13, "C"));
  }

  void fivepairs(Player &p1){
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(1, "S"));
    p1.dealCard(Card(3, "H"));
    p1.dealCard(Card(3, "C"));
    p1.dealCard(Card(6, "S"));
    p1.dealCard(Card(8, "H"));
    p1.dealCard(Card(8, "C"));
    p1.dealCard(Card(9, "S"));
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(10, "S"));
    p1.dealCard(Card(11, "H"));
    p1.dealCard(Card(11, "S"));
    p1.dealCard(Card(12, "D"));
  }

  void twostraight(Player &p1) {
    p1.dealCard(Card(2, "H"));
    p1.dealCard(Card(1, "C"));
    p1.dealCard(Card(9, "C"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(12, "H"));
    p1.dealCard(Card(8, "S"));
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(4, "D"));
    p1.dealCard(Card(9, "S"));
    p1.dealCard(Card(5, "H"));
    p1.dealCard(Card(11, "D"));
    p1.dealCard(Card(3, "C"));
    p1.dealCard(Card(10, "H"));
  }

  void twostraightonetriple(Player &p1) {
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(2, "S"));
    p1.dealCard(Card(3, "S"));
    p1.dealCard(Card(4, "S"));
    p1.dealCard(Card(5, "D"));
    p1.dealCard(Card(5, "S"));
    p1.dealCard(Card(3, "D"));
    p1.dealCard(Card(5, "S"));
    p1.dealCard(Card(9, "D"));
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(11, "D"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(13, "D"));
  }

  void twostraightsonepair(Player &p1) {
    p1.dealCard(Card(1, "D"));
    p1.dealCard(Card(2, "S"));
    p1.dealCard(Card(3, "D"));
    p1.dealCard(Card(4, "D"));
    p1.dealCard(Card(5, "D"));
    p1.dealCard(Card(6, "S"));
    p1.dealCard(Card(7, "C"));
    p1.dealCard(Card(5, "C"));
    p1.dealCard(Card(8, "S"));
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(11, "S"));
    p1.dealCard(Card(12, "H"));
    p1.dealCard(Card(13, "S"));
  }

  void twotriplethreepairs(Player &p1) {
    p1.dealCard(Card(1, "H"));
    p1.dealCard(Card(1, "S"));
    p1.dealCard(Card(2, "S"));
    p1.dealCard(Card(2, "H"));
    p1.dealCard(Card(3, "C"));
    p1.dealCard(Card(3, "H"));
    p1.dealCard(Card(5, "S"));
    p1.dealCard(Card(5, "C"));
    p1.dealCard(Card(5, "D"));
    p1.dealCard(Card(6, "S"));
    p1.dealCard(Card(6, "C"));
    p1.dealCard(Card(6, "D"));
    p1.dealCard(Card(13, "H"));
  }

  void twotriplethreepairs1(Player &p1) {
    p1.dealCard(Card(3, "D"));
    p1.dealCard(Card(3, "S"));
    p1.dealCard(Card(3, "C"));
    p1.dealCard(Card(10, "S"));
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(12, "H"));
    p1.dealCard(Card(12, "S"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(11, "C"));
    p1.dealCard(Card(11, "S"));
    p1.dealCard(Card(7, "C"));
    p1.dealCard(Card(9, "S"));
    p1.dealCard(Card(9, "D"));
  }

  void onestraightoneflush(Player &p1) {
    p1.dealCard(Card(1, "S"));
    p1.dealCard(Card(2, "S"));
    p1.dealCard(Card(3, "C"));
    p1.dealCard(Card(4, "H"));
    p1.dealCard(Card(5, "D"));
    p1.dealCard(Card(13, "H"));
    p1.dealCard(Card(13, "D"));
    p1.dealCard(Card(4, "D"));
    p1.dealCard(Card(5, "S"));
    p1.dealCard(Card(6, "C"));
    p1.dealCard(Card(7, "C"));
    p1.dealCard(Card(10, "C"));
    p1.dealCard(Card(10, "S"));
  }

  void flushtwopairs(Player &p1) {
    p1.dealCard(Card(1, "S"));
    p1.dealCard(Card(1, "C"));
    p1.dealCard(Card(2, "S"));
    p1.dealCard(Card(3, "D"));
    p1.dealCard(Card(4, "S"));
    p1.dealCard(Card(5, "H"));
    p1.dealCard(Card(5, "S"));
    p1.dealCard(Card(7, "C"));
    p1.dealCard(Card(8, "H"));
    p1.dealCard(Card(9, "S"));
    p1.dealCard(Card(12, "D"));
    p1.dealCard(Card(12, "C"));
    p1.dealCard(Card(13, "S"));
  }

};



#endif //CHINESEPOKER_REGRESSIONTEST_H
