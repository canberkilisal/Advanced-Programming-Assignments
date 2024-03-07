#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <iomanip>
#include <chrono>
#include <ctime>
#include "IntQueueHW6.h"

using namespace std;

mutex myMutex;

void capture(IntQueueHW6 &chairs, int playerID, struct tm *ptm)
{
    // begin: code taken from threads8.cpp //
    this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(ptm)));
    // end: code taken from threads8.cpp //

    // locking the mutex to prevent synchronization conflicts
    myMutex.lock();

    // if queue is not full enqueue player id then unlock the mutex
    // if queue is full print failure then unlock the mutex
    if ( !chairs.isFull() )
    {
        chairs.enqueue(playerID);
        cout << "Player " << playerID << " captured a chair at " << put_time(ptm,"%X") << endl;
        myMutex.unlock();
    }
    else
    {
        cout << "Player " << playerID << " couldn't capture a chair." << endl;
        myMutex.unlock();
    }
}

int main() {

    int num, id, turn = 0;
    vector<int> players;

    cout << "Welcome to Musical Chairs game!" << endl;
    cout << "Enter the number of players in the game:" << endl;
    cin >> num;
    cout << "Game Start!" << "\n\n";

    // creating num number of threads but not initializing yet
    thread threads[num];

    // creating num number of player id in players vector
    for (int i=0; i<num; i++)
    {
        players.push_back(i);
    }

    // loop until one player left
    while ( players.size() >= 2 )
    {
        // begin: code taken from threads8.cpp //
        time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
        struct tm *ptm = new struct tm;  //creating the time struct to be used in thread
        localtime_s(ptm, &tt);  //converting the time structures
        // end: code taken from threads8.cpp //

        cout << "Time is now " << put_time(ptm,"%X") << endl;

        // normalizing seconds
        if ( ptm->tm_sec>=58)
        {
            ptm->tm_sec = (ptm->tm_sec + 2) % 60;
            ptm->tm_min++;
        }
        else
            ptm->tm_sec = ptm->tm_sec+2;

        // every loop create a new queue with size of one minus player number
        IntQueueHW6 chairs(players.size()-1);

        // initializing all threads
        for (int i = 0; i < players.size(); i++)
        {
            threads[players[i]] = (thread(&capture, ref(chairs), players[i], ptm));
        }

        // make sure that threads have finished
        for (int i = 0; i < players.size(); i++)
        {
            threads[players[i]].join();
        }

        // incrementing turn number by one
        turn++;

        // deleting all players id
        players.clear();

        // put successful players id in back to players id vector
        for (int i = 0; i < num - turn; i++)
        {
            chairs.dequeue(id);
            players.push_back(id);
        }

        cout << "Remaining players are as follows: ";
        for (int i = 0; i < players.size(); i++)
        {
            cout << players[i] << " ";
        }
        cout << "\n\n";
    }

    cout << "Game over!" << endl;
    cout << "Winner is Player " << players[0] << "!";

    return 0;
}
