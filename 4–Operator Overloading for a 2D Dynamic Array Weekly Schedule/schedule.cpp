#include <string>
#include <sstream>
#include "schedule.h"

// empty constructor
// creates Schedule object with 7 rows 0 columns
Schedule::Schedule()
{
    time_slots = 0;

    data = new string*[7];
    for ( unsigned int i=0; i<7; i++ )
    {
        data[i] = nullptr;
    }
}

// constructor with time slot size
// creates Schedule object with 7 rows c columns
// all elements initialized as "free"
Schedule::Schedule( int c )
{
    time_slots = c;

    data = new string*[7];
    for ( unsigned int i=0; i<7; i++ )
        data[i] = new string[c];

    for ( unsigned int i=0; i<7; i++ )
        for ( unsigned int j=0; j<c; j++ )
            data[i][j] = "free";
}

// destructor
Schedule::~Schedule()
{
    for ( unsigned int i=0; i<7; i++ )
        delete [] data[i];

    delete [] data;
    time_slots = 0;
}

// deep-copy constructor
// uses createClone() to copy data
Schedule::Schedule(const Schedule & copy)
{
    time_slots = copy.time_slots;
    data = copy.createClone();
}

// copies data
string** Schedule::createClone() const
{
    string** clone; // creating new dynamic matrix
    clone = new string*[7];
    if ( time_slots == 0 )
    {
        for (unsigned int i = 0; i < 7; i++)
        {
            clone[i] = nullptr;
        }
    }
    else
    {
        for ( unsigned int k=0; k<7; k++ )
            clone[k] = new string[time_slots];
        for ( unsigned int i = 0; i<7; i++ )
            for ( unsigned int j=0; j<time_slots; j++ )
                clone[i][j] = data[i][j];
    }
    return clone;
}

// returns data
string **Schedule::getData() const
{
    return data;
}

// returns time_slots
int Schedule::getTimeSlots() const
{
    return time_slots;
}

// assignment operator
// copies rhs to lhs
const Schedule& Schedule::operator=(const Schedule & rhs)
{
    if ( this != &rhs ) // if lhs and rhs not same
    {
        // deleting lhs
        for ( unsigned int i=0; i<7; i++ )
            delete [] data[i];

        delete [] data;
        time_slots = 0;

        // copying rhs to lhs
        data = rhs.createClone();
        time_slots = rhs.time_slots;
    }
    return *this;
}

// + operator with parameter Days
// copies lhs to new Schedule object
// changes specified row of Schedule object to "busy"
// returns new Schedule object
Schedule Schedule::operator+(Days rhs) const
{
    Schedule temp(*this); // copying lhs

    for ( unsigned int i=0; i<time_slots; i++ )
    {
        temp.data[rhs][i] = "busy";
    }

    return temp;
}

// + operator with parameter int
// copies lhs to new Schedule object
// changes specified column of Schedule object to "busy"
// returns new Schedule object
Schedule Schedule::operator+(int num) const
{
    Schedule temp(*this); // copying lhs

    for ( unsigned int i=0; i<7; i++ )
    {
        temp.data[i][num] = "busy";
    }

    return temp;
}

// + operator with parameter Schedule object
// copies lhs to new Schedule object
// changes elements of Schedule object to "busy" if not both lhs and rhs elements of Schedule objects are "free"
// returns new Schedule object
Schedule Schedule::operator+(const Schedule & rhs) const
{
    Schedule temp(time_slots); // copying lhs

    for ( unsigned int i=0; i<7; i++ )
    {
        for ( unsigned int j=0; j<time_slots; j++)
        {
            if ( !(data[i][j] == "free" && rhs.data[i][j] == "free") )
            {
                temp.data[i][j] = "busy";
            }
        }
    }

    return temp;
}

// * operator with parameter Schedule object
// copies lhs to new Schedule object
// changes elements of Schedule object to "busy" if both lhs and rhs elements of Schedule objects are "busy"
// returns new Schedule object
Schedule Schedule::operator*(const Schedule & rhs) const
{
    Schedule temp(time_slots); // copying lhs

    for ( unsigned int i=0; i<7; i++ )
    {
        for ( unsigned int j=0; j<time_slots; j++)
        {
            if ( data[i][j] == "busy" && rhs.data[i][j] == "busy" )
            {
                temp.data[i][j] = "busy";
            }
        }
    }

    return temp;
}

// [] operator with parameter Days
// returns specified row of Schedule object
string* Schedule::operator[](Days rhs) const
{
    return data[rhs];
}

// < operator with both parameter Schedule object
// returns true if # of "busy" elements of lhs less than # of "busy" elements of rhs
bool operator<(const Schedule& lhs, const Schedule& rhs)
{
    int lhsCount=0, rhsCount=0;

    // counting lhs elements which are "busy"
    for ( unsigned int i=0; i<7; i++ )
    {
        for ( unsigned int j=0; j<lhs.getTimeSlots(); j++)
        {
            if ( lhs.getData()[i][j] == "busy" )
            {
                lhsCount++;
            }
        }
    }

    // counting rhs elements which are "busy"
    for ( unsigned int i=0; i<7; i++ )
    {
        for ( unsigned int j=0; j<rhs.getTimeSlots(); j++)
        {
            if ( rhs.getData()[i][j] == "busy" )
            {
                rhsCount++;
            }
        }
    }

    return lhsCount<rhsCount;
}

// << operator with parameters ostream and Schedule object
// inserts rhs data onto os, returns os
// format is "Day: " Schedule object data("free" or "busy")
ostream& operator<<(ostream& os, const Schedule& rhs)
{
    os << "Mo: ";
    for ( unsigned int i=0; i<rhs.getTimeSlots(); i++ )
    {
        os << rhs.getData()[0][i] << " ";
    }
    os << endl << "Tu: ";
    for ( unsigned int i=0; i<rhs.getTimeSlots(); i++ )
    {
        os << rhs.getData()[1][i] << " ";
    }
    os << endl << "We: ";
    for ( unsigned int i=0; i<rhs.getTimeSlots(); i++ )
    {
        os << rhs.getData()[2][i] << " ";
    }
    os << endl << "Th: ";
    for ( unsigned int i=0; i<rhs.getTimeSlots(); i++ )
    {
        os << rhs.getData()[3][i] << " ";
    }
    os << endl << "Fr: ";
    for ( unsigned int i=0; i<rhs.getTimeSlots(); i++ )
    {
        os << rhs.getData()[4][i] << " ";
    }
    os << endl << "Sa: ";
    for ( unsigned int i=0; i<rhs.getTimeSlots(); i++ )
    {
        os << rhs.getData()[5][i] << " ";
    }
    os << endl << "Su: ";
    for ( unsigned int i=0; i<rhs.getTimeSlots(); i++ )
    {
        os << rhs.getData()[6][i] << " ";
    }
    os << endl;

    return os;
}

// << operator with parameters ostream and Days
// inserts appropriate string onto os, returns os
// puts the name of the day ("Monday", "Tuesday", etc.) corresponding to the value of rhs
ostream& operator<<(ostream& os, Days rhs)
{
    if ( rhs == Monday )
        os << "Monday";

    else if ( rhs == Tuesday )
        os << "Tuesday";

    else if ( rhs == Wednesday )
        os << "Wednesday";

    else if ( rhs == Thursday )
        os << "Thursday";

    else if ( rhs == Friday )
        os << "Friday";

    else if ( rhs == Saturday )
        os << "Saturday";

    else if ( rhs == Sunday )
        os << "Sunday";

    return os;
}