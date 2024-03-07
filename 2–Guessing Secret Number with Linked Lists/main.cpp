// Lutfi Canberk Ilisal
#include <iostream>
#include "feedback.h"

using namespace std;

struct node
{
    int digit;
    node * next;
};

// deallocating dynamically allocated memory
void DeleteList (node *list[])
{
    node *ptr;
    for (unsigned int z=0; z<3; z++)
    {
        while (list[z] != NULL)
        {
            ptr = list[z]->next;
            delete list[z];
            list[z] = ptr;
        }
    }
}

void DisplayList (node * head)
{
    node * ptr = head;
    while (ptr != NULL)
    {
        cout << ptr ->digit << " ";
        ptr = ptr->next;
    }
}

// counts the number of elements
int CountList (node * head)
{
    int num=0;
    node * ptr = head;
    while (ptr != NULL)
    {
        num++;
        ptr = ptr->next;
    }
    return num;
}

// searches specific element in node if element exists returns true
bool SearchNode(node* head, int num) {

    node* ptr = head;

    while (ptr != NULL)
    {
        if (ptr->digit == num)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

/* Begin: code taken from ptrfunc.cpp */
node * AddInOrder(node * head, int num)
// pre: list is sorted
// post: add newkey to list, keep list sorted, return head of new list with newkey in it
{
    node *  ptr = head;   // loop variable

    // if new node should be first, handle this case and return
    // in this case, we return the address of new node since it is new head
    if (head == NULL || num < head->digit)
    {
        node * temp = new node;  //node to be inserted
        temp->digit = num;
        temp->next = head; //connect the rest
        return temp;
    }

    // check node one ahead so we don't pass!
    while (ptr->next != NULL && ptr->next->digit < num)
    {
        ptr = ptr->next;
    } // postcondition: new node to be inserted just after the node that ptr points

    //now insert node with newkey after where ptr points to
    node * temp = new node;  //node to be inserted
    temp->digit = num;
    temp->next = ptr->next; //connect the rest
    ptr->next = temp;

    return head;
}
/* End: code taken from ptrfunc.cpp */

/* Begin: code taken from ptrfunc.cpp and upgraded */
node * DeleteOneNode ( node * head, int num )
/* post: deletes the node pointed by del, updates head if changes */
/* changes:  instead of taking to be deleted node as parameter, takes as int*/
{
    node * ptr;

    // create node for removing integer
    node *del= new node;
    del->digit = num;
    del->next = NULL;

    if ( head == NULL ) // if the node is empty
    {
        return head;
    }
    else if (del->digit == head->digit)  //if the node to be deleted is the first node
    {
        head = head->next;
        delete del;
        del = NULL;
    }
    else  //if the node to be deleted is in the middle or at the end
    {
        ptr = head;
        while ( ptr->next != NULL )
            if ( ptr->next->digit == del->digit ) // checks one node ahead
            {
                break;
            }
            else
            {
                ptr = ptr->next;
            }
        //after while ptr point to the node just before del

        //connect the previous node to the next node and delete
        ptr->next = del->next;
        delete del;
    }

    return head;
}
/* End: code taken from ptrfunc.cpp and upgraded*/

/* controls guess input entered by user */
bool guess_check ( const string& guess )
{
    unsigned int count = 0;
    if ( guess.size() == 3 ) // size should be 3
    {
        if ( guess[0] != guess[1] && guess[1] != guess[2] && guess[0] != guess[2] ) // digits can not be same
        {
            for (unsigned int i = 0; i < 3; i++)
            {
                int digit = guess[i] -'0';
                if (0 <= digit && digit <= 9) // checks whether digits are between 0-9
                {
                    count++;
                }
            }
            if ( count == 3 )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

int main() {

    string feedback, guess;
    int game_id;
    bool valid;

    node* pSlot0 = new node;
    node* pSlot1 = new node;
    node* pSlot2 = new node;
    node* possible[3] = {pSlot0=NULL, pSlot1=NULL, pSlot2=NULL};
    node* ipSlot0 = new node;
    node* ipSlot1 = new node;
    node* ipSlot2 = new node;
    node* impossible[3] = {ipSlot0=NULL, ipSlot1=NULL, ipSlot2=NULL};


    cout << "Please enter a game ID." << endl;
    cin >> game_id;
    cout << "Enter your guess." << endl;
    cin >> guess;
    valid = guess_check(guess);
    while ( !valid ) // until user enters valid input repeats
    {
        cout << "Invalid guess. Enter your guess." << endl;
        cin >> guess;
        valid = guess_check(guess);
    }

    feedback = get_the_feedback ( guess, game_id );
    while ( true )
    {
        for ( unsigned int i=0; i<3; i++ ) // loops between 0-2 to reach every digit
        {
            if (feedback[i] == 'Y')
            {
                // 1-remove n from P list (i) if exist
                possible[i] = DeleteOneNode( possible[i], guess[i] - '0' ); // remove n to P list of slot i

                // 2-insert n to IP list (i) if not exist
                if (!SearchNode(impossible[i], guess[i] - '0')) // check whether n in IP list of slot i
                {
                    impossible[i] = AddInOrder(impossible[i], guess[i]- '0'); // insert n to IP list of slot i
                }

                // 3-insert n to P lists (other than i) if not exist
                for ( unsigned int j=0; j<3; j++)
                {
                    if ( i != j ) // reaching slots that not equal to i
                    {
                        if (!SearchNode(impossible[j], guess[i] - '0')) // check whether n in IP list of slot j
                        {
                            if (!SearchNode(possible[j], guess[i] - '0')) // check whether n in P list of slot j
                            {
                                possible[j] = AddInOrder(possible[j], guess[i]- '0'); // insert n to P list of slot j
                            }
                        }
                    }
                }
            }

            else if (feedback[i] == 'G')
            {
                // 1-insert n to P list (i) if not exist
                if (!SearchNode(possible[i], guess[i] - '0')) // check whether n in P list of slot i
                {
                    possible[i] = AddInOrder(possible[i], guess[i] - '0'); // insert n to P list of slot i
                }
                // 2-insert n to IP lists (other than i) if not exist
                for ( unsigned int l=0; l<3; l++)
                {
                    if ( i != l ) // reaching slots that not equal to i
                    {
                        if (!SearchNode(impossible[l], guess[i] - '0')) // check whether n in IP list of slot l
                        {
                            impossible[l] = AddInOrder(impossible[l], guess[i] - '0'); // insert n to P list of slot i
                            if ( SearchNode(possible[l], guess[i] -'0') ) // check whether n in P list of slot l
                            {
                                possible[l] = DeleteOneNode( possible[l], guess[i] - '0' ); // remove n to P list of slot l
                            }
                        }
                    }
                }

                // 3-remove n from P lists (other than i) if exist
                for ( unsigned int a=0; a<3; a++)
                {
                    if ( i != a ) // reaching slots that not equal to i
                    {
                        possible[a] = DeleteOneNode( possible[a], guess[i] - '0' ); // remove n to P list of slot a
                    }
                }

                // 4-all digits except n, insert to IP list (i) if not exist
                for ( int k=0; k<10; k++)
                {
                    if ( k != guess[i] - '0') // reaching integers that not equal to n
                    {
                        if (!SearchNode(impossible[i], k)) // check whether k in IP list of slot i
                        {
                            impossible[i] = AddInOrder(impossible[i], k); // insert k to IP list of slot i
                            if (SearchNode(possible[i], k)) // check whether k in P list of slot i
                            {
                                possible[i] = DeleteOneNode( possible[i], k ); // remove k to P list of slot i
                            }
                        }
                    }
                }

                // 5-all digits except n, remove from P list (i) if exist
                for ( int b=0; b<10; b++)
                {
                    if ( b != guess[i] - '0') // reaching integers that not equal to n
                    {
                        possible[i] = DeleteOneNode( possible[i], b ); // remove b to P list of slot i

                    }
                }
            }

            else // feedback 'R'
            {
                // 1-insert n to all IP lists
                for (unsigned int c=0; c<3; c++)
                {
                    if (!SearchNode(impossible[c], guess[i] - '0')) // check whether n in IP list of slot c
                    {
                        impossible[c] = AddInOrder(impossible[c], guess[i] - '0'); // insert n to IP list of slot c
                        if (SearchNode(possible[c], guess[c] - '0')) // check whether n in P list of slot c
                        {
                            possible[c] = DeleteOneNode( possible[c], guess[i] - '0' ); // remove n to P list of slot c
                        }
                    }
                }
            }
        }

        // print possibilities and impossibilities for all slots
        cout << "Linked lists:" << endl;
        for (unsigned int d=0; d<3; d++)
        {
            cout << "Slot: "<< d+1 << endl;
            cout << "Impossibles: ";
            DisplayList(impossible[d]);
            cout << endl << "Possibles: ";
            DisplayList(possible[d]);
            cout << endl << endl;
        }

        if (CountList(impossible[0]) == 9 && CountList(impossible[1]) == 9 && CountList(impossible[2]) == 9)
            // check every slot have nine impossibilities
        {
            // if the game ends with not guessing true number possible list(s) may be empty
            // adding true digit(s) to possible list(s) for displaying true number
            for (unsigned int x=0; x<3; x++)
            {
                if (CountList(possible[x]) == 0)
                {
                    for (int y=0; y<10; y++)
                    {
                        if( !SearchNode(impossible[x], y))
                        {
                            possible[x] = AddInOrder(possible[x], y);
                        }
                    }
                }
            }

            int ones, tens, hundreds;
            // taking true digits for displaying secret number
            hundreds = possible[0]->digit;
            tens = possible[1]->digit;
            ones = possible[2]->digit;

            cout << "The secret number is: " << hundreds << tens << ones << endl;
            cout << "Congrats! Now, deleting the lists...";

            // deleting lists
            DeleteList(impossible);
            DeleteList(possible);

            break;
        }
        else {
            cout << "Enter your guess." << endl;
            cin >> guess;
            valid = guess_check(guess);
            while ( !valid )
            {
                cout << "Invalid guess. Enter your guess." << endl;
                cin >> guess;
                valid = guess_check(guess);
            }
            feedback = get_the_feedback(guess, game_id);
        }
    }

    return 0;
}