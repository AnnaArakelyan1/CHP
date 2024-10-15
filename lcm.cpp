#include <iostream>
using namespace std;
int gcd(int a,int b){
    int i;
    a=abs(a);
    b=abs(b);
    if(a<b) i=a;
    else i=b;
     while(i>=1){
         if(a%i==0 && b%i==0) break;
         else i--;
         
     }
     return i;
    
}
int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

int main() {
  int a,b;
  cout<<"a=";
  cin>>a;
  cout<<"b=";
  cin>>b;
cout<<lcm(a,b);
    return 0;
}
