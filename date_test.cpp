#include "date.h"


int main(){

    date today;
    cin>>today;
    cout<<today<< endl;
    date tomorrow;
    cin >> tomorrow;
    if (today == tomorrow)
        cout << "Dates are same"<< endl;
    else
        cout << "Dates are not same"<< endl;
    if (today.leapyear())
        cout << "It is a leap year" << endl;
    else
        cout << "Not a leap year" << endl;
    today.add_day(300);
    cout << "After adding 300 days: " << today << endl;
    today.add_month(13);
    cout << "After adding 13 months: " << today << endl;
    today.add_year(3);
    cout << "After adding 3 years: " << today << endl;

return 0;}

