#include "std_lib_facilities.h"

class vect {
    int sz;
    double* elem;
public:
    vect(int s)
        :sz{s}, elem{new double [s]}  { /*  */ }
    ~vect()
        { delete[] elem; }
    double& operator[](int i) { return elem[i]; }
    void set(int i, double d) { elem[i] = d; }
    vect(const vect& arg)
// allocate space, then initialize via copy
    :sz{arg.sz}, elem{new double[arg.sz]}
{
    copy(arg.elem, arg.elem + arg.sz, elem);  // from std lib
}
    vect& operator=(const vect& a)
// make this vector a copy of a
{
    double* p = new double[a.sz];
    copy(a.elem, a.elem+ a.sz, p);
    delete[] elem;
    elem = p;
    sz = a.sz;
    return *this;  // return self-ref
}

};


void f(int n)
{
    vect v(n);
    v[2] = 2.2;
    vect v2 = v;
    v[1] = 9.9;
    v2[0]= 8.8;
   cout << v[0] << ' ' << v2[1];
}






int main()
{
    int i=0;
    while (i< 10000){
        f(10);
        i++; }

    return 0;
}

