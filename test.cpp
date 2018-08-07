
#include "std_lib_facilities.h"


int main()
{
    int i = 0 ;
    int tot = 0;
    while (true)
    {
        double* dptr = new double[10000];
        cout<<"Loop no : "<<i<<endl;
        cout<<"Starting address : "<<&dptr[0]<<endl;
        cout<<"Ending address : "<<&dptr[9999]<<endl;
        cout<<"Byte allocated in this loop : 10000"<<endl;
        cout<<"Byte allocated Until now : "<<tot+10000<<endl;
        tot+=10000;
        i++;
    }
}

/*
On Code::Blocks there were 26458 loops and 264590000 bytes memory allocation.


*/
