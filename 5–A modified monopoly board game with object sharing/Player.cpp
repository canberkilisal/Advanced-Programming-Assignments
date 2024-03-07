#include "Player.h"
#include <iostream>

// parametric constructor
// creates Player objects with same Board object and different name, balance and position
Player::Player(Board& gameBoard, const string& pName, const int& pBalance) : board(gameBoard), name(pName), balance(pBalance), position(gameBoard.returnFirst())
{}

// updates Player position to right # of step times
// returns 1 if Player passed or stopped on first Node of Board object, otherwise 0
int Player::move(const int& step)
{
    int cond=0;
    for ( unsigned int i=0; i<step; i++)
    {
        position = position->next;
        if ( position == board.returnFirst() )
        {
            cond = 1;
        }
    }
    return cond;
}

// returns Player's position
Node* Player::where_am_I()
{
    return position;
}

// withdraws 'money' from Player on which the object called then deposits 'money' to 'otherPlayer'
void Player::pay_to_player( Player& otherPlayer, const int& money)
{
    balance -= money;
    otherPlayer.balance += money;
}

// returns Player's balance
int Player::get_balance() const
{
    return balance;
}

// adds 'money' to Player's balance
void Player::deposit_money(const int& money)
{
    balance += money;
}

// changes specified Node of the Board objects owner with Player's name
// subtracts 'price' to Player's balance
void Player::buy_slot(const int& price)
{
    position->owner = name;
    balance -= price;
}

// returns true if Player's balance is less than 0, otherwise false
bool Player::is_bankrupt() const
{
    if ( balance < 0 )
    {
        return true;
    }
    return false;
}

// prints Player's position and balance
void Player::display() const
{
    string line;
    Node* ptr = board.returnFirst();
    while ( ptr != position )
    {
        line += "      ";  // adds 6 whitespaces for every passed Node
        ptr = ptr->next;
    }
    cout << line << name << " " << balance << endl;
}
