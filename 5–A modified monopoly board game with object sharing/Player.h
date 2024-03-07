#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

using namespace std;

class Player
{
private:
    Board & board;
    string name;
    int balance;
    Node* position;
public:
    Player(Board&, const string&, const int&);

    int move(const int&);
    Node* where_am_I();
    void pay_to_player(Player&,const int&);
    int get_balance() const;
    void deposit_money(const int&);
    void buy_slot(const int&);
    bool is_bankrupt() const;
    void display() const;
};

#endif
