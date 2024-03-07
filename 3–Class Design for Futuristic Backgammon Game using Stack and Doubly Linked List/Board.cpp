#include <iostream>
#include "Board.h"
using namespace std;

// default constructor
Board::Board()
{
    head = nullptr;
    tail = nullptr;
    xCnt = 0;
    oCnt = 0;
}

// takes two parameters, a character for the player and an integer for the steps to move
// It returns true, if there is no possible valid move of that player; returns false otherwise
bool Board::noMove(char ch, int steps)
{
    slot* ptr = head;
    bool cond = true;

    // loops until reaching end of the board or finding any possible move
    while(ptr != nullptr && cond )
    {
        // checks whether pointed slot is empty
        if ( ptr->slotStack.isEmpty() )
        {
            ptr = ptr->next;
        }
            // pointed slot is not empty
        else
        {
            // creating char variables to check popped char is same with  player ch
            char slotCh, slotChRight, slotChLeft;
            // creating CharStack variable with copy constructor to avoid pop member function changes
            CharStack copyPtrStack(ptr->slotStack);
            copyPtrStack.pop(slotCh);
            // if player char and popped char is not equal continue with next stack
            if ( slotCh != ch )
            {
                ptr = ptr->next;
            }
                // checks whether there are any moves at left or right
            else
            {
                slot* ptrRight = ptr;
                slot* ptrLeft = ptr;
                // creating two boolean variable to determine can right and left slots exist
                bool condRight=true, condLeft=true;
                // moving from source stack to left and right
                // if there are no stack returns cond to false
                for (unsigned int i=0; i < steps; i++)
                {
                    if ( ptrRight->next != nullptr)
                    {
                        ptrRight = ptrRight->next;
                    }
                    else
                    {
                        condRight = false;
                    }

                    if ( ptrLeft->prev != nullptr)
                    {
                        ptrLeft = ptrLeft->prev;
                    }
                    else
                    {
                        condLeft = false;
                    }
                }

                CharStack rightStack(ptrRight->slotStack);
                CharStack leftStack(ptrLeft->slotStack);
                // both left and right stacks have element(s)
                if ( condRight && condLeft )
                {
                    // if right side of source stack contains element that not equal to player char
                    if ( rightStack.pop(slotChRight) && slotChRight != ch )
                    {
                        cond = true;
                    }
                        // if left side of source stack contains element that not equal to player char
                    else if ( leftStack.pop(slotChLeft) && slotChLeft != ch )
                    {
                        cond = true;
                    }
                        // if one of the side stacks contain element that equal to player char
                    else
                    {
                        cond = false;
                    }
                }
                    // only right side of source stack has element(s)
                else if ( condRight )
                {
                    if ( rightStack.pop(slotChRight) && slotChRight != ch )
                    {
                        cond = true;
                    }
                    else
                    {
                        cond = false;
                    }
                }
                    // only left side of source stack has element(s)
                else if ( condLeft )
                {
                    if ( leftStack.pop(slotChLeft) && slotChLeft != ch )
                    {
                        cond = true;
                    }
                    else
                    {
                        cond = false;
                    }
                }
                    // both left and right stacks have no element
                else
                {
                    cond = true;
                }

                ptr = ptr->next;
            }
        }
    }

    return cond;
}
// takes 4 parameters, player character, start index, amount of steps and direction of move
// return 1 if entered slot index is not within bounds
// return 4 if entered slot index does not belong to the player
// return 2 if target slot index not within bounds
// return 3 if target slot index is not empty or does not belong to the player
// checks are performed in the order above
int Board::validMove(char ch, int start, int step, int direction)
{
    slot* countSlot = head;
    slot* ptr1 = head;
    slot* ptr2 = head;
    int count=0;
    char popCh1, popCh2;

    // counting slots
    while ( countSlot->next != nullptr )
    {
        count++;
        countSlot = countSlot->next;
    }

    if( start > count )
    {
        return 1;
    }

    for ( unsigned int k=0; k<start; k++)
    {
        ptr2 = ptr2->next;
    }
    CharStack ptr2Pop(ptr2->slotStack);
    if ( !ptr2Pop.pop(popCh2) || popCh2 != ch )
    {
        return 4;
    }

    if ( direction == 1 ) // moving right
    {
        if (start + step > count )
        {
            return 2;
        }
    }
    else // moving left
    {
        if ( start - step < 0 )
        {
            return 2;
        }
    }

    for ( unsigned int j=0; j<start; j++)
    {
        ptr1 = ptr1->next;
    }
    if (direction == 1) // moving right
    {
        for ( unsigned int i=0; i<step; i++)
            ptr1 = ptr1->next;
    }
    else // moving left
    {
        for ( unsigned int i=0; i<step; i++)
            ptr1 = ptr1->prev;
    }

    CharStack ptr1Pop(ptr1->slotStack);
    if ( ptr1Pop.pop(popCh1) && popCh1 != ch )
    {
        return 3;
    }


    return 0;
}

// takes two parameters, source index to pop and target index to push
// with pop and push member functions moves one piece to another stack
bool Board::movePiece(int source, int target)
{
    slot* popSlot = head;
    slot * pushSlot = head;
    char ch;

    for ( unsigned int i=0; i<source; i++)
    {
        popSlot = popSlot->next;
    }
    popSlot->slotStack.pop(ch);

    for ( unsigned int j=0; j<target; j++)
    {
        pushSlot = pushSlot->next;
    }
    pushSlot->slotStack.push(ch);

    return false;
}

