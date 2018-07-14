
#include "std_lib_facilities.h"



class Token
{
public:
    char kind;
    double value=0;
    Token(char _ch, double _d){
        kind = _ch;
        value = _d;
    }
};


Token get_token();

vector<Token> tokens;

int main(){
Token t = get_token();
    while(t.kind != 'q'){
        tokens.push_back(t);
        t = get_token();
    }

for(Token tok : tokens){
    if(tok.value < 0  and tok.kind != '8')  cout<<"We received an invalid token of value "<<tok.kind<<endl;
    else if (tok.kind == '8' ) cout<<"A number token with val = "<<tok.value<<endl;
    else cout << "A Token of kind " << tok.kind<<endl;
    }
}

Token get_token(){
    char ch;
    cin >> ch;
    switch(ch)
    {
    case ';': case 'q': case '(': case ')': case '+': case '-': case '/':case '*':
        return Token(ch, 0);
    case '.': case '0':case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    {cin.putback(ch);
    double val;
    cin >> val;
    return Token('8', val);
    }
    default:
        return Token(ch, -1);

    }

}



