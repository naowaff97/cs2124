#include "std_lib_facilities.h"
#include "token.h"
#include "geo.h"
#include <map>


ostream &operator<<(ostream &os, Token const &t) {
    return os << t.kind;
}


void Token_stream::putback(Token t)
{
    buffer.push_back(t);
}

Token Token_stream::popback()
{
    Token t = buffer.back();
    buffer.pop_back();
    return t;
}

map< string, function<double(double)> > dispTable {
    {"sin", [](double a) { return sin(a); }},
    {"cos", [](double a) { return cos(a); }},
    {"tan", [](double a) { return tan(a); }},
    {"asin", [](double a) { return sini(a); }},
    {"acos", [](double a) { return cosi(a); }},
    {"atan", [](double a) { return tani(a); }},
    {"log", [](double a) { return log(a); }},
    {"log2", [](double a) { return log2(a); }},
    {"log10", [](double a) { return log10(a); }},
};

double exec_func(string fname, double arg)
{
    try {
        return dispTable[fname](arg);
    }
    catch(exception) {
        cout << "Error: undefined function " << fname << '\n';
    }
    return 0.0;   // stop compiler warning!
}


Token Token_stream::get() {
    if(buffer.size() > 0) {
        Token t = popback();
        return t;
    }
    char ch;
    cin >> ch;
    switch(ch) {
        case 'a':case 'c': case 'l': case 's' : case 't':{
            cin.putback(ch);
            string check;
            cin>>check;
            int sz = check.size();
            for(int i=0; i<sz; i++) if(dispTable.find(check.substr(0, i+1))!=dispTable.end()) {
                string op = check.substr(0, i+1);
                if(op == "log") {
                    if(i+1 < sz and check[i+1]=='2') op = "log2" , i++;
                    else if(i+2 < sz and check[i+1]=='1' and check[i+2]=='0') op = "log10" , i+=2;
                }
                string value = check.substr(i+1, sz);
                bool is_start = false;
                sz = value.size();
                while(sz--){
                    if(value[sz]==')') is_start = true;
                    else if (value[sz]=='(') break;
                    if (is_start) cin.putback(value[sz]);
                }
                Token_stream ts;
                Token t = ts.get();
                ts.putback(t);
                double num = statement(ts);
                return Token (geo, exec_func(op, num) < exp ? 0 : exec_func(op, num));
            }
            return Token{invalid, -1};
        }
        case 'q': {
            cin.putback(ch);
            string check, _check;
            cin>>check;
            int sz = check.size();
            for(int i = 0 ; i<sz; i++) {
                _check+=tolower(check[i]);
                if(_check == "qua") return Token{qua, -1};
            }
            return Token{ch};
        }
        case 'h': {
            cin.putback(ch);
            string check, _check;
            cin>>check;
            int sz = check.size();
            for(int i = 0 ; i<sz; i++) {
                _check+=tolower(check[i]);
                if(_check == "help") return Token{help, -1};
            }
            return Token{ch};
        }
        case print :case '(':case ')':case '+':case '-':case '/':case '*':case '=':case mod:case '^':
            return Token{ch};
        case '.':case '0': case '1': case '2': case '3': case '4':case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);
            double val;
            cin >> val;
            return Token{number, val};
        }
        default:
            if(isalpha(ch)) {
                string s;
                s += ch;
                while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
                cin.putback(ch);
                return Token{name, s};
            }
            return Token{invalid, double(ch)};
    }
    return Token{quit};
}

void Token_stream::ignore(char c)
{
    while(buffer.size() > 0) {
        Token t = popback();
        if(t.kind == c) return;
    }

    // now search input:
    char ch = 0;
    while(cin>>ch)
        if(ch == c) return;
}

void helper()
{
    freopen("help.txt", "r", stdin);
    string input;
    int coun = 0 ;
    while(cin>>input){
        cout<<input<<" ";
        coun++;
        coun%=15;
        if(!coun) cout<<endl;
    }
    fclose(stdin);
    /* cout<<"-----How to use this calculator-----" << endl;
    cout << "--> Write an expression such as \"1+5*(2+3)/(8*2/30)' followed by a ';' and enter." << endl;
    cout << "--> Assign variables such as 'x = 5*5-(2*3/5)' followed by a ';' and enter, and use the value of x to use in other expressions as '(x*4)^4' or 'sin(2*x-10)'." << endl;
    cout << "--> To use trigonometric functions such as sin, cos or tan, simply type 'sin(2*x-10)' (This is only applicable if x has been assigned beforehand)" << endl;
    cout << "--> To find the roots of a quadratic expression such as 'ax^2+bx+c', type 'qua' and then follow the instructions." << endl;
    cout << "--> If you happen to see 'primary expected' or 'unknown exception', type ';' followed by enter to continues using the calculator." << endl;
    cout << "--> To quit type 'q' and enter." << endl;
    */
}


