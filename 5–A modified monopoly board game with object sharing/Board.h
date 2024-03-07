#ifndef BOARD_H
#define BOARD_H

#include <string>

using namespace std;

struct Node {
    string owner;
    Node* next;
    Node ();
    Node ( const string& o, Node* p):owner(o), next(p)
    {};
};

class Board
{
private:
    Node* first;
public:
    Board(const int&);
    ~Board();

    void display() const;
    string who_owns(Node*) const;
    Node* returnFirst() const;
};

#endif
