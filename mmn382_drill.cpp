#include "std_lib_facilities.h"

int main(){
    string first_name;
    string friend_name;
    int age;
    cout << "Enter the name of the person you want to write to : ";

    cin >> first_name;
    cout << "Dear " << first_name;
    cin >> friend_name;
    cout << "Have you seen " << friend_name << " lately?";

    cin >> age;
    cout << "I hear you had a birthday and you are now " << age << " years old!";
    if (age <= 0 || age >= 110)
        simple_error(" you're kidding!");
    if (age < 17)
        cout << " You are young to be at NYU!";
    if (age > 65)
        cout << " It's great to see senior students around campus!";


return 0;}
