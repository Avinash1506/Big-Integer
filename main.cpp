#include<iostream>
#include "bigInt.h"
using namespace std;

int main(){
    BigI a,b,d,e;
    int c;
    cout<<"Enter Big Integer 'a': ";
    cin>>a;
    cout<<"Enter Big Integer 'b': ";
    cin>>b;
    cout<<"Enter integer 'c': ";
    cin>>c;
    cout<<"Enter Big Integer 'd': ";
    cin>>d;
    cout<<"Enter Big Integer 'e': ";
    cin>>e;

    cout<<"\na: "<<a<<"\n";
    cout<<"b: "<<b<<"\n";
    cout<<"c: "<<c<<"\n";
    cout<<"d: "<<d<<"\n";
    cout<<"e: "<<e<<"\n";

    cout<<"\nArithmetic operations BigI + BigI (a + b): "<<"\n";
    cout<<"\tAddition: "<<a + b<<"\n";
    cout<<"\tSubtraction: "<<a - b<<"\n";
    cout<<"\tMultiplication: "<<a * b<<"\n";
    cout<<"\tDivision: "<<a / b<<"\n";
    cout<<"\tModulus: "<<a % b<<"\n";
    cout<<"\nArithmetic operations BigI + int (a + c): "<<"\n";
    cout<<"\tAddition: "<<a + c<<"\n";
    cout<<"\tSubtraction: "<<a - c<<"\n";
    cout<<"\tMultiplication: "<<a * c<<"\n";
    cout<<"\tDivision: "<<a / c<<"\n";
    cout<<"\tModulus: "<<a % c<<"\n";

    cout<<"\nRelational operator BigI operator BigI (a operator b): ";

    cout<<"\n\tGreater than: "<<(a>b)<<"\n";
    cout<<"\tGreater than or equal to: "<<(a>=b)<<"\n";
    cout<<"\tLess than: "<<(a<b)<<"\n";
    cout<<"\tLess than or equal to: "<<(a<=b)<<"\n";
    cout<<"\tEqual to: "<<(a==b)<<"\n";
    cout<<"\tNot equal to: "<<(a!=b)<<"\n";

    cout<<"\nRelational operator BigI operator int (a operator c): ";
    cout<<"\n\tGreater than: "<<(a>c)<<"\n";
    cout<<"\tGreater than or equal to: "<<(a>=c)<<"\n";
    cout<<"\tLess than: "<<(a<c)<<"\n";
    cout<<"\tLess than or equal to: "<<(a<=c)<<"\n";
    cout<<"\tEqual to: "<<(a==c)<<"\n";
    cout<<"\tNot equal to: "<<(a!=c)<<"\n";

    cout<<"\nsize of 'a': "<<a.size()<<"\n";

    cout<<"\nAbsolute value of a: "<<abs(a)<<"\n";
    cout<<"Max value between a and b: "<<max(a,b)<<"\n";
    cout<<"Min value between a and b: "<<min(a,b)<<"\n";
    cout<<"GCD of a and b: "<<gcd(a,b)<<"\n";
    cout<<"LCM of a and b: "<<lcm(a,b)<<"\n";

    cout<<"square root of a is: "<<sqrt(a)<<"\n";

    a++;
    b--;

    cout<<"\na after increment: "<<a<<"\n";
    cout<<"b after decrement: "<<b<<"\n";

    cout<<"\nfactorial of d is: "<<fact(d)<<"\n";
    cout<<"\nd power e is: "<<pow(d,e)<<"\n";

}

