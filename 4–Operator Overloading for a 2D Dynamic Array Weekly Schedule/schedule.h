#ifndef SCHEDULE_H
#define SCHEDULE_H

using namespace std;

enum Days {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

class Schedule
{
private:
    int time_slots;
    string** data;
public:
    Schedule(); // empty constructor
    Schedule(int); // constructor with time slot size
    Schedule(const Schedule &); // deep-copy constructor, uses createClone()
    ~Schedule(); // destructor
    string** createClone() const; // copies data

    string** getData() const; // returns data
    int getTimeSlots() const; // returns time_slots

    const Schedule& operator=(const Schedule&); // assignment operator
    Schedule operator+(Days) const; // + operator with parameter Days
    Schedule operator+(int) const; // + operator with parameter int
    Schedule operator+(const Schedule&) const; // + operator with parameter Schedule
    Schedule operator*(const Schedule&) const; // * operator
    string* operator[](Days) const; // [] operator
};

bool operator<(const Schedule&, const Schedule&); // < operator
ostream& operator<<(ostream&, const Schedule&); // << operator, prints Schedule
ostream& operator<<(ostream&, Days); // << operator, prints Days

#endif
