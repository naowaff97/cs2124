
#include "std_lib_facilities.h"

void print_vector(vector<string>v){
    for (int iter = 0 ; iter < v.size(); iter++){
            cout << v[iter]<<" ";
        }
    cout<<endl;
}


int main(){
    cout << "Enter a phrase: \n";
    vector <string >text;
    for (string temp; cin >> temp;){
        text.push_back(temp);
    }
    //print_vector(text);
    sort(text);
    //print_vector(text);
    int index = 0;
    string prev = text[index];
    int count = 0;
    while (index < text.size()){
            //cout<<index<<" "<<count<<" "<<text[index]<<" "<<prev<<endl;
        if (text[index] == prev){
            count++;

        }else{
            cout << endl<< prev << ": "<< count << endl;
            prev = text[index];
            count = 1;
        }
        index++;


    }
    cout << endl << prev<< ": " << count << endl;
    keep_window_open();
return 0;}





