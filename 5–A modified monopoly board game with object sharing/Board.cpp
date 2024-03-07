#include "Board.h"
#include <iostream>
#include <iomanip>

// parametric constructor
// creates circular linked list with specified length
// assuming that len>=6
Board::Board(const int& len)
{
    // creating first node
    Node *ptr = new Node("None", first);
    first = ptr;
    first->next = first;

    // adding len - 1 nodes to circular linked list
    for (unsigned int i=1; i<len; i++)
    {
        Node *old = first;
        Node *ptr2 = new Node("None", first);
        first = ptr2;

        Node* nextP= old;
        while(nextP->next != old)
        {
            nextP = nextP->next;
        }
        // connecting last node with first node
        nextP->next = first;
    }
}

// destructor
Board::~Board()
{
    if (first != nullptr)
    {
        Node *currentNode = first;
        Node *nextNode = currentNode->next;
        while (nextNode != first)
        {
            currentNode = nextNode;
            nextNode = nextNode->next;
            delete currentNode;

        }
        delete nextNode;
        first = nullptr;
    }
}

void Board::display() const
{
    int count=1;
    string line2, line3;
    Node* ptr = first;

    // printing first line of the Board object
    do
    {
        count++; // counting # of Nodes of the Board object
        cout << left << setw(4) << ptr->owner << "->";  // printing owner name with left aligned and length of four
        ptr = ptr->next;
    } while ( ptr->next != first);

    cout << left << setw(4) << ptr->owner << endl;  // printing last Node's owner

    // printing second line of the Board object
    // first n-1 Node printed with length of 6 ("None->" etc.) but last Node printed with length of 4 ("None" etc.)
    // first lines length is ((count-1)*6)+4 but first and last elements are determined ("^" and "|")
    // so (((count-1)*6)+4)-2 whitespaces added between first and last element
    for (unsigned int i=0; i<(((count-1)*6)+2); i++)
    {
        line2 += " ";
    }
    cout << "^" << line2  << "|" << endl;

    // printing third line of the Board object
    // first and last Node's display are determined ("|----<" and "---v"), middle Nodes have length of 6
    // so count-2 number of "-----<" added between first and last element
    for ( unsigned int j=0; j<(count-2); j++)
    {
        line3 += "-----<";
    }

    cout << "|----<" << line3 << "---v" << endl;
}

// returns owner of the specified Node
string Board::who_owns(Node * loc) const
{
    return loc->owner;
}

// returns first Node of the Board object
Node *Board::returnFirst() const
{
    return first;
}
