
#include "std_lib_facilities.h"

const char number = '8';
const char quit = 'q';
const char print = ';';
const string prompt = "> ";
const string result = "= ";



class Token {
public:
    char kind;
    double value;

};





class Token_stream {
    public:
        Token get();
        void putback(Token t);
        void ignore(char c);
    private:
        bool full{false};
        Token buffer;
};



void Token_stream::ignore(char c){
    if(full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;
    char ch = 0;
    while(cin >> ch)
        if(ch == c) return;
}


void Token_stream::putback(Token t){
    buffer = t;
    full = true;
}

Token Token_stream::get() {
if(full) {
    full = false;
    return buffer;
}
char ch;
cin >> ch;
switch(ch) {
    case ';': case 'q': case '(': case ')': case '+': case '-': case '/': case '*': case '%':
        return Token{ch};
    case '.': case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':{
        cin.putback(ch);
        double val;
        cin >> val;
        return Token{'8', val};}
    default:
        return Token{'i', double(ch)};
	}
    return Token{'q'};
}

Token_stream ts;


void print_token(Token t){
cout << "Token.kind = "<< t.kind;

}







double expression();
double term();
double primary();



double expression(){
/* grammar recognized:
 *
 Expression:
    Term
    Expression "+" Term
    Expression "-" Term
 *
 */
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch(t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

double term(){
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':{
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
            }
        case '%':{
            double d = primary();
            if (d == 0) error("divide by zero");
            left = fmod(left, d);
                t = ts.get();
                break;
            }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }

}

double primary()
{
	Token t = ts.get();
    switch (t.kind) {
    case '(':    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return d;
        }
    case number:
        return t.value;
    case '-':
        return -primary();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
}





/*
int main()
{
    cout << "Write an expression: "<< endl << "> ";
    try {
        double val = 0.0;
        while(cin) {
            Token t = ts.get();
// this output is for debugging:
		//	cout << "in main(), got token: " << t.kind
			//	<< " with val of " << t.value << '\n';
            if(t.kind == 'q') break;
            if(t.kind == ';')
                cout << " = " << val << '\n'<<endl<< "> ";
            else
                ts.putback(t);
            val = expression();
        }
        // keep_window_open();   only if needed!
    }
    catch(exception& e) {
        cerr << e.what() << '\n';
        return 1;
    }
    catch(...) {
        cerr << "exception \n";
        return 2;
    }
}
*/

void clean_up_mess(){   // naive version
{
    ts.ignore(print);
}


    while(true) {      // skip until we hit a print
        Token t = ts.get();
        if(t.kind == print) return;
    }
}


void calculate(){
while(cin) {
        try{
    cout << prompt;
    Token t = ts.get();
    while (t.kind == print) t = ts.get();
    if (t.kind == quit) return;
    ts.putback(t);
    cout << result << expression() << endl;
}
    catch(exception& e){
        cerr << e.what() << '\n';
    clean_up_mess();
    }}
}






int main(){
    Token_stream ts;

    try {
        cout<< "Write an expression: " << endl ;
        calculate();
        // keep_window_open();   // only if needed!
        return 0;

    }
    catch(...) {
        cerr << "unknown exception \n";
        return 2;
    }
}