void roots() {

    double a, b, c, root_1, root_2, under_square_root, real, imaginary;
    cout << "Enter coefficients a, b and c (ax^2+bx+c): "<< endl;
    cout << "Coefficient of x^2 (a) = ";
    cin >> a ;
    cout << '\n' <<"Coefficient of x (b) = ";
    cin >> b;
    cout <<'\n'<< "Coefficient of x^0 (c) =  ";
    cin >> c;
    under_square_root = (b*b) - (4*a*c);

    if (under_square_root > 0) {
        root_1 = (-b + sqrt(under_square_root)) / (2*a);
        root_2 = (-b - sqrt(under_square_root)) / (2*a);
        cout << "Roots are real and different." << endl;
        cout << "First root = " << root_1 << endl;
        cout << "Second root = " << root_2 << endl;
    }

    else if (under_square_root == 0) {
        cout << "Roots are real and same." << endl;
        root_1 = (-b + sqrt(under_square_root)) / (2*a);
        cout << "They both have the same root" << root_1 << endl;
    }

    else {
        real = -b/(2*a);
        imaginary =sqrt(-under_square_root)/(2*a);
        cout << "Roots are complex and different."  << endl;
        cout << "First root = " << real << "+" << imaginary << "i" << endl;
        cout << "Second root = " << real << "-" << imaginary << "i" << endl;
    }
}


double statement(Token_stream& ts)
{
    Token t = ts.get();
    if(t.kind==geo) {
        return t.value;
    }
    else if(t.kind == qua){
        roots();
        return t.value;
    }
    else if(t.kind == help){
        helper();
        return t.value;
    }
    else if(t.kind == name) {
        Token var = t;
        t = ts.get();
        if(t.kind == '=') {
            double d = expression(ts);
            set_value(var.name, d);
            return d;
        }
        else if(t.kind == print) {
            ts.putback(t);
            return get_value(var.name);
        }
        ts.putback(t);
        ts.putback(var);
        return expression(ts);
    }
    ts.putback(t);
    return expression(ts);
}

double expression(Token_stream& ts)
{

    double left = term(ts);
    Token t = ts.get();
    while(true) {
        switch(t.kind) {
        case '+':
            left += term(ts);
            t = ts.get();
            break;
        case '-':
            left -= term(ts);
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

double term(Token_stream& ts)
{
    double left = expon(ts);
    Token t = ts.get();
    while(true) {
        switch (t.kind) {
        case '*':
            left *= expon(ts);
            t = ts.get();
            break;
        case '/':
            {
                double d = expon(ts);
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
        case '%':
            {
                double d = expon(ts);
                if (d == 0) error("divide by zero");
                left = fmod(left, d);
                t = ts.get();
                break;
            }
        default:
            ts.putback(t);
            return left;
        }
    }

}

double expon(Token_stream& ts)
{
    double left = primary(ts);
    Token t = ts.get();
    if(t.kind == '^') {
        double d = primary(ts);
        return pow(left, d);
    }
    else {
        ts.putback(t);
        return left;
    }
}

double primary(Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':
        {
            double d = expression(ts);
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
    case number:
        return t.value;
    case name:
        return get_value(t.name);
    case '-':
        return -primary(ts);
    case '+':
        return primary(ts);
    default:
        error("primary expected");
    }
    return 0.0;
}


vector<Variable> var_table;

double get_value(string s)
{
    for(Variable var : var_table)
        if(var.name == s) return var.value;

    return 0.0;
}

void set_value(string s, double d)
{
    for(Variable& var : var_table)
        if(var.name == s) {
            var.value = d;
            return;
        }
    // if var not in table, we choose to add it:
    var_table.push_back(Variable{s, d});
}

void print_vars()
{
    for(Variable var : var_table)
        cout << "Var " << var.name << " = " << var.value << endl;
}
void clean_up_mess(Token_stream& ts)
{
    ts.ignore(print);
}

void calculate(Token_stream& ts)
{

    while(cin) {
        try {
            cout << "Write an expression (for help type: help): " << endl;
            cout << "> ";
            Token t = ts.get();
            while(t.kind == print) t = ts.get();
            if(t.kind == quit) return;
            ts.putback(t);
            if(t.kind == qua or t.kind == help) statement(ts);
            else cout << setprecision(5) << "= " << statement(ts) << '\n';
        }
        catch(exception& e) {
            cerr << e.what() << '\n';
            clean_up_mess(ts);
        }
    }

}




int main()
{
    Token_stream ts;
    try
    {
        set_value("pi", 3.1415926535);
    set_value("e", 2.7182818284);
        calculate(ts);
        return 0;
    }
    catch(...)
    {
        cerr << "unknown exception \n";
        return 1;
    }
}
