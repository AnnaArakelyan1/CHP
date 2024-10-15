//encryption
#include <iostream>
#include <string>
using namespace std;

void print(const string& str, int size) {
    for (int i = 0; i < size; i++) {
        cout << str[i];
    }
    cout << endl;
}

string encryption(const string& text, const string& esh, const string& desh, int size) {
    string encr;
    for (int i = 0; i < size; i++) {
        char current = text[i];
        for (int j = 0; j < 26; j++) {
            if (current == esh[j]) {
                encr += desh[j];
                break;
            }
        }
    }
    return encr;
}

int main() {
     string esh, desh;
     
     esh.resize(26); 
    for (int i = 0; i < 26; i++) {
        esh[i] = 'a' + i;
    }
    print(esh, 26);
    
    desh.resize(26); 
    for (int i = 0; i < 24; i++) {
        desh[i] = 'c' + i;
       
    }
     desh[24] = 'a';
      desh[25] = 'b';
    print(desh, 26);
    string text;
    getline(cin,text);
    cout<<endl<<"Current text:";
    print(text,text.length());
    cout<<"encrypted text:";
    string en=encryption(text,esh,desh,text.length());
    cout<<en;
      
      
    return 0;
}
