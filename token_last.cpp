#include "std_lib_facilities.h"
#include "token.h"


std::ostream &operator<<(std::ostream &os, Token const &t) {
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

Token Token_stream::get() {
    if(buffer.size() > 0) {
        Token t = popback();
        return t;
    }
    char ch;
    cin >> ch;
    switch(ch) {
        case print:case quit:case '(':case ')':case '+':case '-':case '/':case '*':case '=':case mod:case '^':
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


double statement(Token_stream& ts)
{

    Token t = ts.get();
    if(t.kind == name) {
        Token var = t;
        t = ts.get();
        if(t.kind == '=') {  // an assignment
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
            cout << "Write an expression: " << endl;
            cout << "> ";
            Token t = ts.get();
            while(t.kind == print) t = ts.get();
            if(t.kind == quit) return;
            ts.putback(t);
            cout << setprecision(5) << "= " << statement(ts) << '\n';
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
        calculate(ts);
        return 0;
    }
    catch(...)
    {
        cerr << "unknown exception \n";
        return 1;
    }
}
