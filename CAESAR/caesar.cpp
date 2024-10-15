//caesar algorithm
#include <iostream>
#include <string>
using namespace std;

class MyClass{
     private:
         string str;
         int size;
     
     public:
        MyClass(const string& input,int n) {
            this->str=input;
            this->size=n;
        }
         
         void print(const string& str, int size) {
                  cout << str;
                  cout << endl;
                    
         }
       
 string encryption(const string& text, const string& esh, const string& desh, int size) {
    string encr;
    for (int i = 0; i < size; i++) {  
           char current = text[i];
            bool b=false;
            for (int j = 0; j < 26; j++) {
                if (current == esh[j]) {
                  encr += desh[j];
                  b=true;
                  break;
                 }
            }
            if(b==false){
                    encr+=current;
            }
            
        
    }
    return encr;
}


string decryption(const string& text, const string& esh, const string& desh, int size) {
    string decr;
    for (int i = 0; i < size; i++) {
        char current = text[i];
        bool b=false;
        for (int j = 0; j < 26; j++) {
            if (current == desh[j]) {
                decr += esh[j];
                b=true;
                break;
            }
        }
         if(b==false){
              decr+=current;
            }
    }
    return decr;
}

   
};



int main() {
    string esh, desh;
    string text;
    cout<<"Input text: ";
    getline(cin,text);
    MyClass myclass(text,text.length());
    
    esh.resize(26);
    for (int i = 0; i < 26; i++) {
        esh[i] = 'a' + i;
    }
    cout<<endl<<"Encryption alphabet: ";
    myclass.print(esh,esh.length());
    
    desh.resize(26);
    for (int i =0; i < 26; i++) {
          desh[i]='a'+i+3;
    }
    desh[23]='a';
    desh[24]='b';
    desh[25]='c';
    cout<<"Decryption alphabet: ";
    myclass.print(desh,desh.length());
      
    string en=myclass.encryption(text,esh,desh,text.length());
    cout<<endl<<"Encrypted text: ";
    myclass.print(en,en.length());
     cout<<"Decrypted text: ";
    string dec=myclass.decryption(en,esh,desh,text.length());
    myclass.print(dec,dec.length());
    return 0;
}
