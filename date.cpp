#include "date.h"
#include "std_lib_facilities.h"

ostream& operator << (ostream& os, const date& d){          // os means output stream
    os<<"("<<month_names[d.month]<<" "<<d.day<<", "<<d.year<<")";
    return os;
}

istream& operator >> (istream& is, date& d){                // is means input stream
    char first, second;
    while(1){
        cout<<"Please enter a date in format YYYY,MM,DD: ";
        is>>d.year>>first>>d.month>>second>>d.day;
        try{
            if(!d.isvalid()) throw 404;
            break;
        }
        catch (int a){
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "An exception occurred. Exception : Invalid Date input\nPlease try again.\n"<<endl;
        }
    }
    return is;
}

bool operator == (const date& a, const date& b) {
    return a.day==b.day && a.month==b.month && a.year==b.year;
}

bool operator != (const date& a, const date& b){
    return a.day!=b.day || a.month!=b.month || a.year!=b.year;
}

bool date :: leapyear(){
    if(year%4) return false;
    else if(year%400 == 0) return true;
    else if(year%100 == 0) return false;
    else return true;
}

bool date :: is31(){
    if(month < 8)  return month%2;
    else return !(month%2);
}

bool date :: isvalid(){
    if((day > 31) || (day > 30 && !is31())) return false;
    else if((month==2 && !leapyear() && day>28) || (month==2 && leapyear() && day>29)) return false;
    else if (month > 12) return false;
    return true;
}

void date::add_year(int y){
    year+=y;
    if(!isvalid()) day--;
}

void date::add_month(int m){
    while(m--){
        month++;
        if(month>12) {
            year++;
            month=1;
        }
    }
    while(!isvalid()) day--;
}

void date::add_day(int d){
    while(d--){
        day++;
        if(month==2){
            if(leapyear() && day == 30) {
                day = 1 ;
                month++;
            }
            else if(!leapyear() && day == 29) {
                day = 1 ;
                month++;
            }
        }
        else{
            if(is31() && day==32) {
                day = 1 ;
                month++;
            }
            else if(!is31() && day==31) {
                day = 1 ;
                month++;
            }
        }
        if(month>12) {
            month=1;
            year++;
        }
    }
}


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

