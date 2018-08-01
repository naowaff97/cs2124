
#include "std_lib_facilities.h"


int main()
{
    char c = 'a';
    int i = 4096;
    double d = 3.14;
    char* cp = &c;
    int* ip = &i;
    cout << "c = " << c << " its value is " << c << " size of c is " << sizeof(c) << endl;
    cout << "i = " << i << " its value is " << i << " size of i is " << sizeof(i) << endl;
    cout << "d = " << d << " its value is " << d << " size of d is " << sizeof(d) << endl;
    cout << "cp = " << cp << " its value is " << *cp << " size of cp is " << sizeof(cp) << endl;
    cout << "ip = " << ip << " its value is " << *ip << " size of ip is " << sizeof(ip) << endl;

    return 0;
}
