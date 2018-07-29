

/*
Outputting dates with << (operator overloading).
Inputting dates with >> (operator overloading).
Overloaded checks for equality (==) and non-equality (!=)
Adding days, months and years to a date.
A default constructor with a default date value
Checking for valid day, month and year. Throw exception if invalid.
Use const functions to tell the compiler day() etc. don't change the date.
Print a long form of the date, i.e., "March 3, 1999" using a vector of month names.
Helper functions for leapyear() and isvalid().
Your main should allow the user to input a date, using your >> operator overload, and employ that date in the rest of your code.
So, the first thing in main() should be a prompt: "Please enter a date in format (YYYY,MM,DD): " Then you should use >> to read the date.
*/

#include "std_lib_facilities.h"

const vector<string>month_names = {     "not_applicable", "January", "February", "March", "April", "May", "June",
                                        "July", "August", "September", "October", "November", "December" };

class date{
public:
    int day, month, year;
    date(int _day, int _month, int _year){
        day = _day;
        month = _month;
        year = _year;
    }
    date(){
        day = 1;
        month = 1;
        year = 1901;
    }
    int get_day() const {return day;}
    int get_month() const {return month;}
    int get_year() const {return year;}
    bool leapyear();
    bool is31();
    bool isvalid();
    void add_year(int y);
    void add_month(int m);
    void add_day(int d);
};


ostream& operator << (ostream& os, const date& d);
istream& operator >> (istream& is, const date& d);
bool operator==(const date& a, const date& b);
bool operator!=(const date& a, const date& b);