// prints board
// uses copy constructor to pop elements from stack in order to do not affect board stack elements
void Board::printBoard()
{
    slot* ptr = head;
    string line[5];
    char ch;

    // creating string array to print board
    while (ptr != nullptr)
    {
        line[0] += '^';
        CharStack copyStack(ptr->slotStack);
        for (unsigned int i=1; i<5; i++)
        {
            if (copyStack.pop(ch))
            {
                line[i] += ch;
            }
            else
            {
                line[i] += ' ';
            }
        }
        ptr = ptr->next;
    }

    // printing board
    for (int i=4; i>=0; i--)
    {
        for (unsigned int j=0; j < line[i].size(); j++)
        {
            cout << line[i][j];
        }
        cout << endl;
    }


}
// returns 1 if x has less pieces than o
// returns 2 if o has less pieces than x
// returns 3 if x and o have equal pieces
int Board::evaluateGame() const
{
    if ( xCnt < oCnt )
    {
        return 1;
    }
    else if ( oCnt < xCnt )
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

// takes target slot index as parameter
// returns true if stack is full, false otherwise
bool Board::targetSlotFull(int target)
{
    slot* ptr = head;

    for (unsigned int i=0; i < target; i++ )
    {
        ptr = ptr->next;
    }

    if (ptr->slotStack.isFull())
    {
        return true;
    }

    return false;
}

// takes target slot index as parameter
// deletes target slot and decreases player char count by 4
void Board::destroySlot(int target)
{
    slot* ptr = head;
    char ch;

    for (unsigned int i=0; i < target; i++ )
    {
        ptr = ptr->next;
    }

    ptr->slotStack.pop(ch);
    if ( ch == 'x' )
    {
        xCnt = xCnt - 4;
    }
    else
    {
        oCnt = oCnt - 4;
    }

    // if slot to be deleted is head
    if ( ptr == head )
    {
        head = head->next;
        head-> prev = nullptr;
        delete ptr;
    }
        // if slot to be deleted is tail
    else if ( ptr == tail )
    {
        tail = tail->prev;
        tail-> next = nullptr;
        delete ptr;
    }
        // if slot to be deleted is in the middle of list
    else
    {
        slot* ptrLeft = ptr->prev;
        slot* ptrRight = ptr->next;
        ptrLeft-> next = ptrRight;
        ptrRight-> prev = ptrLeft;
        delete ptr;
    }
}

// takes two parameters, player character and  number of characters
// creates a slot at the head of the list with given the number of characters in it
void Board::createSlotBegin(char ch, int num)
{
    slot* x = new slot;
    CharStack y;
    for (unsigned int i =0; i < num; i++)
    {
        if ( y.push(ch) )
        {
            if ( ch == 'x' )
            {
                xCnt++;
            }
            else
            {
                oCnt++;
            }
        }
    }
    x->prev = nullptr;
    x->next = head;
    x->slotStack = y;
    head->prev = x;
    head = head->prev;
}

// takes two parameters, player character and  number of characters
// creates a slot at the end of the list with given the number of characters in it
void Board::createSlotEnd(char ch, int num)
{
    slot* x = new slot;

    // if the list is empty
    if (head == nullptr)
    {
        CharStack y;
        for (unsigned int i =0; i<num; i++)
        {
            if ( y.push(ch) )
            {
                if ( ch == 'x' )
                {
                    xCnt++;
                }
                else
                {
                    oCnt++;
                }
            }
        }
        x->prev = nullptr;
        x->next = nullptr;
        x->slotStack = y;
        head = x;
        tail = x;
    }

        // if the list has one slot
    else if ( head->next == nullptr )
    {
        CharStack y;
        for (unsigned int i =0; i<num; i++)
        {
            if ( y.push(ch) )
            {
                if (ch == 'x')
                {
                    xCnt++;
                }
                else
                {
                    oCnt++;
                }
            }
        }
        x->prev = head;
        x->next = nullptr;
        x->slotStack = y;
        tail = x;
        head->next = tail;
    }
        // if the list has more than one slot
    else
    {
        CharStack y;
        for (unsigned int i =0; i<num; i++)
        {
            if ( y.push(ch) )
            {
                if (ch == 'x')
                {
                    xCnt++;
                }
                else
                {
                    oCnt++;
                }
            }
        }
        x->prev = tail;
        x->next = nullptr;
        x->slotStack = y;
        tail->next = x;
        tail = tail->next;
    }
}

// creates an empty slot at the end of the list
void Board::createEmptySlotEnd()
{
    slot* x = new slot;

    // if the list is empty
    if ( head == nullptr )
    {
        CharStack y;
        x->prev = nullptr;
        x->next = nullptr;
        x->slotStack = y;
        head = x;
        tail = x;
    }

        // if the list has one slot
    else if ( head->next == nullptr )
    {
        CharStack y;
        x->prev = head;
        x->next = nullptr;
        x->slotStack = y;
        head->next = x;
        tail->next = x;
        tail = x;
    }

        // if the list has more than one slot
    else
    {
        CharStack y;
        x->prev = tail;
        x->next = nullptr;
        x->slotStack = y;
        tail->next = x;
        tail = x;
    }
}

// deletes all slots and makes x and o count equal to 0
void Board::clearBoard()
{
    slot* ptr;
    while ( head != nullptr )
    {
        ptr = head;
        head = head->next;
        delete ptr;
    }
    tail = nullptr;

    xCnt = 0;
    oCnt = 0;
}